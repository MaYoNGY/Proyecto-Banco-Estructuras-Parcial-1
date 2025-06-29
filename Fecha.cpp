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

void Fecha::sumarMinutos(int min) {
    std::tm tmFecha = {};
    tmFecha.tm_mday = dia;
    tmFecha.tm_mon = mes - 1;
    tmFecha.tm_year = anio - 1900;
    tmFecha.tm_hour = hora;
    tmFecha.tm_min = minutos;
    tmFecha.tm_sec = segundos;
    std::time_t t = std::mktime(&tmFecha);
    t += min * 60;
    tmFecha = *std::localtime(&t);
    dia = tmFecha.tm_mday;
    mes = tmFecha.tm_mon + 1;
    anio = tmFecha.tm_year + 1900;
    hora = tmFecha.tm_hour;
    minutos = tmFecha.tm_min;
    segundos = tmFecha.tm_sec;
}

int Fecha::diferenciaEnMinutos(const Fecha& otra) const {
    std::tm tm1 = {}, tm2 = {};
    tm1.tm_mday = dia; tm1.tm_mon = mes - 1; tm1.tm_year = anio - 1900;
    tm1.tm_hour = hora; tm1.tm_min = minutos; tm1.tm_sec = segundos;
    tm2.tm_mday = otra.dia; tm2.tm_mon = otra.mes - 1; tm2.tm_year = otra.anio - 1900;
    tm2.tm_hour = otra.hora; tm2.tm_min = otra.minutos; tm2.tm_sec = otra.segundos;
    std::time_t t1 = std::mktime(&tm1);
    std::time_t t2 = std::mktime(&tm2);
    return static_cast<int>(std::difftime(t1, t2) / 60);
}

