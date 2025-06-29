#ifndef CITA_H
#define CITA_H

#include "Fecha.h"
#include "Sucursal.h"
#include <string>
#include <vector>

class Cita {
private:
    Fecha fecha;
    Sucursal sucursal;
    std::string cliente;
    std::string cedula;
public:
    Cita(const Fecha& f, const Sucursal& s, const std::string& c, const std::string& ced)
        : fecha(f), sucursal(s), cliente(c), cedula(ced) {}

    Fecha getFecha() const { return fecha; }
    Sucursal getSucursal() const { return sucursal; }
    std::string getCliente() const { return cliente; }
    std::string getCedula() const { return cedula; }
};

void asignarCitaSucursal(const Sucursal& sucursal, const std::string& cliente, const std::string& cedula, const Fecha& fechaDeseada, int intervaloMin);
void mostrarDistanciasEntreCitas(const std::vector<Cita>& citas);
void guardarCitasEnArchivo(const std::string& nombreArchivo);
void cargarCitasDesdeArchivo(const std::string& nombreArchivo, const std::vector<Sucursal>& sucursales);void cargarCitasDesdeArchivo(const std::string& nombreArchivo, const std::vector<Sucursal>& sucursales);
void mostrarDistanciaBinariaEntreCitas(const std::vector<Cita>& citas, const Fecha& fechaBuscada);

#endif