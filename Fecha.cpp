#include "Fecha.h"
#include <ctime>

Fecha::Fecha() : dia(0), mes(0), anio(0) {}

int Fecha::getDia() { return dia; }
void Fecha::setDia(int newDia) { dia = newDia; }
int Fecha::getMes() { return mes; }
void Fecha::setMes(int newMes) { mes = newMes; }
int Fecha::getAnio() { return anio; }
void Fecha::setAnio(int newAnio) { anio = newAnio; }

void Fecha::inicializarConFechaActual() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    dia = now->tm_mday;
    mes = now->tm_mon + 1;
    anio = now->tm_year + 1900;
}

bool Fecha::validarFecha(int d, int m, int a) {
    // Año razonable para Ecuador
    if (a < 1900 || a > 2100) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;

    // Días máximos por mes
    int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    // Ajuste para año bisiesto en febrero
    bool bisiesto = (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0));
    if (bisiesto && m == 2) {
        if (d > 29) return false;
    } else {
        if (d > diasMes[m - 1]) return false;
    }
    return true;
}

void calcularPascua(int anio, int &dia, int &mes) {
    int a = anio % 19;
    int b = anio / 100;
    int c = anio % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    int mesPascua = (h + l - 7 * m + 114) / 31;
    int diaPascua = ((h + l - 7 * m + 114) % 31) + 1;
    dia = diaPascua;
    mes = mesPascua;
}

bool Fecha::feriado(int d, int m, int a) {
    // Feriados nacionales fijos en Ecuador
    if ((d == 1 && m == 1)   // Año Nuevo
        || (d == 1 && m == 5)   // Día del Trabajo
        || (d == 24 && m == 5)  // Batalla de Pichincha
        || (d == 10 && m == 8)  // Independencia de Guayaquil
        || (d == 9 && m == 10)  // Independencia de Guayaquil (a veces se mueve)
        || (d == 2 && m == 11)  // Día de los Difuntos
        || (d == 3 && m == 11)  // Independencia de Cuenca
        || (d == 25 && m == 12) // Navidad
    ) return true;

    // FERIADOS MÓVILES: Carnaval y Viernes Santo
    int diaPascua, mesPascua;
    calcularPascua(a, diaPascua, mesPascua);

    // Carnaval: lunes y martes antes de Pascua (47 y 48 días antes)
    tm fechaPascua = {};
    fechaPascua.tm_year = a - 1900;
    fechaPascua.tm_mon = mesPascua - 1;
    fechaPascua.tm_mday = diaPascua;
    mktime(&fechaPascua);

    // Lunes y martes de Carnaval
    tm carnavalLunes = fechaPascua;
    carnavalLunes.tm_mday -= 48;
    mktime(&carnavalLunes);
    tm carnavalMartes = fechaPascua;
    carnavalMartes.tm_mday -= 47;
    mktime(&carnavalMartes);

    if ((d == carnavalLunes.tm_mday && m == carnavalLunes.tm_mon + 1) ||
        (d == carnavalMartes.tm_mday && m == carnavalMartes.tm_mon + 1)) {
        return true;
    }

    // Viernes Santo: 2 días antes de Pascua
    tm viernesSanto = fechaPascua;
    viernesSanto.tm_mday -= 2;
    mktime(&viernesSanto);

    if (d == viernesSanto.tm_mday && m == viernesSanto.tm_mon + 1) {
        return true;
    }

    return false;

    // Corpus Christi: 60 días después de Pascua
    tm corpusChristi = fechaPascua;
    corpusChristi.tm_mday += 60;
    mktime(&corpusChristi);
    if (d == corpusChristi.tm_mday && m == corpusChristi.tm_mon + 1) {
        return true;
    }

    // Ascensión: 39 días después de Pascua
    tm ascension = fechaPascua;
    ascension.tm_mday += 39;
    mktime(&ascension);
    if (d == ascension.tm_mday && m == ascension.tm_mon + 1) {
        return true;
    }
}

bool Fecha::diaLaboral(int d, int m, int a) {
    // 0 = domingo, 6 = sábado
    tm fecha = {};
    fecha.tm_mday = d;
    fecha.tm_mon = m - 1;
    fecha.tm_year = a - 1900;
    mktime(&fecha);
    int diaSemana = fecha.tm_wday;
    if (diaSemana == 0 || diaSemana == 6) return false; // Domingo o sábado
    if (feriado(d, m, a)) return false;
    return true;
}

