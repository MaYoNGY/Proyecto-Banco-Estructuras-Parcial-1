#include "Cuenta.h"
#include <string>

int Cuenta::getIdCuenta(void)
{
   return idCuenta;
}

void Cuenta::setIdCuenta(int newIdCuenta)
{
   idCuenta = newIdCuenta;
}

std::string Cuenta::getNombre(void) { 
   return persona.getNombre(); 
}

void Cuenta::setNombre(std::string newNombre) { 
   persona.setNombre(newNombre); 
}

std::string Cuenta::getCedula(void) { 
   return persona.getCedula(); 
}

void Cuenta::setCedula(std::string newCedula) { 
   persona.setCedula(newCedula); 
}

double Cuenta::getSaldo(void)
{
   return saldo;
}

void Cuenta::setSaldo(double newSaldo)
{
   saldo = newSaldo;
}

Cuenta::Cuenta(int id, const Persona& persona, double saldo, TipoCuenta tipo) : idCuenta(id), persona(persona), saldo(saldo), tipo(tipo) {}
Cuenta::~Cuenta(){}

TipoCuenta Cuenta::getTipo(void)
{
   return tipo;
}

void Cuenta::setTipo(TipoCuenta newTipo)
{
   tipo = newTipo;
}