#include "Validar.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>


int ingresoDatos(char mensaje[20])
{
    char c;
    int valor, i = 0;
    char dato[10];
    printf("\n%s", mensaje);
    while (true) {
        c = getch();

        if (c == 13) {
            break;
        }
        else if (c == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (c >= '0' && c <= '9') {
            if (i < 9) { //
                dato[i++] = c;
                printf("%c", c);
            }
        }
    }

    dato[i] = '\0';
    valor = atoi(dato);
    return valor;
}

bool validarCedulaEcuatoriana(const std::string& cedula) {
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