#include "Fecha.h"
#include <ctime>

Fecha::Fecha() : dia(0), mes(0), anio(0), hora(0), minutos(0), segundos(0) {}

Fecha::Fecha(int dia, int mes, int anio, int hora, int minutos, int segundos) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
    this->hora = hora;
    this->minutos = minutos;
    this->segundos = segundos;
}

void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAnio(int a) { anio = a; }
void Fecha::setHora(int h) { hora = h; }
void Fecha::setMinutos(int min) { minutos = min; }
void Fecha::setSegundos(int sec) { segundos = sec; }

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }
int Fecha::getHora() const { return hora; }
int Fecha::getMinutos() const { return minutos; }
int Fecha::getSegundos() const { return segundos; }

void Fecha::inicializarConFechaActual() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    dia = now->tm_mday;
    mes = now->tm_mon + 1;
    anio = now->tm_year + 1900;
    hora = now->tm_hour;
    minutos = now->tm_min;
    segundos = now->tm_sec;
}

bool Fecha::validarFecha(int d, int m, int a) {
    if (a < 1900 || a > 2100) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;

    int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    bool bisiesto = (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0));
    if (bisiesto && m == 2) {
        if (d > 29) return false;
    } else {
        if (d > diasMes[m - 1]) return false;
    }
    return true;
}

void Fecha::mostrarFechaHora() const {
    std::cout << dia << "/" << mes << "/" << anio << " "
              << hora << ":" << minutos << ":" << segundos;
}

