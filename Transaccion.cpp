#include "Transaccion.h"

Cuenta Transaccion::getCuenta() const { 
   return cuenta; 
}

void Transaccion::setCuenta(const Cuenta& c) { 
   cuenta = c; 
}

TipoTransaccion Transaccion::getTipoTransaccion(void) { 
   return tipoTransaccion; 
}

void Transaccion::setTipoTransaccion(const TipoTransaccion& newTipoTransaccion) { 
   tipoTransaccion = newTipoTransaccion; 
}

double Transaccion::getMonto(void) { 
   return monto; 
}

void Transaccion::setMonto(double newMonto) { 
   monto = newMonto; 
}

Fecha Transaccion::getFecha(void) { 
   return fecha; 
}

void Transaccion::setFecha(Fecha newFecha) { 
   fecha = newFecha; 
}

Transaccion::Transaccion(const Cuenta& cuenta, const TipoTransaccion& tipo, double monto, const Fecha& fecha) : cuenta(cuenta), tipoTransaccion(tipo), monto(monto), fecha(fecha) {}

Transaccion::~Transaccion() {}