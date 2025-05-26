
#include "Persona.h"
#include <string>

std::string Persona::getCedula(void) const
{
    return cedula;
}

void Persona::setCedula(std::string newCedula)
{
   cedula = newCedula;
}

std::string Persona::getNombre(void) const
{
   return nombre;
}

void Persona::setNombre(std::string newNombre)
{
   nombre = newNombre;
}

std::string Persona::getApellido(void) const
{
   return apellido;
}

void Persona::setApellido(std::string newApellido)
{
   nombre = newApellido;
}


Persona::Persona(std::string cedula, std::string nombre, std::string apellido)
{
   this->cedula = cedula;
   this->nombre = nombre;
   this->apellido = apellido;
}

Persona::~Persona()
{
   // TODO : implement
}