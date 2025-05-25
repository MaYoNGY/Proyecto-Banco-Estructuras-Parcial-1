#include "Cuenta.h"
#include <iostream>
#include <set>
#include <string>

// Variable estática para almacenar los IDs generados
/*static std::set<std::string> idsGenerados;

std::string Cuenta::getIdCuenta(void)
{
    // Generar ID: primera letra del nombre + apellido + número si es necesario
    std::string nombreCompleto = persona.getNombre();
    std::istringstream iss(nombreCompleto);
    std::string nombre, apellido;
    iss >> nombre >> apellido; // Se asume que siempre hay nombre y apellido

    // Construir el ID base
    std::string idBase = "";
    idBase += toupper(nombre[0]);
    idBase += apellido;

    std::string idGenerado = idBase;
    int contador = 1;

    // Si el ID ya existe, agregar un número al final
    while (idsGenerados.find(idGenerado) != idsGenerados.end()) { idGenerado = idBase + std::to_string(contador);
        contador++;
    }

    // Guardar el nuevo ID generado
    idsGenerados.insert(idGenerado);

    std::cout << "ID generado para la cuenta: " << idGenerado << std::endl;

    return idCuenta; // Si quieres usar el ID generado como int, puedes hacer un hash aquí
}*/

int Cuenta::getIdCuenta(void) const
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