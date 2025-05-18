/***********************************************************************
 * Module:  Cuenta.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:02:01
 * Purpose: Declaration of the class Cuenta
 ***********************************************************************/

#if !defined(__Proyecto1_Cuenta_h)
#define __Proyecto1_Cuenta_h

#include <TipoCuenta.h>

class Cuenta
{
public:
   int getIdCuenta(void);
   void setIdCuenta(int newIdCuenta);
   std::string getNombre(void);
   void setNombre(std::string newNombre);
   double getSaldo(void);
   void setSaldo(double newSaldo);
   Cuenta();
   ~Cuenta();
   TipoCuenta getTipo(void);
   void setTipo(TipoCuenta newTipo);

protected:
private:
   int idCuenta;
   std::string nombre;
   double saldo;
   TipoCuenta tipo;


};

#endif