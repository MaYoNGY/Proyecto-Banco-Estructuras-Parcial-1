#ifndef __FECHA_H
#define __FECHA_H

#include <iostream>

class Fecha {
private:
    int dia, mes, anio;
    int hora, minutos, segundos;

public:
    Fecha();
    Fecha(int dia, int mes, int anio, int hora = 0, int minutos = 0, int segundos = 0);

    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);
    void setHora(int h);
    void setMinutos(int min);
    void setSegundos(int sec);

    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;
    int getMinutos() const;
    int getSegundos() const;

    void inicializarConFechaActual();
    static bool validarFecha(int dia, int mes, int anio);
    bool diaLaboral(int dia, int mes, int anio);
    bool feriado(int dia, int mes, int anio);
    void mostrarFechaHora() const;

    // Operador <
    bool operator<(const Fecha& other) const {
        if (anio != other.anio) return anio < other.anio;
        if (mes != other.mes) return mes < other.mes;
        if (dia != other.dia) return dia < other.dia;
        if (hora != other.hora) return hora < other.hora;
        if (minutos != other.minutos) return minutos < other.minutos;
        return segundos < other.segundos;
    }

    // Suma minutos a la fecha/hora
    void sumarMinutos(int min);

    // Diferencia en minutos entre dos fechas
    int diferenciaEnMinutos(const Fecha& otra) const;
};

#endif