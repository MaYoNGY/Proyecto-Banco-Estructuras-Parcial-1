#include "Anio.h"
#include <iostream>
#include <ctime> // Agrega esta línea


int Anio::getAnio(void)
{
   return anio;
}

void Anio::setAnio(int newAnio)
{
   anio = newAnio;
}

void Anio::iniciar(void)
{
   // Inicializa el año actual
   time_t t = time(nullptr);
   tm* now = localtime(&t);
   anio = now->tm_year + 1900; // Ajuste para obtener el año actual
   std::cout << "Año inicializado: " << anio << std::endl;
}

void Anio::finalize(void)
{
    // Si necesitas liberar recursos antes de destruir el objeto
    if (ptr != nullptr) {
        delete ptr;
        ptr = nullptr;
    }
}
