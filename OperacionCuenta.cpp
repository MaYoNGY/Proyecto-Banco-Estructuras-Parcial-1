#include "OperacionCuenta.h"
#include <iostream>
#include <chrono>

OperacionCuenta::OperacionCuenta(Cuenta& c) 
    : cuenta(c), tieneSobregiro(false), montoSobregiro(0), fechaInicioSobregiro(0) {}

bool OperacionCuenta::validarMonto(double monto) {
    return monto > 0;
}

bool OperacionCuenta::depositar(double monto) {
    if (!validarMonto(monto)) {
        std::cout << "Monto a depositar debe ser mayor que 0.\n";
        return false;
    }
    if (monto > 5000) {
        std::cout << "No puede depositar más de $5000 en un solo depósito.\n";
        return false;
    }
    cuenta.setSaldo(cuenta.getSaldo() + monto);
    std::cout << "Depósito exitoso. Nuevo saldo: $" << cuenta.getSaldo() << "\n";
    return true;
}

bool OperacionCuenta::retirar(double monto) {
    if (!validarMonto(monto)) {
        std::cout << "Monto a retirar debe ser mayor que 0.\n";
        return false;
    }
    if (monto > 1000) {
        std::cout << "No puede retirar más de $1000 en un solo retiro.\n";
        return false;
    }

    if (cuenta.getTipo().esAhorro()) {
        if (cuenta.getSaldo() >= monto) {
            cuenta.setSaldo(cuenta.getSaldo() - monto);
            std::cout << "Retiro exitoso. Nuevo saldo: $" << cuenta.getSaldo() << "\n";
            return true;
        } else {
            std::cout << "Saldo insuficiente en cuenta de ahorros. No puede retirar esa cantidad.\n";
            return false;
        }
    } else if (cuenta.getTipo().esCorriente()) {
        if (cuenta.getSaldo() >= monto) {
            cuenta.setSaldo(cuenta.getSaldo() - monto);
            std::cout << "Retiro exitoso. Nuevo saldo: $" << cuenta.getSaldo() << "\n";
            return true;
        } else {
            double sobregiroPermitido = 500;
            double montoDisponible = cuenta.getSaldo() + (tieneSobregiro ? (sobregiroPermitido - montoSobregiro) : sobregiroPermitido);

            if (monto <= montoDisponible) {
                std::cout << "Saldo insuficiente, desea usar sobregiro? (max $500)\n(S/N): ";
                char opcion;
                std::cin >> opcion;
                if (opcion == 'S' || opcion == 's') {
                    double usoSobregiro = monto - cuenta.getSaldo();
                    iniciarSobregiro(usoSobregiro);
                    cuenta.setSaldo(0);
                    std::cout << "Sobregiro aprobado por $" << usoSobregiro << ". Tiene 5 días para pagar con 0.05% diario de interés.\n";
                    return true;
                } else {
                    std::cout << "Retiro cancelado.\n";
                    return false;
                }
            } else {
                std::cout << "Sobregiro máximo $500 superado. Retiro cancelado.\n";
                return false;
            }
        }
    }
    return false;
}

void OperacionCuenta::iniciarSobregiro(double monto) {
    tieneSobregiro = true;
    montoSobregiro += monto;
    fechaInicioSobregiro = std::time(nullptr);
}

// Sobrecarga operador += para depósito
OperacionCuenta& OperacionCuenta::operator+=(double monto) {
    depositar(monto);
    return *this;
}

// Sobrecarga operador -= para retiro
OperacionCuenta& OperacionCuenta::operator-=(double monto) {
    retirar(monto);
    return *this;
}

// Operadores que no modifican saldo, solo calculan
double OperacionCuenta::operator+(double monto) {
    return cuenta.getSaldo() + monto;
}

double OperacionCuenta::operator-(double monto) {
    return cuenta.getSaldo() - monto;
}

// Comparadores con saldo
bool OperacionCuenta::operator==(double monto) {
    return cuenta.getSaldo() == monto;
}

bool OperacionCuenta::operator!=(double monto) {
    return cuenta.getSaldo() != monto;
}

// Sobrecarga operador << para imprimir estado
std::ostream& operator<<(std::ostream& os, const OperacionCuenta& op) {
    os << "Cuenta ID: " << op.cuenta.getIdCuenta()
       << ", Tipo: " << op.cuenta.getTipo().getTipo()
       << ", Saldo: $" << op.cuenta.getSaldo();
    if (op.tieneSobregiro) {
        os << ", Sobregiro pendiente: $" << op.montoSobregiro;
    }
    return os;
}

void OperacionCuenta::calcularInteresSobregiro() {
    if (!tieneSobregiro) return;

    std::time_t ahora = std::time(nullptr);
    int diasPasados = static_cast<int>(std::difftime(ahora, fechaInicioSobregiro) / (60 * 60 * 24));

    double interes = 0.0;
    if (diasPasados <= 5) {
        interes = montoSobregiro * 0.0005 * diasPasados; 
        std::cout << "Interés sobregiro (periodo 5 días): $" << interes << "\n";
    } else {
        int diasMora = diasPasados - 5;
        double interesNormal = montoSobregiro * 0.0005 * 5;
        double interesMora = montoSobregiro * 0.001 * diasMora;
        interes = interesNormal + interesMora;
        std::cout << "Interés sobregiro: $" << interesNormal << " + Interés mora por " << diasMora << " días: $" << interesMora << " Total: $" << interes << "\n";
    }
}

void OperacionCuenta::aplicarInteresAhorros() {
    if (!cuenta.getTipo().esAhorro()) return;

    double interesMensual = cuenta.getSaldo() * 0.001; // 0.1%
    cuenta.setSaldo(cuenta.getSaldo() + interesMensual);
    std::cout << "Interés mensual aplicado: $" << interesMensual << ". Nuevo saldo: $" << cuenta.getSaldo() << "\n";
}

void OperacionCuenta::mostrarEstadoSobregiro() const {
    if (tieneSobregiro) {
        std::cout << "Actualmente tiene sobregiro por $" << montoSobregiro << ". Debe pagar en máximo 5 días para evitar intereses de mora.\n";
    } else {
        std::cout << "No tiene sobregiro activo.\n";
    }
}

void OperacionCuenta::pagarSobregiro(double monto) {
    if (!tieneSobregiro) {
        std::cout << "No tiene sobregiro activo.\n";
        return;
    }
    if (monto >= montoSobregiro) {
        std::cout << "Sobregiro pagado en su totalidad.\n";
        montoSobregiro = 0;
        tieneSobregiro = false;
        cuenta.setSaldo(cuenta.getSaldo() + (monto - montoSobregiro));
    } else {
        montoSobregiro -= monto;
        std::cout << "Pago parcial de sobregiro realizado. Queda pendiente: $" << montoSobregiro << "\n";
    }
    
}
