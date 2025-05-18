/***********************************************************************
 * Module:  Transaccion.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:31:51
 * Purpose: Declaration of the class Transaccion
 ***********************************************************************/

#if !defined(__Proyecto1_Transaccion_h)
#define __Proyecto1_Transaccion_h

#include <Fecha.h>

class Transaccion
{
public:
   std::string getTipoTransaccion(void);
   void setTipoTransaccion(std::string newTipoTransaccion);
   double getMonto(void);
   void setMonto(double newMonto);
   Fecha getFecha(void);
   void setFecha(Fecha newFecha);
   Transaccion();
   ~Transaccion();

protected:
private:
   std::string tipoTransaccion;
   double monto;
   Fecha fecha;


};

#endif