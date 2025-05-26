#ifndef __LISTACUENTA_H
#define __LISTACUENTA_H
#include <iostream>
#include <string>
#include "NodoCuenta.h"
#include <fstream>
#include <sstream>
#include "Cuenta.h"
#include "Persona.h"
#include "TipoCuenta.h"
#include "Fecha.h"

template <typename T>
class ListaCuenta
{
private:
   NodoCuenta<T>* cabeza;
   NodoCuenta<T>* cola;
public:
   ListaCuenta() : cabeza(nullptr), cola(nullptr) {}

   ~ListaCuenta() {
      NodoCuenta<T>* actual = cabeza;
      while (actual) {
         NodoCuenta<T>* temp = actual;
         actual = actual->getSiguiente();
         delete temp;
      }
   }

   void insertarCuenta(const T& cuenta) {
      NodoCuenta<T>* nuevo = new NodoCuenta<T>(cuenta);
      if (!cabeza) {
         cabeza = cola = nuevo;
         cabeza->setSiguiente(cabeza);
         cabeza->setAnterior(cabeza);
      } else {
         cola->setSiguiente(nuevo);
         nuevo->setAnterior(cola);
         nuevo->setSiguiente(cabeza);
         cola = nuevo;
         cabeza->setAnterior(cola);
      }
   }

   NodoCuenta<T>* buscarCuenta(int idCuenta, const std::string& nombre) { /// modificar para que busque el id 
       if (!cabeza) {
         std::cout << "No hay cuentas en la lista." << std::endl;
            return nullptr;
      }
       NodoCuenta<T>* actual = cabeza;
       do {
           if (actual->getDato().getIdCuenta() == idCuenta && actual->getDato().getNombre() == nombre) {
               return actual;
           }
           actual = actual->getSiguiente();
       } while (actual != cabeza);
       return nullptr;
   }

   void mostrarCuentas() const {
      if (!cabeza) {
         std::cout << "No hay cuentas en la lista." << std::endl;
         return;
      }
      NodoCuenta<T>* actual = cabeza;
      do {
        std::cout << "ID: " << actual->getDato().getIdCuenta()
                  << ", Cedula: " << actual->getDato().getCedula()
                  << ", Nombre: " << actual->getDato().getNombre()
                  << ", Apellido: " << actual->getDato().getApellido()
                  << ", Saldo: " << actual->getDato().getSaldo()
                  << ", Tipo: " << actual->getDato().getTipo().getTipo()
                  << std::endl;
        actual = actual->getSiguiente();
    } while (actual != cabeza);
   }

   /*void eliminarCuenta(int idCuenta) {
       if (!cabeza) {
           std::cout << "No hay cuentas en la lista." << std::endl;
           return;
       }

       NodoCuenta<T>* actual = cabeza;
       do {
           if (std::stoi(actual->getDato().getIdCuenta()) == idCuenta) {
               if (actual == cabeza && actual == cola) {
                   // Solo hay un nodo
                   delete actual;
                   cabeza = cola = nullptr;
                   return;
               }
               if (actual == cabeza) {
                   cabeza = cabeza->getSiguiente();
                   cola->setSiguiente(cabeza);
                   cabeza->setAnterior(cola);
               } else if (actual == cola) {
                   cola = cola->getAnterior();
                   cola->setSiguiente(cabeza);
                   cabeza->setAnterior(cola);
               } else {
                   actual->getAnterior()->setSiguiente(actual->getSiguiente());
                   actual->getSiguiente()->setAnterior(actual->getAnterior());
               }
               delete actual;
               return;
           }
           actual = actual->getSiguiente();
       } while (actual != cabeza);
   }*/

    T* buscarCuentaPorCedula(const std::string& cedula) {
        if (!cabeza) return nullptr;
        NodoCuenta<T>* actual = cabeza;
        do {
            if (actual->getDato().getCedula() == cedula) {
                return &(actual->getDato());
            }
            actual = actual->getSiguiente();
        } while (actual != cabeza);
        return nullptr;
    }

