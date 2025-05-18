/***********************************************************************
 * Module:  Anio.h
 * Author:  mayo
 * Modified: lunes, 28 de abril de 2025 12:05:21 a. m.
 * Purpose: Declaration of the class Anio
 ***********************************************************************/

#if !defined(__Class_Diagram_2_Anio_h)
#define __Class_Diagram_2_Anio_h

class Anio
{
public:
   bool getAnioBisiesto(void);
   void setAnioBisiesto(bool newAnioBisiesto);
   int getAnio(void);
   void setAnio(int newAnio);
   void iniciar(void);

protected:
   void finalize(void);

private:
   bool anioBisiesto;
   int anio;


};

#endif
