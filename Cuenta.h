#ifndef __CUENTA_H
#define __CUENTA_H


#include <string>
#include "TipoCuenta.h"
#include "Persona.h"

class Cuenta
{
private:
   int idCuenta; 
   Persona persona;
   double saldo;
   TipoCuenta tipo;

public:
   int getIdCuenta(void) const;
   void setIdCuenta(int newIdCuenta);
   
   std::string getNombre(void);     
   void setNombre(std::string newNombre);
   std::string getCedula(void);      
   void setCedula(std::string newCedula); 

   double getSaldo(void);
   void setSaldo(double newSaldo);

   Cuenta(int id, const Persona& persona, double saldo, TipoCuenta tipo);
      


   ~Cuenta();
   
   TipoCuenta getTipo(void);
   void setTipo(TipoCuenta newTipo);
};

#endif