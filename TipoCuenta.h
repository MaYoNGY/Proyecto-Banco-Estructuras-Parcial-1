#ifndef __TIPOCUENTA_H
#define __TIPOCUENTA_H
#include <string>

class TipoCuenta
{
private:
    std::string tipo; // Solo puede ser "ahorro" o "corriente"

public:
    TipoCuenta(); // Constructor por defecto
    TipoCuenta(const std::string& tipo); // Espera solo "ahorro" o "corriente"
    ~TipoCuenta();
    std::string getTipo() const;
    bool esAhorro() const;
    bool esCorriente() const;
};

#endif