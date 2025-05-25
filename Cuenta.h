#ifndef __CUENTA_H
#define __CUENTA_H


#include <string>
#include "TipoCuenta.h"
#include "Persona.h"

class Cuenta
{
private:
   std::string idCuenta; 
   Persona persona;
   double saldo;
   TipoCuenta tipo;
   std::string contrasena;

// ...existing code...
public:
   std::string getIdCuentaStr(void);
   void generarIdCuenta();

   std::string getNombre(void);
   void setNombre(std::string newNombre);
   std::string getCedula(void);
   void setCedula(std::string newCedula);

   double getSaldo(void);
   void setSaldo(double newSaldo);

   void setContrasena(const std::string& contrasena);
    std::string getContrasena() const;

   Cuenta(const Persona& persona, double saldo, TipoCuenta tipo); // <--- CORREGIDO
   ~Cuenta();

   TipoCuenta getTipo(void);
   void setTipo(TipoCuenta newTipo);
};

#endif