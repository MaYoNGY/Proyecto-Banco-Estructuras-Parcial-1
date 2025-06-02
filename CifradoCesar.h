#ifndef CIFRADOCESAR_H
#define CIFRADOCESAR_H

#include <fstream>
#include <string>

class CifradoCesar {
public:
    static void cifrarArchivo(const std::string& archivoEntrada, const std::string& archivoSalida, int clave) {
        std::ifstream in(archivoEntrada, std::ios::binary);
        std::ofstream out(archivoSalida, std::ios::binary);
        if (!in) {
        std::cerr << "No se pudo abrir el archivo de entrada: " << archivoEntrada << std::endl;
        return;
        }
        if (!out) {
        std::cerr << "No se pudo abrir el archivo de salida: " << archivoSalida << std::endl;
        return;
        }
        char c;
        while (in.get(c)) {
            out.put(c + clave);
        }
        in.close();
        out.close();
    }

    static void descifrarArchivo(const std::string& archivoEntrada, const std::string& archivoSalida, int clave) {
        std::ifstream in(archivoEntrada, std::ios::binary);
        std::ofstream out(archivoSalida, std::ios::binary);
        if (!in) {
        std::cerr << "No se pudo abrir el archivo de entrada: " << archivoEntrada << std::endl;
        return;
        }
        if (!out) {
        std::cerr << "No se pudo abrir el archivo de salida: " << archivoSalida << std::endl;
        return;
        }
        char c;
        while (in.get(c)) {
            out.put(c - clave);
        }
        in.close();
        out.close();
    }
};

#endif