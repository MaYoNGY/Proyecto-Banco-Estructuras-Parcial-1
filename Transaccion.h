#ifndef __TRANSACCION_H
#define __TRANSACCION_H
#include <iostream>
#include <string>
#include  "Fecha.h"
#include "TipoTransaccion.h"
#include "Cuenta.h"

class Transaccion
{
private:
   Cuenta cuenta;
   TipoTransaccion tipoTransaccion;
   double monto;
   Fecha fecha;

public:
   Cuenta getCuenta() const;
   void setCuenta(const Cuenta& cuenta);
   TipoTransaccion getTipoTransaccion(void);
   void setTipoTransaccion(const TipoTransaccion& newTipoTransaccion);
   double getMonto(void);
   void setMonto(double newMonto);
   Fecha getFecha(void);
   void setFecha(Fecha newFecha);
   Transaccion(const Cuenta& cuenta, const TipoTransaccion& tipo, double monto, const Fecha& fecha);
   ~Transaccion();
};

#endif