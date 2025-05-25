#ifndef __CUENTA_H
#define __CUENTA_H


#include <string>
#include "TipoCuenta.h"
#include "Persona.h"
#include "Fecha.h"

class Cuenta
{
private:
   std::string idCuenta; 
   Persona persona;
   double saldo;
   TipoCuenta tipo;
   std::string contrasena;
   Fecha fechaCreacion;


public:
   std::string getIdCuentaStr(void);
   void generarIdCuenta();

   std::string getNombre(void);
   void setNombre(std::string newNombre);
   std::string getApellido(void);
   void setApellido(std::string newApellido);
   std::string getCedula(void);
   void setCedula(std::string newCedula);
   std::string getIdCuenta(void);
   void setIdCuenta(std::string newIdCuenta);

   double getSaldo(void);
   void setSaldo(double newSaldo);

   void setContrasena(const std::string& contrasena);
    std::string getContrasena() const;

   Cuenta(const Persona& persona, double saldo, TipoCuenta tipo);
   ~Cuenta();

   TipoCuenta getTipo(void);
   void setTipo(TipoCuenta newTipo);

   void setFechaCreacion(const Fecha& fecha);
   Fecha getFechaCreacion() const;

};

#endif