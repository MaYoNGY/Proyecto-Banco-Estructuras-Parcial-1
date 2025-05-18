/***********************************************************************
 * Module:  Transaccion.cpp
 * Author:  camev
 * Modified: sábado, 17 de mayo de 2025 21:31:51
 * Purpose: Implementation of the class Transaccion
 ***********************************************************************/

#include "Transaccion.h"

////////////////////////////////////////////////////////////////////////
// Name:       Transaccion::getTipoTransaccion()
// Purpose:    Implementation of Transaccion::getTipoTransaccion()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Transaccion::getTipoTransaccion(void)
{
   return tipoTransaccion;
}

////////////////////////////////////////////////////////////////////////
// Name:       Transaccion::setTipoTransaccion(std::string newTipoTransaccion)
// Purpose:    Implementation of Transaccion::setTipoTransaccion()
// Parameters:
// - newTipoTransaccion
// Return:     void
////////////////////////////////////////////////////////////////////////

void Transaccion::setTipoTransaccion(std::string newTipoTransaccion)
{
   tipoTransaccion = newTipoTransaccion;
}

////////////////////////////////////////////////////////////////////////
// Name:       Transaccion::getMonto()
// Purpose:    Implementation of Transaccion::getMonto()
// Return:     double
////////////////////////////////////////////////////////////////////////

double Transaccion::getMonto(void)
{
   return monto;
}

////////////////////////////////////////////////////////////////////////
// Name:       Transaccion::setMonto(double newMonto)
// Purpose:    Implementation of Transaccion::setMonto()
// Parameters:
// - newMonto
// Return:     void
////////////////////////////////////////////////////////////////////////

void Transaccion::setMonto(double newMonto)
{
   monto = newMonto;
}

////////////////////////////////////////////////////////////////////////
// Name:       Transaccion::getFecha()
// Purpose:    Implementation of Transaccion::getFecha()
// Return:     Fecha
////////////////////////////////////////////////////////////////////////

Fecha Transaccion::getFecha(void)
{
   return fecha;
}

////////////////////////////////////////////////////////////////////////
// Name:       Transaccion::setFecha(Fecha newFecha)
// Purpose:    Implementation of Transaccion::setFecha()
// Parameters:
// - newFecha
// Return:     void
////////////////////////////////////////////////////////////////////////

void Transaccion::setFecha(Fecha newFecha)
{
   fecha = newFecha;
}

////////////////////////////////////////////////////////////////////////
// Name:       Transaccion::Transaccion()
// Purpose:    Implementation of Transaccion::Transaccion()
// Return:     
////////////////////////////////////////////////////////////////////////

Transaccion::Transaccion()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       Transaccion::~Transaccion()
// Purpose:    Implementation of Transaccion::~Transaccion()
// Return:     
////////////////////////////////////////////////////////////////////////

Transaccion::~Transaccion()
{
   // TODO : implement
}