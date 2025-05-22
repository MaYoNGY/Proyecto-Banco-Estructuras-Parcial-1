#ifndef __ANIO_H
#define __ANIO_H

class Anio
{

private:
   bool anioBisiesto;
   int anio;
   
public:
   bool getAnioBisiesto(void);
   void setAnioBisiesto(bool newAnioBisiesto);
   int getAnio(void);
   void setAnio(int newAnio);
   void iniciar(void);

protected:
   void finalize(void);




};

#endif