#include "OperacionCuenta.h"
#include "Cuenta.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>

static const int LIMITE_SOBREGIROS_MES = 3;

OperacionCuenta::OperacionCuenta(Cuenta& c) 
    : cuenta(c), fechaInicioSobregiro(0),
      sobregirosEsteMes(0), mesUltimoSobregiro(-1), anioUltimoSobregiro(-1) {}

bool OperacionCuenta::validarMonto(double monto) {
    return monto > 0;
}

bool OperacionCuenta::depositar(double monto) {
    if (!validarMonto(monto)) {
        std::cout << "Monto a depositar debe ser mayor que 0.\n";
        return false;
    }
    if (monto > 5000) {
        std::cout << "No puede depositar mas de $5000 en un solo deposito.\n";
        return false;
    }

    double saldo = cuenta.getSaldo();
    if (saldo < 0) {
        double montoSobregiroPendiente = -saldo;
        if (monto >= montoSobregiroPendiente) {
            cuenta.setSaldo(monto - montoSobregiroPendiente);
            std::cout << "Sobregiro pagado en su totalidad. Nuevo saldo: $" << cuenta.getSaldo() << "\n";
        } else {
            cuenta.setSaldo(saldo + monto);
            std::cout << "Pago parcial de sobregiro realizado. Queda pendiente: $" << -cuenta.getSaldo() << "\n";
        }
    } else {
        cuenta.setSaldo(saldo + monto);
        std::cout << "Deposito exitoso. Nuevo saldo: $" << cuenta.getSaldo() << "\n";
    }
    return true;
}

bool OperacionCuenta::retirar(double monto) {
    if (!validarMonto(monto)) {
        std::cout << "Monto a retirar debe ser mayor que 0.\n";
        return false;
    }
    if (monto > 1000) {
        std::cout << "No puede retirar mas de $1000 en un solo retiro.\n";
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
    }
    else if (cuenta.getTipo().esCorriente()) {
        if (cuenta.getSaldo() >= monto) {
            cuenta.setSaldo(cuenta.getSaldo() - monto);
            std::cout << "Retiro exitoso. Nuevo saldo: $" << cuenta.getSaldo() << "\n";
            return true;
        } else {
            double sobregiroPermitido = 500;
            double montoDisponible = cuenta.getSaldo() + sobregiroPermitido;

            // Control de límite mensual antes de ofrecer sobregiro
            std::time_t ahora = std::time(nullptr);
            std::tm* fecha = std::localtime(&ahora);
            int mesActual = fecha->tm_mon;
            int anioActual = fecha->tm_year;
            if (mesUltimoSobregiro != mesActual || anioUltimoSobregiro != anioActual) {
                sobregirosEsteMes = 0;
                mesUltimoSobregiro = mesActual;
                anioUltimoSobregiro = anioActual;
            }
            if (sobregirosEsteMes >= LIMITE_SOBREGIROS_MES) {
                std::cout << "Ha alcanzado el limite de " << LIMITE_SOBREGIROS_MES << " sobregiros este mes. Retiro cancelado.\n";
                return false;
            }

            if (monto <= montoDisponible) {
                std::cout << "Saldo insuficiente, desea usar sobregiro? (max $500)\n(S/N): ";
                char opcion;
                std::cin >> opcion;
                if (opcion == 'S' || opcion == 's') {
                    double usoSobregiro = monto - cuenta.getSaldo();
                    iniciarSobregiro(usoSobregiro);
                    if (sobregirosEsteMes <= LIMITE_SOBREGIROS_MES) {
                        cuenta.setSaldo(cuenta.getSaldo() - monto);
                        std::cout << "Sobregiro aprobado por $" << usoSobregiro << ". Tiene 5 dias para pagar con 0.05% diario de interes.\n";
                    }
                    return true;
                } else {
                    std::cout << "Retiro cancelado.\n";
                    return false;
                }
            } else {
                std::cout << "Sobregiro maximo $500 superado. Retiro cancelado.\n";
                return false;
            }
        }
    }
    return false;
}

bool OperacionCuenta::retirarAhorroSimple(double monto) {
    double tolerancia = 0.01;
    if (monto <= 0) {
        std::cout << "Monto a retirar debe ser mayor que 0.\n";
        return false;
    }
    if (monto > 1000) {
        std::cout << "No puede retirar mas de $1000 en un solo retiro.\n";
        return false;
    }
    if (cuenta.getSaldo() + tolerancia >= monto) {
        cuenta.setSaldo(cuenta.getSaldo() - monto);
        std::cout << "Retiro exitoso. Nuevo saldo: $" << cuenta.getSaldo() << "\n";
        return true;
    } else {
        std::cout << "Saldo insuficiente en cuenta de ahorros. No puede retirar esa cantidad.\n";
        return false;
    }
}

