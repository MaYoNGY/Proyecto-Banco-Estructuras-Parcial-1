#ifndef __FECHA_H
#define __FECHA_H

class Fecha
{
private:
   int dia;
   int mes;
   int anio;

public:
   Fecha(); // Constructor por defecto
   Fecha(int dia, int mes, int anio); // Constructor con parámetros
    int getDia(void);
    void setDia(int newDia);
    int getMes(void);
    void setMes(int newMes);
    int getAnio(void);
    void setAnio(int newAnio);
    void inicializarConFechaActual();
    bool validarFecha(int dia, int mes, int anio);
    bool diaLaboral(int dia, int mes, int anio);
    bool feriado(int dia, int mes, int anio);
   


};

#endif