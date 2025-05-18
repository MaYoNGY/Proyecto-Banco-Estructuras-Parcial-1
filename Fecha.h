/***********************************************************************
 * Module:  Fecha.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:24:01
 * Purpose: Declaration of the class Fecha
 ***********************************************************************/

#if !defined(__Proyecto1_Fecha_h)
#define __Proyecto1_Fecha_h

#include <Anio.h>

class Fecha
{
public:
   Anio getAnio(void);
   void setAnio(Anio newAnio);
   int getMes(void);
   void setMes(int newMes);
   int getDia(void);
   void setDia(int newDia);
   Fecha();
   ~Fecha();

protected:
private:
   Anio anio;
   int mes;
   int dia;


};

#endif