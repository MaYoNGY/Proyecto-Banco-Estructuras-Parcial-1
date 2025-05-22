#include "ContrasenaUsuario.h"
#include <random>
#include <string>
#include <iostream>

std::string ContrasenaUsuario::generarContrasenaBancaria() {
   const std::string numeros = "0123456789";
    const std::string letrasMayus = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string letrasMinus = "abcdefghijklmnopqrstuvwxyz";
    const std::string simbolos = "!@#$%^&*()-_=+[]{}|;:,.<>?";

    std::random_device rd;
    std::mt19937 generador(rd());
    std::uniform_int_distribution<> distNum(0, numeros.size() - 1);
    std::uniform_int_distribution<> distMayus(0, letrasMayus.size() - 1);
    std::uniform_int_distribution<> distMinus(0, letrasMinus.size() - 1);
    std::uniform_int_distribution<> distSimbolo(0, simbolos.size() - 1);
    std::uniform_int_distribution<> distPos(0, 9); // Para insertar en una posición aleatoria

    std::string contrasena;

    // Agrega 3 números
    for (int i = 0; i < 3; ++i) {
        char c = numeros[distNum(generador)];
        int pos = contrasena.empty() ? 0 : distPos(generador) % (contrasena.length() + 1);
        contrasena.insert(pos, 1, c);
    }

    // Agrega 3 letras minúsculas
    for (int i = 0; i < 3; ++i) {
        char c = letrasMinus[distMinus(generador)];
        int pos = distPos(generador) % (contrasena.length() + 1);
        contrasena.insert(pos, 1, c);
    }

    // Agrega 3 letras mayúsculas
    for (int i = 0; i < 3; ++i) {
        char c = letrasMayus[distMayus(generador)];
        int pos = distPos(generador) % (contrasena.length() + 1);
        contrasena.insert(pos, 1, c);
    }

    // Agrega 1 símbolo especial
    char simbolo = simbolos[distSimbolo(generador)];
    int pos = distPos(generador) % (contrasena.length() + 1);
    contrasena.insert(pos, 1, simbolo);

    return contrasena;
}
