#ifndef SIMULADOR_SOBREGIRO_H
#define SIMULADOR_SOBREGIRO_H

#include <iostream>
#include <iomanip>
#include "Validar.h"
#include "ListaCuenta.h"
#include "Cuenta.h"

class SimuladorSobregiro {
public:
    static void calcularPagoSobregiro(Cuenta* cuenta) {
        system("cls");

        if (!cuenta) {
            std::cout << "Cuenta no válida." << std::endl;
            return;
        }

        double saldo = cuenta->getSaldo();
        if (saldo >= 0) {
            std::cout << "La cuenta no tiene sobregiro (saldo negativo)." << std::endl;
            return;
        }

        double montoSobregiro = -saldo; // El saldo es negativo
        int plazoMeses = Validar::pedirPlazoMeses();
        double tasaAnual = Validar::pedirTasaAnual();
        std::cout << "Monto de sobregiro: $" << montoSobregiro << std::endl;

        double r = tasaAnual / 12.0 / 100.0; // tasa mensual

        // Búsqueda binaria para encontrar la cuota mínima
        double left = 0.0, right = montoSobregiro * 2, cuotaMinima = right;
        for (int iter = 0; iter < 100; ++iter) {
            double mid = (left + right) / 2.0;
            double saldoTemp = montoSobregiro;
            for (int i = 0; i < plazoMeses; ++i) {
                saldoTemp = saldoTemp * (1 + r) - mid;
            }
            if (saldoTemp <= 0) {
                cuotaMinima = mid;
                right = mid;
            } else {
                left = mid;
            }
        }

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "La cuota mensual minima para saldar el sobregiro es: $" << cuotaMinima << std::endl;
        std::cout << "Total pagado: $" << cuotaMinima * plazoMeses << std::endl;
        std::cout << "Intereses pagados: $" << (cuotaMinima * plazoMeses - montoSobregiro) << std::endl;
    }
};

#endif