#ifndef ACCESO_USUARIO_H
#define ACCESO_USUARIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <iomanip>

class AccesoUsuario {
public:
    static void registrarAcceso(const std::string& cedula) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int hora = ltm->tm_hour;
        std::ofstream archivo("accesos.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << cedula << " " << hora << std::endl;
            archivo.close();
        }
    }

    static void mostrarPicoAcceso(const std::string& cedula) {
        std::ifstream archivo("accesos.txt");
        if (!archivo.is_open()) {
            std::cout << "No hay registros de acceso." << std::endl;
            return;
        }

        std::vector<std::pair<std::string, int>> registros;
        std::string ced;
        int hora;
        while (archivo >> ced >> hora) {
            registros.push_back({ced, hora});
        }
        archivo.close();

        if (registros.empty()) {
            std::cout << "No hay accesos registrados." << std::endl;
            return;
        }

        // Ordenar por cédula para poder aplicar búsqueda binaria
        std::sort(registros.begin(), registros.end(),
                  [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                      return a.first < b.first;
                  });

        // Búsqueda binaria para encontrar un índice con la cédula
        int inicio = 0, fin = registros.size() - 1, encontrado = -1;
        while (inicio <= fin) {
            int medio = (inicio + fin) / 2;
            if (registros[medio].first == cedula) {
                encontrado = medio;
                break;
            } else if (registros[medio].first < cedula) {
                inicio = medio + 1;
            } else {
                fin = medio - 1;
            }
        }

        if (encontrado == -1) {
            std::cout << "No hay accesos registrados para este usuario." << std::endl;
            return;
        }

        // Buscar hacia atrás y adelante desde el índice encontrado
        int i = encontrado;
        while (i >= 0 && registros[i].first == cedula) i--;
        int inicioRango = i + 1;

        i = encontrado;
        while (i < registros.size() && registros[i].first == cedula) i++;
        int finRango = i - 1;

        int frecuencia[24] = {0};
        for (int j = inicioRango; j <= finRango; ++j) {
            int h = registros[j].second;
            if (h >= 0 && h < 24)
                frecuencia[h]++;
        }

        int maxFreq = 0, picoHora = 0;
        for (int i = 0; i < 24; ++i) {
            if (frecuencia[i] > maxFreq) {
                maxFreq = frecuencia[i];
                picoHora = i;
            }
        }

        std::cout << "El horario de mayor acceso para el usuario " << cedula << " es: ";
        std::cout << std::setfill('0') << std::setw(2) << picoHora << ":00 - "
                  << std::setfill('0') << std::setw(2) << picoHora << ":59"
                  << " (" << maxFreq << " accesos)" << std::endl;
    }
};

#endif