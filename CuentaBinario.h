#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Cuenta.h"
#include "Persona.h"
#include "TipoCuenta.h"
#include "Fecha.h"

class CuentaBinario {
public:
    
    static void txtACuentasBinario(const std::string& archivoTxt, const std::string& archivoBinario) {
        std::ifstream inFile(archivoTxt);
        if (!inFile.is_open()) {
            std::cerr << "Error al abrir el archivo de texto: " << archivoTxt << std::endl;
            return;
        }

        std::ofstream outFile(archivoBinario, std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Error al abrir el archivo binario: " << archivoBinario << std::endl;
            return;
        }

        std::string linea;
        while (std::getline(inFile, linea)) {
            if (linea.empty()) continue;

            std::istringstream iss(linea);
            std::string idCuenta, cedula, nombre, apellido, tipo, contrasena;
            
            double saldo;
            int dia, mes, anio;

            Fecha fechaCreacion(dia, mes, anio);
            TipoCuenta tipoCuenta(tipo);
            Persona persona(cedula, nombre, apellido);
            Cuenta cuenta(idCuenta, persona, saldo, tipoCuenta, contrasena, fechaCreacion);

            outFile.write(reinterpret_cast<const char*>(&cuenta), sizeof(Cuenta));
        }

        inFile.close();
        outFile.close();
    }
};
