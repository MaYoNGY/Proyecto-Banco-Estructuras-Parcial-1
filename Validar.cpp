#include "Validar.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
using namespace std;

std::string Validar::pedirCedula() {
    std::string cedula;
    while (true) {
        cout << "Ingrese su cedula: ";
        cedula = "";
        char c;
        while (true) {
            c = _getch();
            if (c == 13) { // Enter
                cout << endl;
                break;
            }
            if (c == 8) { // Backspace
                if (!cedula.empty()) {
                    cedula.pop_back();
                    cout << "\b \b";
                }
            } else if (c >= '0' && c <= '9' && cedula.length() < 10) {
                cedula += c;
                cout << c;
            }
        }
        if (cedula.length() == 10 && Validar::validarCedulaEcuatoriana(cedula)) {
            break;
        } else {
            cout << "Cedula invalida. Intente de nuevo." << endl;
        }
    }
    return cedula;
}

std::string Validar::pedirNombre() {
    std::string nombre;
    do {
        cout << "Ingrese su nombre: ";
        nombre = "";
        char c;
        while (true) {
            c = _getch();
            if (c == 13) { // Enter
                cout << endl;
                break;
            }
            else if (c == 8) { // Backspace
                if (!nombre.empty()) {
                    nombre.pop_back();
                    cout << "\b \b";
                }
            }
            else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
                nombre += c;
                cout << c;
            }
        }
        if (nombre.empty()) {
            cout << "El nombre no puede estar vacio. Intente de nuevo." << endl;
        }
    } while (nombre.empty());
    return nombre;
}

std::string Validar::pedirApellido() {
    std::string apellido;
    do {
        cout << "Ingrese su apellido: ";
        apellido = "";
        char c;
        while (true) {
            c = _getch();
            if (c == 13) { // Enter
                cout << endl;
                break;
            }
            else if (c == 8) { // Backspace
                if (!apellido.empty()) {
                    apellido.pop_back();
                    cout << "\b \b";
                }
            }
            else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
                apellido += c;
                cout << c;
            }
        }
        if (apellido.empty()) {
            cout << "El apellido no puede estar vacio. Intente de nuevo." << endl;
        }
    } while (apellido.empty());
    return apellido;
}

std::string Validar::pedirContrasena() {
    std::string contrasena;
    do {
    cout << "Ingrese su contrasena: ";
    char c;
        while (true) {
        c = _getch();
        if (c == 13) { // Enter
            cout << endl;
            break;
        }
        else if (c == 8) { // Backspace
            if (!contrasena.empty()) {
                contrasena.pop_back();
                cout << "\b \b";
            }
        }
        else {
            contrasena += c;
            cout << '*'; // Mostrar asterisco en lugar de caracter
        }
    
        }
        if (contrasena.empty()) {
            cout << "La contraseña no puede estar vacia. Intente de nuevo." << endl;
        }
    }while(contrasena.empty());
    return contrasena;
}

std::string Validar::pedirMonto() {
    std::string monto;
    char c;
    cout << "(Solo numeros y punto decimal, maximo 2 decimales, Enter para finalizar)\n";
    while (true) {
        monto = "";
        bool tienePunto = false;
        int decimales = 0;
        while (true) {
            c = _getch();
            if (c == 13) { // Enter
                cout << endl;
                break;
            }
            if (c == 8) { // Backspace
                if (!monto.empty()) {
                    if (monto.back() == '.') {
                        tienePunto = false;
                        decimales = 0;
                    } else if (tienePunto) {
                        decimales--;
                    }
                    monto.pop_back();
                    cout << "\b \b";
                }
            } else if ((c >= '0' && c <= '9')) {
                if (tienePunto) {
                    if (decimales < 2) {
                        monto += c;
                        decimales++;
                        cout << c;
                    }
                } else {
                    monto += c;
                    cout << c;
                }
            } else if (c == '.' && !tienePunto && !monto.empty()) {
                monto += c;
                tienePunto = true;
                decimales = 0;
                cout << c;
            }
        }
        // Validar formato y que sea mayor a 0
        try {
            double val = std::stod(monto);
            // Validar máximo 2 decimales
            size_t punto = monto.find('.');
            if (val > 0 && (punto == std::string::npos || monto.size() - punto - 1 <= 2)) {
                return monto;
            } else {
                cout << "El monto debe ser mayor que 0 y tener maximo 2 decimales. Intente de nuevo: ";
            }
        } catch (...) {
            cout << "Monto invalido. Intente de nuevo: ";
        }
    }
}

