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
   std::string getCedula(void) const;
   void setCedula(std::string newCedula);
   std::string getNombre(void) const;
   void setNombre(std::string newNombre);
   std::string getApellido(void) const;
   void setApellido(std::string newApellido);
   Persona() : cedula(""), nombre(""), apellido("") {} // Constructor por defecto
   Persona(std::string cedula, std::string nombre, std::string apellido);
   ~Persona();

};

#endif