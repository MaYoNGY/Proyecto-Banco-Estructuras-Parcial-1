#ifndef OPERACIONCUENTA_H
#define OPERACIONCUENTA_H

#include "Cuenta.h"
#include <ctime>
#include <iostream>

class OperacionCuenta {
private:
    Cuenta& cuenta;
    bool tieneSobregiro;
    double montoSobregiro;
    std::time_t fechaInicioSobregiro;

    // Para control de sobregiros mensuales
    int sobregirosEsteMes;
    int mesUltimoSobregiro;
    int anioUltimoSobregiro;

public:
    OperacionCuenta(Cuenta& c);

    // Métodos normales
    bool depositar(double monto);
    bool retirar(double monto);

    // Sobrecarga operadores que modifican saldo
    OperacionCuenta& operator+=(double monto); // depósito
    OperacionCuenta& operator-=(double monto); // retiro

    // Sobrecarga operadores que no modifican saldo (solo calculan)
    double operator+(double monto);  // saldo + monto
    double operator-(double monto);  // saldo - monto

    // Comparadores con saldo
    bool operator==(double monto);
    bool operator!=(double monto);

    // Método para imprimir estado con cout << operacion
    friend std::ostream& operator<<(std::ostream& os, const OperacionCuenta& op);

    // Otros métodos
    void calcularInteresSobregiro();
    void aplicarInteresAhorros();

    void mostrarEstadoSobregiro() const;
    void pagarSobregiro(double monto);

private:
    bool validarMonto(double monto);
    void iniciarSobregiro(double monto);
};

#endif
