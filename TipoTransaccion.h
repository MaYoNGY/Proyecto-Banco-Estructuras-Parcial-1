#ifndef __TIPOTRANSACCION_H
#define __TIPOTRANSACCION_H
#include <string>

class TipoTransaccion
{
private:
    std::string tipo; // Solo puede ser "DEPOSITO" o "RETIRO"

public:
    TipoTransaccion(const std::string& tipo); // Espera solo "DEPOSITO" o "RETIRO"
    ~TipoTransaccion();
    std::string getTipo() const;
    bool esDeposito() const;
    bool esRetiro() const;
};

#endif