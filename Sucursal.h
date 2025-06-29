// Sucursal.h
#ifndef SUCURSAL_H
#define SUCURSAL_H

#include <string>

class Sucursal {
private:
    std::string nombre;
    std::string direccion; // Opcional
    std::string codigo;    // Opcional, para identificar sucursal

public:
    Sucursal(const std::string& nombre, const std::string& direccion = "", const std::string& codigo = "")
        : nombre(nombre), direccion(direccion), codigo(codigo) {}

    std::string getNombre() const { return nombre; }
    std::string getDireccion() const { return direccion; }
    std::string getCodigo() const { return codigo; }

    void setNombre(const std::string& n) { nombre = n; }
    void setDireccion(const std::string& d) { direccion = d; }
    void setCodigo(const std::string& c) { codigo = c; }
};

#endif