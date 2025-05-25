
#include "Persona.h"
#include <string>

std::string Persona::getCedula(void)
{
    // Valida que la cédula tenga exactamente 10 dígitos
    while (cedula.length() != 10) {
        std::cout << "Error: La cédula debe tener exactamente 10 dígitos. Ingrese nuevamente: ";
        std::cin >> cedula;
    }
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
   this->cedula = cedula;
   this->nombre = nombre;
   this->direccion = direccion;
}

Persona::~Persona()
{
   // TODO : implement
}