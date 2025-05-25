#ifndef __PERSONA_H
#define __PERSONA_H
#include <string>

class Persona
{

private:
   std::string cedula;
   std::string nombre;
   std::string apellido;

public:
   std::string getCedula(void);
   void setCedula(std::string newCedula);
   std::string getNombre(void);
   void setNombre(std::string newNombre);
   std::string getApellido(void);
   void setApellido(std::string newApellido);
   Persona(std::string cedula, std::string nombre, std::string apellido);
   ~Persona();

};

#endif