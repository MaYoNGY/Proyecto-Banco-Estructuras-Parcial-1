#ifndef __VALIDAR_H
#define __VALIDAR_H
#include <string> 
#include "Fecha.h"
using namespace std;

class Validar
{
private:
   // Métodos privados para validar entradas
   Fecha fecha;

public:
   static std::string pedirCedula();
   static std::string pedirNombre();
   static std::string pedirApellido();
   static std::string pedirContrasena();
   static std::string pedirMonto();
   static std::string pedirIdCuenta();
   static Fecha pedirFecha();
   static std::pair<Fecha, Fecha> pedirRangoFecha();
   static bool validarCedulaEcuatoriana(const std::string& cedula);



};

#endif


