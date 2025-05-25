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