    T* buscarCuentaPorCedulaYTipo(const std::string& cedula, const std::string& tipo) {
    if (!cabeza) return nullptr;
    NodoCuenta<T>* actual = cabeza;
    do {
        if (actual->getDato().getCedula() == cedula &&
            actual->getDato().getTipo().getTipo() == tipo) {
            return &(actual->getDato());
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return nullptr;
    }

    int buscarCuentasPorCedulaYContrasena(const std::string& cedula, const std::string& contrasena, Cuenta* cuentasUsuario[2]) {
        int cuentaCount = 0;
        NodoCuenta<Cuenta>* actual = cabeza;
        if (actual) {
            do {
                Cuenta& cuenta = actual->getDato();
                if (cuenta.getCedula() == cedula && cuenta.getContrasena() == contrasena) {
                    if (cuentaCount < 2) {
                        cuentasUsuario[cuentaCount++] = &cuenta;
                    }
                }
                actual = actual->getSiguiente();
            } while (actual != cabeza);
        }
        return cuentaCount;
    }

   // Elimina la cuenta por cédula y tipo (totalmente independiente)
   bool eliminarCuentaPorCedulaYTipo(const std::string& cedula, const std::string& tipo) {
       if (!cabeza) return false;
       NodoCuenta<T>* actual = cabeza;
       
       do {
           if (actual->getDato().getCedula() == cedula &&
               actual->getDato().getTipo().getTipo() == tipo) {
               // Eliminar el nodo actual de la lista circular
               if (actual == cabeza && actual == cola) {
                   delete actual;
                   cabeza = cola = nullptr;
                   return true;
               }
               if (actual == cabeza) {
                   cabeza = cabeza->getSiguiente();
                   cola->setSiguiente(cabeza);
                   cabeza->setAnterior(cola);
               } else if (actual == cola) {
                   cola = cola->getAnterior();
                   cola->setSiguiente(cabeza);
                   cabeza->setAnterior(cola);
               } else {
                   actual->getAnterior()->setSiguiente(actual->getSiguiente());
                   actual->getSiguiente()->setAnterior(actual->getAnterior());
               }
               delete actual;
               return true;
           }
           actual = actual->getSiguiente();
       } while (actual != cabeza);
       return false;
   }

   // Método para obtener el puntero al primer nodo (cabeza)
   NodoCuenta<T>* getNodoCabeza() const {
      return cabeza;
   }

   // Método para guardar todas las cuentas en un archivo txt
   void guardarCuentasEnArchivo(const std::string& nombreArchivo) {
      std::ofstream archivo(nombreArchivo, std::ios::out);
      if (!archivo) {
         std::cerr << "Error al abrir el archivo " << nombreArchivo << " para escritura.\n";
         return;
      }
      NodoCuenta<T>* actual = cabeza;
      if (!actual) {
         archivo.close();
         return;
      }
      do {
         archivo << actual->getDato().getIdCuenta() << " "
                 << actual->getDato().getCedula() << " "
                 << actual->getDato().getNombre() << " "
                 << actual->getDato().getApellido() << " "
                 << actual->getDato().getTipo().getTipo() << " "
                 << actual->getDato().getContrasena() << " "
                 << actual->getDato().getFechaCreacion().getDia() << " "
                 << actual->getDato().getFechaCreacion().getMes() << " "
                 << actual->getDato().getFechaCreacion().getAnio()
                 << std::endl;
         actual = actual->getSiguiente();
      } while (actual != cabeza);
      archivo.close();
   }

   // Limpia la lista antes de cargar para evitar duplicados
   void limpiarLista() {
      NodoCuenta<T>* actual = cabeza;
      if (!actual) return;
      do {
         NodoCuenta<T>* temp = actual;
         actual = actual->getSiguiente();
         delete temp;
      } while (actual != cabeza);
      cabeza = nullptr;
      cola = nullptr;
   }

   // Método robusto para cargar cuentas desde un archivo txt
   void cargarCuentasDesdeArchivo(const std::string& nombreArchivo) {
      std::ifstream archivo(nombreArchivo);
      if (!archivo.is_open()) {
         std::cerr << "Error al abrir el archivo " << nombreArchivo << " para lectura.\n";
         return;
      }

      limpiarLista(); // Limpia la lista antes de cargar

      std::string linea;
      while (std::getline(archivo, linea)) {
         if (linea.empty()) continue;
         std::istringstream iss(linea);
         std::string idCuenta, cedula, nombre, apellido, tipo, contrasena;
         double saldo;
         int dia, mes, anio;

         // Lee los campos en el mismo orden en que se guardaron
         if (!(iss >> idCuenta >> cedula >> nombre >> apellido >>  tipo >> contrasena >> dia >> mes >> anio)) {
            std::cerr << "Error de formato en la línea: " << linea << std::endl;
            continue;
         }

         // Validación básica de datos
         if (idCuenta.empty() || cedula.empty() || nombre.empty() || apellido.empty() || tipo.empty() || contrasena.empty())
            continue;

         Fecha fechaCreacion;
         fechaCreacion.setDia(dia);
         fechaCreacion.setMes(mes);
         fechaCreacion.setAnio(anio);

         TipoCuenta tipoCuenta(tipo);
         Persona persona(cedula, nombre, apellido);
         Cuenta cuenta(idCuenta, persona, saldo, tipoCuenta, contrasena, fechaCreacion);
         insertarCuenta(cuenta);
      }
      archivo.close();
   }

void buscarCuentasPorNombre(const std::string& nombreCompleto) const {
    if (!cabeza) {
        std::cout << "No hay cuentas en la lista." << std::endl;
        return;
    }
    NodoCuenta<T>* actual = cabeza;
    bool encontrada = false;
    do {
        std::string nombreCuenta = actual->getDato().getNombre() + " " + actual->getDato().getApellido();
        if (nombreCuenta == nombreCompleto) {
            std::cout << "ID: " << actual->getDato().getIdCuenta()
                    << ", Cedula: " << actual->getDato().getCedula()
                    << ", Nombre: " << actual->getDato().getNombre()
                    << ", Apellido: " << actual->getDato().getApellido()
                    << ", Saldo: " << actual->getDato().getSaldo()
                    << ", Tipo: " << actual->getDato().getTipo().getTipo()
                    << std::endl;
            encontrada = true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    if (!encontrada) {
        std::cout << "No se encontraron cuentas con ese nombre y apellido." << std::endl;
    }
}

// Buscar cuenta por ID (retorna puntero a Cuenta o nullptr)
T* buscarCuentaPorId(const std::string& id) const {
    if (!cabeza) return nullptr;
    NodoCuenta<T>* actual = cabeza;
    do {
        if (actual->getDato().getIdCuenta() == id) {
            return &(actual->getDato());
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return nullptr;
}

// Buscar y mostrar cuentas por cédula
void buscarCuentasPorCedula(const std::string& cedula) const {
    if (!cabeza) {
        std::cout << "No hay cuentas en la lista." << std::endl;
        return;
    }
    NodoCuenta<Cuenta>* actual = cabeza;
    bool encontradas = false;
    do {
        if (actual->getDato().getCedula() == cedula) {
            std::cout << "ID: " << actual->getDato().getIdCuenta()
                      << ", Cedula: " << actual->getDato().getCedula()
                      << ", Nombre: " << actual->getDato().getNombre()
                      << ", Apellido: " << actual->getDato().getApellido()
                      << ", Saldo: " << actual->getDato().getSaldo()
                      << ", Tipo: " << actual->getDato().getTipo().getTipo()
                      << std::endl;
            encontradas = true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    if (!encontradas) {
        std::cout << "No se encontraron cuentas con esa cedula." << std::endl;
    }
}


void mostrarCuentaPorId(const std::string& id) const {
    if (!cabeza) {
        std::cout << "No hay cuentas en la lista." << std::endl;
        return;
    }
    NodoCuenta<T>* actual = cabeza; // Usa T, no Cuenta
    bool encontrada = false;
    do {
        if (actual->getDato().getIdCuenta() == id) {
            const T& cuenta = actual->getDato();
            std::cout << "ID: " << cuenta.getIdCuenta()
                    << ", Cedula: " << cuenta.getCedula()
                    << ", Nombre: " << cuenta.getNombre()
                    << ", Apellido: " << cuenta.getApellido()
                    << ", Saldo: " << cuenta.getSaldo()
                    << ", Tipo: " << cuenta.getTipo().getTipo()
                    << std::endl;
            encontrada = true;
            break;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    if (!encontrada) {
        std::cout << "No se encontro ninguna cuenta con ese ID." << std::endl;
    }
}

};

#endif