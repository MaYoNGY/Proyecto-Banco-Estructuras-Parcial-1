/***********************************************************************
 * Module:  Persona.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 20:48:05
 * Purpose: Declaration of the class Persona
 ***********************************************************************/

#if !defined(__Proyecto1_Persona_h)
#define __Proyecto1_Persona_h

class Persona
{
public:
   std::string getCedula(void);
   void setCedula(std::string newCedula);
   std::string getNombre(void);
   void setNombre(std::string newNombre);
   std::string getDireccion(void);
   void setDireccion(std::string newDireccion);
   Persona(std::string cedula, std::string nombre, std::string direccion);
   ~Persona();

protected:
private:
   std::string cedula;
   std::string nombre;
   std::string direccion;


};

#endif