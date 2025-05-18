/***********************************************************************
 * Module:  NodoCuenta.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:05:35
 * Purpose: Declaration of the class NodoCuenta
 ***********************************************************************/

#if !defined(__Proyecto1_NodoCuenta_h)
#define __Proyecto1_NodoCuenta_h

#include <Cuenta.h>

class NodoCuenta
{
public:
protected:
private:
   Cuenta cuenta;
   NodoCuenta* siguiente;
   NodoCuenta* anterior;


};

#endif