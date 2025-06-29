#include "Cuenta.h"
#include <iostream>
#include <sstream>
#include <conio.h> // Para _getch()
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

    std::string codigoPais = "EC";
    std::string codigoEntidad = "2112";
    std::string codigoSucursal = sucursal.getCodigo().empty() ? "0001" : sucursal.getCodigo();

    // Cálculo del dígito de control usando módulo 11
    // Ponderaciones típicas: 2,3,4,5,6,7,2,3,4,5 (de derecha a izquierda)
    int ponderaciones[10] = {2,3,4,5,6,7,2,3,4,5};
    int suma = 0;
    for (int i = 0; i < 10; ++i) {
        int digito = idCuenta[9 - i] - '0'; // de derecha a izquierda
        suma += digito * ponderaciones[i];
    }
    int digitoControl = 11 - (suma % 11);
    if (digitoControl == 11) digitoControl = 0;
    if (digitoControl == 10) digitoControl = 1;

    std::ostringstream ossCompleto;
    ossCompleto << codigoPais << std::setw(2) << std::setfill('0') << digitoControl 
                << codigoEntidad << codigoSucursal
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
Cuenta::Cuenta(const Persona& persona, double saldo, TipoCuenta tipo, const Sucursal& sucursal)
    : persona(persona), saldo(saldo), tipo(tipo), sucursal(sucursal) {
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

// Métodos para el número de cuenta bancaria completo
std::string Cuenta::getNumeroCuentaCompleto() const {
    return numeroCuentaCompleto;
}

void Cuenta::setNumeroCuentaCompleto(const std::string& numero) {
    numeroCuentaCompleto = numero;
}

void Cuenta::setSucursal(const Sucursal& s) {
    sucursal = s;
}

Sucursal Cuenta::getSucursal() const {
    return sucursal;
}