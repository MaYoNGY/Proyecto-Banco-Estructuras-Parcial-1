#ifndef __FECHA_H
#define __FECHA_H

#include "Anio.h"
#include "Validar.h"

class Fecha
{
public:
   int getDia(void);
   void setDia(int newDia);
   int getMes(void);
   void setMes(int newMes);
   int getAnio(void);
   void setAnio(int newAnio);
   void fecha(void);
   void inicializarConFechaActual();

protected:
   void finalize(void);

private:
   int dia;
   int mes;
   int anio;

    bool validarFecha(int dia, int mes, int anio);
    bool diaLaboral(int dia, int mes, int anio);
    bool feriado(int dia, int mes, int anio);
};

#endif