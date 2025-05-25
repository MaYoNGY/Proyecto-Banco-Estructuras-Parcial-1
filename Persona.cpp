
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


Persona::Persona(std::string cedula, std::string nombre)
{
   this->cedula = cedula;
   this->nombre = nombre;

}

Persona::~Persona()
{
   // TODO : implement
}