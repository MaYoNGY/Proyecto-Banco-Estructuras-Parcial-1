#ifndef __CUENTA_H
#define __CUENTA_H

#include <string>
#include "TipoCuenta.h"
#include "Persona.h"
#include "Fecha.h"
#include "Sucursal.h"

class Cuenta
{
private:
   std::string idCuenta; 
   std::string numeroCuentaCompleto;
   Persona persona;
   double saldo;
   TipoCuenta tipo;
   std::string contrasena;
   Fecha fechaCreacion;
   Sucursal sucursal; // Ahora es un objeto Sucursal

public:
   std::string getIdCuentaStr(void) const;
   void generarIdCuenta();

   std::string getNumeroCuentaCompleto() const;
   void setNumeroCuentaCompleto(const std::string& numero);

   std::string getNombre(void) const;
   void setNombre(std::string newNombre);
   std::string getApellido(void) const;
   void setApellido(std::string newApellido);
   std::string getCedula(void) const;
   void setCedula(std::string newCedula);
   std::string getIdCuenta(void) const;
   void setIdCuenta(std::string newIdCuenta);

   double getSaldo(void) const;
   void setSaldo(double newSaldo);

   void setContrasena(const std::string& contrasena);
   std::string getContrasena() const;

   Cuenta(const Persona& persona, double saldo, TipoCuenta tipo, const Sucursal& sucursal);
   Cuenta(const std::string& idCuenta, const Persona& persona, double saldo, const TipoCuenta& tipo, const std::string& contrasena, const Fecha& fechaCreacion, const Sucursal& sucursal)
      : idCuenta(idCuenta), persona(persona), saldo(saldo), tipo(tipo), contrasena(contrasena), fechaCreacion(fechaCreacion), sucursal(sucursal) {}
   ~Cuenta();

   TipoCuenta getTipo(void) const;
   void setTipo(TipoCuenta newTipo);

   void setFechaCreacion(const Fecha& fecha);
   Fecha getFechaCreacion() const;

   void setSucursal(const Sucursal& s);
   Sucursal getSucursal() const;
};

#endif