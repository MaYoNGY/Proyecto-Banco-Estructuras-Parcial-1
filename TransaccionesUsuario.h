#ifndef TRANSACCIONES_USUARIO_H
#define TRANSACCIONES_USUARIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>

class TransaccionesUsuario {
public:
    // Registra una transacción con idCuenta, monto y hora
    static void registrarTransaccion(const std::string& idCuenta, double monto) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int hora = ltm->tm_hour;
        std::ofstream archivo("transacciones_usuario.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << idCuenta << " " << monto << " " << hora << std::endl;
            archivo.close();
        }
    }

    // Muestra el pico horario de transacciones para un idCuenta usando búsqueda binaria
    static void mostrarPicoTransacciones(const std::string& idCuenta) {
        std::ifstream archivo("transacciones_usuario.txt");
        if (!archivo.is_open()) {
            std::cout << "No hay registros de transacciones." << std::endl;
            return;
        }

        struct Registro {
            std::string idCuenta;
            double monto;
            int hora;
        };

        std::vector<Registro> registros;
        std::string id;
        double monto;
        int hora;
        while (archivo >> id >> monto >> hora) {
            registros.push_back({id, monto, hora});
        }
        archivo.close();

        if (registros.empty()) {
            std::cout << "No hay transacciones registradas." << std::endl;
            return;
        }

        // Ordenar por idCuenta para búsqueda binaria
        std::sort(registros.begin(), registros.end(),
                  [](const Registro& a, const Registro& b) {
                      return a.idCuenta < b.idCuenta;
                  });

        // Búsqueda binaria para encontrar un índice con el idCuenta
        int inicio = 0, fin = registros.size() - 1, encontrado = -1;
        while (inicio <= fin) {
            int medio = (inicio + fin) / 2;
            if (registros[medio].idCuenta == idCuenta) {
                encontrado = medio;
                break;
            } else if (registros[medio].idCuenta < idCuenta) {
                inicio = medio + 1;
            } else {
                fin = medio - 1;
            }
        }

        if (encontrado == -1) {
            std::cout << "No hay transacciones para este ID de cuenta." << std::endl;
            return;
        }

        // Buscar el rango de ocurrencias del idCuenta
        int i = encontrado;
        while (i >= 0 && registros[i].idCuenta == idCuenta) i--;
        int inicioRango = i + 1;

        i = encontrado;
        while (i < (int)registros.size() && registros[i].idCuenta == idCuenta) i++;
        int finRango = i - 1;

        // Contar transacciones por hora
        int frecuencia[24] = {0};
        for (int j = inicioRango; j <= finRango; ++j) {
            int h = registros[j].hora;
            if (h >= 0 && h < 24)
                frecuencia[h]++;
        }

        // Buscar pico horario
        int maxFreq = 0, picoHora = 0;
        for (int i = 0; i < 24; ++i) {
            if (frecuencia[i] > maxFreq) {
                maxFreq = frecuencia[i];
                picoHora = i;
            }
        }

        std::cout << "El horario con mas transacciones para la cuenta " << idCuenta << " es: ";
        std::cout << std::setfill('0') << std::setw(2) << picoHora << ":00 - "
                  << std::setfill('0') << std::setw(2) << picoHora << ":59"
                  << " (" << maxFreq << " transacciones)" << std::endl;
    }
};

#endif