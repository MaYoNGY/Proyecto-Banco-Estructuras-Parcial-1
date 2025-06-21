#include "Cuenta.h"
#include <iostream>
#include <sstream>
#include <set>
#include <cctype>
#include <string>
#include <iomanip>

// Variable estática para el contador de IDs

extern unsigned long long contadorId;

// Genera un ID de cuenta incremental con ceros a la izquierda
void Cuenta::generarIdCuenta() {
    std::ostringstream oss;
    oss << std::setw(10) << std::setfill('0') << contadorId++;
    idCuenta = oss.str();
    
    // Generar el número de cuenta completo con formato ecuatoriano
    std::string codigoPais = "EC";
    std::string codigoEntidad = "0001";
    std::string codigoOficina = "0001";
    
    // Cálculo simple de dígitos de control
    int suma = 0;
    for (char c : idCuenta) suma += c - '0';
    int digitoControl = suma % 100;
    
    std::ostringstream ossCompleto;
    ossCompleto << codigoPais << codigoEntidad << codigoOficina
               << std::setw(2) << std::setfill('0') << digitoControl
               << idCuenta;
    
    numeroCuentaCompleto = ossCompleto.str();
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
    generarIdCuenta();  // Esto ya establece idCuenta y numeroCuentaCompleto
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

// Métodos para el número de cuenta bancaria completo
std::string Cuenta::getNumeroCuentaCompleto() const {
    return numeroCuentaCompleto;
}

void Cuenta::setNumeroCuentaCompleto(const std::string& numero) {
    numeroCuentaCompleto = numero;
}