/***********************************************************************
 * Module:  Anio.h
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:22:42
 * Purpose: Declaration of the class Anio
 ***********************************************************************/

#if !defined(__Proyecto1_Anio_h)
#define __Proyecto1_Anio_h

class Anio
{
public:
   int getAnio(void);
   void setAnio(int newAnio);
   bool getAnioBisiesto(void);
   void setAnioBisiesto(bool newAnioBisiesto);
   Anio();
   ~Anio();

protected:
private:
   int anio;
   bool anioBisiesto;


};

#endif