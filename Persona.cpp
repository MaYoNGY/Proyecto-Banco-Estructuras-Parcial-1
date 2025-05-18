/***********************************************************************
 * Module:  Persona.cpp
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 20:48:05
 * Purpose: Implementation of the class Persona
 ***********************************************************************/

#include "Persona.h"

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getCedula()
// Purpose:    Implementation of Persona::getCedula()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getCedula(void)
{
   return cedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setCedula(std::string newCedula)
// Purpose:    Implementation of Persona::setCedula()
// Parameters:
// - newCedula
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setCedula(std::string newCedula)
{
   cedula = newCedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getNombre()
// Purpose:    Implementation of Persona::getNombre()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getNombre(void)
{
   return nombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setNombre(std::string newNombre)
// Purpose:    Implementation of Persona::setNombre()
// Parameters:
// - newNombre
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setNombre(std::string newNombre)
{
   nombre = newNombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getDireccion()
// Purpose:    Implementation of Persona::getDireccion()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getDireccion(void)
{
   return direccion;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setDireccion(std::string newDireccion)
// Purpose:    Implementation of Persona::setDireccion()
// Parameters:
// - newDireccion
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setDireccion(std::string newDireccion)
{
   direccion = newDireccion;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::Persona(std::string cedula, std::string nombre, std::string direccion)
// Purpose:    Implementation of Persona::Persona()
// Parameters:
// - cedula
// - nombre
// - direccion
// Return:     
////////////////////////////////////////////////////////////////////////

Persona::Persona(std::string cedula, std::string nombre, std::string direccion)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::~Persona()
// Purpose:    Implementation of Persona::~Persona()
// Return:     
////////////////////////////////////////////////////////////////////////

Persona::~Persona()
{
   // TODO : implement
}