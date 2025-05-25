#ifndef __VALIDAR_H
#define __VALIDAR_H
#include <string> 
using namespace std;

class Validar
{
public:
   static std::string pedirCedula();
   static std::string pedirNombre();
   static std::string pedirApellido();
   static std::string pedirContrasena();
   static bool validarCedulaEcuatoriana(const std::string& cedula);



};

#endif