void OperacionCuenta::iniciarSobregiro(double /*monto*/) {
    // Control de límite mensual
    std::time_t ahora = std::time(nullptr);
    std::tm* fecha = std::localtime(&ahora);
    int mesActual = fecha->tm_mon;
    int anioActual = fecha->tm_year;

    if (mesUltimoSobregiro != mesActual || anioUltimoSobregiro != anioActual) {
        sobregirosEsteMes = 0;
        mesUltimoSobregiro = mesActual;
        anioUltimoSobregiro = anioActual;
    }

    if (sobregirosEsteMes >= LIMITE_SOBREGIROS_MES) {
        std::cout << "Ha alcanzado el limite de " << LIMITE_SOBREGIROS_MES << " sobregiros este mes.\n";
        return;
    }

    fechaInicioSobregiro = ahora;
    sobregirosEsteMes++;
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

// Sobrecarga operador + para simular saldo tras sumar monto (no modifica saldo real)
double OperacionCuenta::operator+(double monto) {
    return cuenta.getSaldo() + monto;
}

// Sobrecarga operador - para simular saldo tras restar monto (no modifica saldo real)
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
    os << "Cuenta ID: " << op.cuenta.getIdCuentaStr()
       << ", Tipo: " << op.cuenta.getTipo().getTipo()
       << ", Saldo: $" << op.cuenta.getSaldo();
    if (op.cuenta.getSaldo() < 0) {
        os << ", Sobregiro pendiente: $" << -op.cuenta.getSaldo();
    }
    return os;
}

void OperacionCuenta::calcularInteresSobregiro() {
    double saldo = cuenta.getSaldo();
    if (saldo >= 0) return;

    std::time_t ahora = std::time(nullptr);

    if (fechaInicioSobregiro <= 0) {
        std::cout << "No se puede calcular interes: fecha de inicio de sobregiro desconocida.\n";
        return;
    }

    int diasPasados = static_cast<int>(std::difftime(ahora, fechaInicioSobregiro) / (60 * 60 * 24));
    if (diasPasados < 0) diasPasados = 0;

    double montoSobregiro = -saldo;
    double interes = 0.0;
    if (diasPasados <= 5) {
        interes = montoSobregiro * 0.0005 * diasPasados; 
        std::cout << "Interes sobregiro (periodo 5 dias): $" << interes << "\n";
    } else {
        int diasMora = diasPasados - 5;
        double interesNormal = montoSobregiro * 0.0005 * 5;
        double interesMora = montoSobregiro * 0.001 * diasMora;
        interes = interesNormal + interesMora;
        std::cout << "Interes sobregiro: $" << interesNormal << " + Interes mora por " << diasMora << " dias: $" << interesMora << " Total: $" << interes << "\n";
    }
}

void OperacionCuenta::aplicarInteresAhorros() {
    if (!cuenta.getTipo().esAhorro()) return;

    double interesMensual = cuenta.getSaldo() * 0.001; // 0.1%
    cuenta.setSaldo(cuenta.getSaldo() + interesMensual);
    std::cout << "Interes mensual aplicado: $" << interesMensual << ". Nuevo saldo: $" << cuenta.getSaldo() << "\n";
}

void OperacionCuenta::mostrarEstadoSobregiro() const {
    if (cuenta.getSaldo() < 0) {
        std::cout << "Actualmente tiene sobregiro por $" << -cuenta.getSaldo() << ". Debe pagar en maximo 5 dias para evitar intereses de mora.\n";
    } else {
        std::cout << "No tiene sobregiro activo.\n";
    }
}

void OperacionCuenta::pagarSobregiro(double monto) {
    double saldo = cuenta.getSaldo();
    if (saldo >= 0) {
        std::cout << "No tiene sobregiro activo.\n";
        return;
    }
    double montoSobregiro = -saldo;
    double tolerancia = 0.01;

    if (monto > montoSobregiro + tolerancia) {
        std::cout << "No puede pagar mas del monto pendiente de sobregiro. Pendiente: $" << montoSobregiro << "\n";
        return;
    }
    cuenta.setSaldo(saldo + monto);

    if (cuenta.getSaldo() >= -tolerancia) {
        std::cout << "Sobregiro pagado en su totalidad.\n";
        cuenta.setSaldo(std::max(0.0, cuenta.getSaldo()));
    } else {
        double pendiente = -cuenta.getSaldo();
        std::cout << "Pago parcial de sobregiro realizado. Queda pendiente: $" << pendiente << "\n";
    }
}