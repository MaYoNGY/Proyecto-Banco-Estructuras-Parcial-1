#include "Cita.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>

extern std::map<std::string, std::vector<Cita>> citasPorSucursal;

void asignarCitaSucursal(const Sucursal& sucursal, const std::string& cliente, const std::string& cedula, const Fecha& fechaDeseada, int intervaloMin) {
    std::vector<Cita>& citas = citasPorSucursal[sucursal.getCodigo()];
    std::sort(citas.begin(), citas.end(), [](const Cita& a, const Cita& b) {
        return a.getFecha() < b.getFecha();
    });

    Fecha posible = fechaDeseada;

    // Caso base: no hay citas
    if (citas.empty()) {
        citas.push_back(Cita(posible, sucursal, cliente, cedula));        
        std::cout << "Cita asignada para: ";
        posible.mostrarFechaHora();
        std::cout << std::endl;
        return;
    }

    // Búsqueda binaria para encontrar la posición de inserción
    int left = 0, right = citas.size();
    int pos = citas.size(); // Por defecto al final
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (citas[mid].getFecha() < posible) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    pos = left; // Aquí debería insertarse la cita

    // Verifica si hay hueco ANTES de la cita en pos
    bool asignada = false;
    if (pos == 0) {
        // ¿Cabe antes de la primera cita?
        if (citas[0].getFecha().diferenciaEnMinutos(posible) >= intervaloMin && !(posible < citas[0].getFecha())) {
            citas.insert(citas.begin(), Cita(posible, sucursal, cliente, cedula));
            asignada = true;
        }
    } else {
        // ¿Cabe entre citas[pos-1] y citas[pos]?
        Fecha finAnterior = citas[pos-1].getFecha();
        finAnterior.sumarMinutos(intervaloMin);
        if ((pos == citas.size() || posible.diferenciaEnMinutos(finAnterior) >= 0) &&
            (pos == citas.size() || citas[pos].getFecha().diferenciaEnMinutos(posible) >= intervaloMin)) {
            // Ajusta posible si es antes del fin de la anterior
            if (posible < finAnterior) posible = finAnterior;
            citas.insert(citas.begin() + pos, Cita(posible, sucursal, cliente, cedula));
            asignada = true;
        }
    }

    // Si no se pudo asignar en el hueco encontrado, busca el siguiente hueco disponible
    while (!asignada) {
        // Busca después de la última cita
        Fecha finUltima = citas.back().getFecha();
        finUltima.sumarMinutos(intervaloMin);
        posible = finUltima;
        citas.push_back(Cita(posible, sucursal, cliente, cedula));        
        asignada = true;
    }

    std::cout << "Cita asignada para: ";
    posible.mostrarFechaHora();
    std::cout << std::endl;
}

void mostrarDistanciasEntreCitas(const std::vector<Cita>& citas) {
    for (size_t i = 1; i < citas.size(); ++i) {
        int D = citas[i].getFecha().diferenciaEnMinutos(citas[i-1].getFecha());
        std::cout << "Distancia D entre cliente " << i-1 << " y " << i << ": " << D << " minutos\n";
    }
}

void guardarCitasEnArchivo(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    for (const auto& par : citasPorSucursal) {
        const std::string& codigoSucursal = par.first;
        for (const Cita& cita : par.second) {
            const Fecha& f = cita.getFecha();
            archivo << codigoSucursal << '|'
                    << cita.getCliente() << '|'
                    << cita.getCedula() << '|'
                    << f.getDia() << ' ' << f.getMes() << ' ' << f.getAnio() << ' '
                    << f.getHora() << ' ' << f.getMinutos() << ' ' << f.getSegundos()
                    << '\n';
        }
    }
    archivo.close();
}

void cargarCitasDesdeArchivo(const std::string& nombreArchivo, const std::vector<Sucursal>& sucursales) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    citasPorSucursal.clear();
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string codigoSucursal, cliente, cedula;
        int dia, mes, anio, hora, minutos, segundos;
        if (std::getline(iss, codigoSucursal, '|') &&
            std::getline(iss, cliente, '|') &&
            std::getline(iss, cedula, '|') &&
            iss >> dia >> mes >> anio >> hora >> minutos >> segundos) {
            // Busca la sucursal por código
            auto it = std::find_if(sucursales.begin(), sucursales.end(),
                [&](const Sucursal& s) { return s.getCodigo() == codigoSucursal; });
            if (it != sucursales.end()) {
                Fecha fecha(dia, mes, anio, hora, minutos, segundos);
                citasPorSucursal[codigoSucursal].push_back(Cita(fecha, *it, cliente, cedula));
            }
        }
    }
    archivo.close();
}

void mostrarDistanciaBinariaEntreCitas(const std::vector<Cita>& citas, const Fecha& fechaBuscada) {
    if (citas.size() < 2) {
        std::cout << "No hay suficientes citas para calcular distancias.\n";
        return;
    }

    // Búsqueda binaria por día, mes y año
    int left = 0, right = citas.size() - 1;
    int pos = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        const Fecha& f = citas[mid].getFecha();
        if (f.getAnio() < fechaBuscada.getAnio() ||
            (f.getAnio() == fechaBuscada.getAnio() && f.getMes() < fechaBuscada.getMes()) ||
            (f.getAnio() == fechaBuscada.getAnio() && f.getMes() == fechaBuscada.getMes() && f.getDia() < fechaBuscada.getDia())) {
            left = mid + 1;
        } else if (f.getAnio() > fechaBuscada.getAnio() ||
                   (f.getAnio() == fechaBuscada.getAnio() && f.getMes() > fechaBuscada.getMes()) ||
                   (f.getAnio() == fechaBuscada.getAnio() && f.getMes() == fechaBuscada.getMes() && f.getDia() > fechaBuscada.getDia())) {
            right = mid - 1;
        } else {
            pos = mid;
            break;
        }
    }

    if (pos == -1) {
        std::cout << "No se encontro una cita en esa fecha.\n";
        return;
    }

    // Mostrar distancia con la cita anterior (si existe)
    if (pos > 0) {
        int Dprev = citas[pos].getFecha().diferenciaEnMinutos(citas[pos-1].getFecha());
        std::cout << "Distancia D entre cliente " << citas[pos-1].getCliente()
                  << " y " << citas[pos].getCliente() << ": " << Dprev << " minutos\n";
    }
    // Mostrar distancia con la cita siguiente (si existe)
    if (pos < (int)citas.size() - 1) {
        int Dnext = citas[pos+1].getFecha().diferenciaEnMinutos(citas[pos].getFecha());
        std::cout << "Distancia D entre cliente " << citas[pos].getCliente()
                  << " y " << citas[pos+1].getCliente() << ": " << Dnext << " minutos\n";
    }
}

