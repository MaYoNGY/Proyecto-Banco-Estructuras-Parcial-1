#include "TipoTransaccion.h"

TipoTransaccion::TipoTransaccion(const std::string& tipo)
{
    this->tipo = tipo; // Asume que tipo es "DEPOSITO" o "RETIRO"
}

TipoTransaccion::~TipoTransaccion() {}

std::string TipoTransaccion::getTipo() const {
    return tipo;
}

bool TipoTransaccion::esDeposito() const {
    return tipo == "corriente";
}

bool TipoTransaccion::esRetiro() const {
    return tipo == "retiro";
}