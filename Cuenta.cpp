#include "Cuenta.h"
#include <iostream>
#include <sstream>
#include <set>
#include <cctype>
#include <string>


// Variable estática para almacenar los IDs generados
static std::set<std::string> idsGenerados;

void Cuenta::generarIdCuenta() {
    std::string nombre = persona.getNombre();
    std::string apellido = persona.getApellido();

    std::string idBase = "";
    if (!nombre.empty())
        idBase += toupper(nombre[0]);
    idBase += apellido;

    std::string idGenerado = idBase;
    int contador = 1;

    while (idsGenerados.find(idGenerado) != idsGenerados.end()) {
        idGenerado = idBase + std::to_string(contador);
        contador++;
    }

    idsGenerados.insert(idGenerado);
    idCuenta = idGenerado;
}

std::string Cuenta::getIdCuentaStr(void) {
    return idCuenta;
}

std::string Cuenta::getNombre(void) { 
   return persona.getNombre(); 
}

void Cuenta::setNombre(std::string newNombre) { 
   persona.setNombre(newNombre); 
}

std::string Cuenta::getApellido(void) { 
   return persona.getApellido(); 
}

void Cuenta::setApellido(std::string newApellido) { 
   persona.setApellido(newApellido); 
}

std::string Cuenta::getCedula(void) { 
   return persona.getCedula(); 
}

void Cuenta::setCedula(std::string newCedula) { 
   persona.setCedula(newCedula); 
}

double Cuenta::getSaldo(void) {
   return saldo;
}

void Cuenta::setSaldo(double newSaldo) {
   saldo = newSaldo;
}

// Constructor corregido: NO recibe id, el id se genera con generarIdCuenta()
Cuenta::Cuenta(const Persona& persona, double saldo, TipoCuenta tipo)
    : persona(persona), saldo(saldo), tipo(tipo) {
    generarIdCuenta();
    fechaCreacion.inicializarConFechaActual();
}

Cuenta::~Cuenta() {}

TipoCuenta Cuenta::getTipo(void) {
   return tipo;
}

void Cuenta::setTipo(TipoCuenta newTipo) {
   tipo = newTipo;
}

void Cuenta::setContrasena(const std::string& contrasena) {
    this->contrasena = contrasena;
}

std::string Cuenta::getContrasena() const {
    return contrasena;
}

void Cuenta::setFechaCreacion(const Fecha& fecha) { 
   fechaCreacion = fecha; 
}

Fecha Cuenta::getFechaCreacion() const { 
   return fechaCreacion; 
}