bool Validar::validarCedulaEcuatoriana(const std::string& cedula) {
    if (cedula.length() != 10) return false;

    for (char c : cedula) {
        if (!std::isdigit(c)) return false;
    }

    int provincia = std::stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) return false;

    int tercerDigito = cedula[2] - '0';
    if (tercerDigito > 5) return false;

    int suma = 0;
    for (int i = 0; i < 9; ++i) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int digitoVerificadorCalculado = (10 - (suma % 10)) % 10;
    int digitoVerificadorReal = cedula[9] - '0';

    return digitoVerificadorCalculado == digitoVerificadorReal;
}
std::string Validar::pedirIdCuenta() {
    std::string id;
    do {
        std::cout << "Ingrese el ID de la cuenta: ";
        id = "";
        char c;
        while (true) {
            c = _getch();
            if (c == 13) { // Enter
                std::cout << std::endl;
                break;
            }
            else if (c == 8) { // Backspace
                if (!id.empty()) {
                    id.pop_back();
                    std::cout << "\b \b";
                }
            }
            // Permitir letras y números
            else if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                id += c;
                std::cout << c;
            }
        }
        if (id.empty()) {
            std::cout << "El ID no puede estar vacio. Intente de nuevo." << std::endl;
        }
    } while (id.empty());
    return id;
}

Fecha Validar::pedirFecha() {
    std::string diaStr, mesStr, anioStr;
    int dia, mes, anio;
    while (true) {
        // Día
        std::cout << "Ingrese dia: ";
        diaStr = "";
        char c;
        while (true) {
            c = _getch();
            if (c == 13) { std::cout << std::endl; break; }
            else if (c == 8) {
                if (!diaStr.empty()) { diaStr.pop_back(); std::cout << "\b \b"; }
            }
            else if (c >= '0' && c <= '9' && diaStr.length() < 2) {
                diaStr += c; std::cout << c;
            }
        }
        // Mes
        std::cout << "Ingrese mes: ";
        mesStr = "";
        while (true) {
            c = _getch();
            if (c == 13) { std::cout << std::endl; break; }
            else if (c == 8) {
                if (!mesStr.empty()) { mesStr.pop_back(); std::cout << "\b \b"; }
            }
            else if (c >= '0' && c <= '9' && mesStr.length() < 2) {
                mesStr += c; std::cout << c;
            }
        }
        // Año
        std::cout << "Ingrese anio: ";
        anioStr = "";
        while (true) {
            c = _getch();
            if (c == 13) { std::cout << std::endl; break; }
            else if (c == 8) {
                if (!anioStr.empty()) { anioStr.pop_back(); std::cout << "\b \b"; }
            }
            else if (c >= '0' && c <= '9' && anioStr.length() < 4) {
                anioStr += c; std::cout << c;
            }
        }
        // Validación básica
        if (!diaStr.empty() && !mesStr.empty() && !anioStr.empty()) {
            dia = std::stoi(diaStr);
            mes = std::stoi(mesStr);
            anio = std::stoi(anioStr);
            if (Fecha::validarFecha(dia, mes, anio)) {
                break; // Fecha válida, salimos del ciclo
            } else {
                std::cout << "Fecha invalida. Intente de nuevo." << std::endl;
            }
        } else {
            std::cout << "La fecha no puede estar vacia. Intente de nuevo." << std::endl;
        }
    }
    return Fecha(dia, mes, anio); // Solo retornas aquí, cuando la fecha es válida
}

std::pair<Fecha, Fecha> Validar::pedirRangoFecha() {
    Fecha fechaInicio, fechaFin;
    while (true) {
        std::cout << "Ingrese la fecha de inicio:" << std::endl;
        fechaInicio = pedirFecha();

        std::cout << "Ingrese la fecha de fin:" << std::endl;
        fechaFin = pedirFecha();

        // Validar que fechaFin >= fechaInicio
        bool valido = 
            (fechaFin.getAnio() > fechaInicio.getAnio()) ||
            (fechaFin.getAnio() == fechaInicio.getAnio() && fechaFin.getMes() > fechaInicio.getMes()) ||
            (fechaFin.getAnio() == fechaInicio.getAnio() && fechaFin.getMes() == fechaInicio.getMes() && fechaFin.getDia() >= fechaInicio.getDia());

        if (valido) {
            break;
        } else {
            std::cout << "La fecha de fin no puede ser menor que la fecha de inicio. Intente de nuevo." << std::endl;
        }
    }
    return std::make_pair(fechaInicio, fechaFin);
}

