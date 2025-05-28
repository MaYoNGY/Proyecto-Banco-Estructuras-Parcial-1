#include "Cuenta.h"
#include <iostream>
#include <sstream>
#include <set>
#include <cctype>
#include <string>
#include <iomanip>

// Variable estática para el contador de IDs
static unsigned long long contadorId = 1;

// Genera un ID de cuenta incremental con ceros a la izquierda
void Cuenta::generarIdCuenta() {
    std::ostringstream oss;
    oss << std::setw(9) << std::setfill('0') << contadorId++;
    idCuenta = oss.str();
}

// Devuelve el ID de cuenta como string
std::string Cuenta::getIdCuentaStr() const {
    return idCuenta;
}     
std::string Cuenta::getNombre(void) const { 
   return persona.getNombre(); 
}

void Cuenta::setNombre(std::string newNombre) { 
   persona.setNombre(newNombre); 
}

std::string Cuenta::getApellido(void) const { 
   return persona.getApellido(); 
}

void Cuenta::setApellido(std::string newApellido) { 
   persona.setApellido(newApellido); 
}

std::string Cuenta::getCedula(void) const { 
   return persona.getCedula(); 
}
std::string Cuenta::getIdCuenta() const { 
   return idCuenta; 
}

void Cuenta::setCedula(std::string newCedula) { 
   persona.setCedula(newCedula); 
}

double Cuenta::getSaldo(void) const {
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

TipoCuenta Cuenta::getTipo(void) const {
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