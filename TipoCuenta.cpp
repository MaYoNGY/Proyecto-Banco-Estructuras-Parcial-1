#include "TipoCuenta.h"

TipoCuenta::TipoCuenta() : tipo("") {} // Implementación del constructor por defecto

TipoCuenta::TipoCuenta(const std::string& t) : tipo(t) {}

TipoCuenta::~TipoCuenta() {}

std::string TipoCuenta::getTipo() const {
    return tipo;
}

bool TipoCuenta::esAhorro() const {
    return tipo == "Ahorro";
}

bool TipoCuenta::esCorriente() const {
    return tipo == "corriente";
}