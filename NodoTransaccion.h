/***********************************************************************
 * Module:  NodoTransaccion.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:30:28
 * Purpose: Declaration of the class NodoTransaccion
 ***********************************************************************/

#if !defined(__Proyecto1_NodoTransaccion_h)
#define __Proyecto1_NodoTransaccion_h

#include <Transaccion.h>

class NodoTransaccion
{
public:
protected:
private:
   Transaccion transaccion;
   NodoTransaccion* siguiente;
   NodoTransaccion* anterior;


};

#endif