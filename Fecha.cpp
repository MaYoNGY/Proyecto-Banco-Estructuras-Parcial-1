#include "Fecha.h"
#include "Validar.h"
#include "Anio.h"
#include <iostream>
#include <ctime>
using namespace std;

int Fecha::getDia(void)
{
   return dia;
}

void Fecha::setDia(int newDia)
{
   dia = newDia;
}

int Fecha::getMes(void)
{
   return mes;
}

void Fecha::setMes(int newMes)
{
   mes = newMes;
}

int Fecha::getAnio(void)
{    
   return anio;
}

void Fecha::setAnio(int newAnio)
{
   anio = newAnio;
}

void Fecha::fecha(void)
{
   int dia_f, mes_f, anio_f;

    bool fechaValida = false;

    while(!fechaValida){

    anio_f = ingresoDatos("Ingrese el anio: ");
    mes_f = ingresoDatos("Ingrese el mes: ");
    dia_f = ingresoDatos("Ingrese el dia: ");


        if (validarFecha(dia_f, mes_f, anio_f) && diaLaboral(dia_f, mes_f, anio_f)){
            setAnio(anio_f);
            setMes(mes_f);
            setDia(dia_f);
            cout << "\nFecha de pago valida: " << dia_f << "/" << mes_f << "/" << anio_f << endl;
            fechaValida = true;
        } else {
            cout << "\nLa fecha ingresada no es valida para pago (dia inexistente, fin de semana o feriado)!!! Ingrese nuevamente:" << endl;
        }
   }
}

void Fecha::inicializarConFechaActual()
{
    // Obtiene la fecha y hora actual del sistema
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    dia = now->tm_mday;
    mes = now->tm_mon + 1;      // tm_mon es 0-11, por eso se suma 1
    anio = now->tm_year + 1900; // tm_year es años desde 1900

    std::cout << "Fecha actual: " << dia << "/" << mes << "/" << anio << std::endl;
}

void Fecha::finalize(void){}

bool Fecha::validarFecha(int dia, int mes, int anio){

    if (mes < 1 || mes > 12){
        return false;
    }
        int diaEnMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        Anio objAnio;
        objAnio.setAnio(anio);

        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)){
            objAnio.setAnioBisiesto(true);
            cout << "\nEl anio " <<anio << " es bisiesto!!";
        } else {
            objAnio.setAnioBisiesto(false);
            cout << "\nEl anio " <<anio << " no es bisiesto!!";
        }

        if (objAnio.getAnioBisiesto() && mes == 2){
            diaEnMes[2] = 29;
        }

        if (dia < 1 || dia > diaEnMes[mes]){
            return false;

        }

        return true;
}

bool Fecha::diaLaboral(int dia, int mes, int anio){

    if(feriado(dia, mes, anio)){
        return false;
    }

    if(mes == 1 || mes == 2){
        mes += 12;
        anio -=1;
    }

    int d = anio % 100;
    int j = anio / 100;

    int h = (dia + 13*(mes + 1)/5 + d + d/4 + j/4 + 5*j) % 7;

    if(h == 0 || h == 1){
        cout << "\nLa fecha cae en fin de semana!!!";
        return false;
    }

    return true;
}

bool Fecha::feriado(int dia, int mes, int anio){

    if ((dia == 1 && mes == 1) || (dia == 1 && mes == 5) ||
        (dia == 10 && mes == 8) || (dia == 2 && mes == 11) ||
        (dia == 25 && mes == 12)){
        return true;
    }

    if (anio == 2025) {
        if ((dia == 3 && mes == 3) || (dia == 4 && mes == 3)) return true;
        if ((dia == 18 && mes == 4) || (dia == 2 && mes == 5))return true;
        if ((dia == 23 && mes == 5) || (dia == 11 && mes == 8))return true;
    }

    return false;

}

