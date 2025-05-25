#ifndef __PERSONA_H
#define __PERSONA_H
#include <string>

class Persona
{

private:
   std::string cedula;
   std::string nombre;

public:
   std::string getCedula(void);
   void setCedula(std::string newCedula);
   std::string getNombre(void);
   void setNombre(std::string newNombre);
   Persona(std::string cedula, std::string nombre);
   ~Persona();

};

#endif