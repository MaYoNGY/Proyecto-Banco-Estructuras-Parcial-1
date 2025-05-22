
#include "Persona.h"
#include <string>

std::string Persona::getCedula(void)
{
   return cedula;
}

void Persona::setCedula(std::string newCedula)
{
   cedula = newCedula;
}

std::string Persona::getNombre(void)
{
   return nombre;
}

void Persona::setNombre(std::string newNombre)
{
   nombre = newNombre;
}

std::string Persona::getDireccion(void)
{
   return direccion;
}

void Persona::setDireccion(std::string newDireccion)
{
   direccion = newDireccion;
}

Persona::Persona(std::string cedula, std::string nombre, std::string direccion)
{
   // TODO : implement
}

Persona::~Persona()
{
   // TODO : implement
}