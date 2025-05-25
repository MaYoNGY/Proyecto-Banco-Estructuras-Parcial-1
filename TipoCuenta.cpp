#include "TipoCuenta.h"

TipoCuenta::TipoCuenta(const std::string& tipo)
{
    this->tipo = tipo; // Asume que tipo es "ahorro" o "corriente"
}

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