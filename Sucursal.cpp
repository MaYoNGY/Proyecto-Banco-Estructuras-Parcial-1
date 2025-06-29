#include "Sucursal.h"
#include <iostream>
#include "Sucursal.h"
#include <iostream>

// Puedes agregar métodos adicionales si necesitas lógica específica para la sucursal.
// Por ahora, la clase solo tiene getters y setters simples definidos en el header (inline).



// Ejemplo de función para mostrar información de la sucursal:
void mostrarSucursal(const Sucursal& sucursal) {
    std::cout << "Sucursal: " << sucursal.getNombre() << std::endl;
    std::cout << "Dirección: " << sucursal.getDireccion() << std::endl;
    std::cout << "Código: " << sucursal.getCodigo() << std::endl;
}