/***********************************************************************
 * Module:  TipoCuenta.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:02:01
 * Purpose: Declaration of the class TipoCuenta
 ***********************************************************************/

#if !defined(__Proyecto1_TipoCuenta_h)
#define __Proyecto1_TipoCuenta_h

class TipoCuenta
{
public:
   TipoCuenta(std::string tipo);
   ~TipoCuenta();

protected:
private:
   std::string tipo;


};

#endif