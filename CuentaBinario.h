#pragma once
#include <fstream>
#include <iostream>
#include "ListaCuenta.h"
#include "Cuenta.h"
#include "NodoCuenta.h"

class CuentaBinario {
public:
    static void generarArchivoBinario(const ListaCuenta<Cuenta>& lista) {
        // Verificar si el archivo existe. Si no existe, lo creamos vacío.
        std::ifstream archivoExistente("cuentas.bin", std::ios::binary);
        if (!archivoExistente) {
            std::ofstream crearArchivo("cuentas.bin", std::ios::binary);
            if (!crearArchivo) {
                std::cout << "No se pudo crear el archivo binario." << std::endl;
                return;
            }
            crearArchivo.close();
        } else {
            archivoExistente.close();
        }

        // Ahora escribimos en el archivo
        std::ofstream archivo("cuentas.bin", std::ios::binary | std::ios::out | std::ios::app);
        if (!archivo) {
            std::cout << "No se pudo abrir el archivo binario." << std::endl;
            return;
        }

        auto actual = lista.getNodoCabeza();
        if (actual) {
            NodoCuenta<Cuenta>* inicio = actual;
            do {
                const Cuenta& cuenta = actual->getDato();
                archivo.write(reinterpret_cast<const char*>(&cuenta), sizeof(Cuenta));
                actual = actual->getSiguiente();
            } while (actual && actual != inicio);
        }

        archivo.close();
    }
};
