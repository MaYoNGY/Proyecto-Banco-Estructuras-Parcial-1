/***********************************************************************
 * Module:  ListaTransaccion.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:34:40
 * Purpose: Declaration of the class ListaTransaccion
 ***********************************************************************/

#if !defined(__Proyecto1_ListaTransaccion_h)
#define __Proyecto1_ListaTransaccion_h

#include <NodoTransaccion.h>
#include <Transaccion.h>

class ListaTransaccion
{
public:
   void insertarTransaccion(Transaccion transaccion);
   void mostrarTransacciones(void);
   void filtrarTransacciones(void);

protected:
private:
   NodoTransaccion* cabeza;
   NodoTransaccion* cola;


};

#endif