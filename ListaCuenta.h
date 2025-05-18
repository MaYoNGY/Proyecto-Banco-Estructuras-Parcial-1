/***********************************************************************
 * Module:  ListaCuenta.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:08:05
 * Purpose: Declaration of the class ListaCuenta
 ***********************************************************************/

#if !defined(__Proyecto1_ListaCuenta_h)
#define __Proyecto1_ListaCuenta_h

#include <NodoCuenta.h>
#include <Cuenta.h>

class ListaCuenta
{
public:
   void insertarCuenta(Cuenta& cuenta);
   NodoCuenta* buscarCuenta(int idCuenta, std::string nombre);
   void mostrarCuentas(void);
   void eliminarCuenta(int idCuenta);

protected:
private:
   NodoCuenta* cabeza;
   NodoCuenta* cola;


};

#endif