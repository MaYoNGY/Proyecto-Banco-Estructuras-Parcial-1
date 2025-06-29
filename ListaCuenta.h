#ifndef __LISTACUENTA_H
#define __LISTACUENTA_H
#include <iostream>
#include <string>
#include "NodoCuenta.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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
        Fecha fecha = actual->getDato().getFechaCreacion();  
        std::cout << "ID: " << actual->getDato().getIdCuenta()
                  << ", Cedula: " << actual->getDato().getCedula()
                  << ", Nombre: " << actual->getDato().getNombre()
                  << ", Apellido: " << actual->getDato().getApellido()
                  << ", Saldo: " << actual->getDato().getSaldo()
                  << ", Tipo: " << actual->getDato().getTipo().getTipo()
                  << ", Fecha de Creacion: "
                  << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio()
                  << " " << fecha.getHora() << ":" << fecha.getMinutos() << ":" << fecha.getSegundos()
                  << ", Sucursal: " << actual->getDato().getSucursal().getNombre() // <-- Usa el objeto
                  << ", Codigo Sucursal: " << actual->getDato().getSucursal().getCodigo()
                  << std::endl;
        actual = actual->getSiguiente();
    } while (actual != cabeza);
   }

void mostrarCuentasConFecha() const {
    if (!cabeza) {
        std::cout << "No hay cuentas en la lista." << std::endl;
        return;
    }
    NodoCuenta<T>* actual = cabeza;
    do {
        Fecha fecha = actual->getDato().getFechaCreacion();       
        std::cout << "ID: " << actual->getDato().getIdCuenta()
                  << ", Cedula: " << actual->getDato().getCedula()
                  << ", Nombre: " << actual->getDato().getNombre()
                  << ", Apellido: " << actual->getDato().getApellido()
                  << ", Saldo: " << actual->getDato().getSaldo()
                  << ", Tipo: " << actual->getDato().getTipo().getTipo()
                  << ", Fecha de Creacion: "
                  << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio()
                  << " " << fecha.getHora() << ":" << fecha.getMinutos() << ":" << fecha.getSegundos()
                  << ", Sucursal: " << actual->getDato().getSucursal().getNombre() // <-- Usa el objeto
                  << ", Codigo Sucursal: " << actual->getDato().getSucursal().getCodigo()
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
                << actual->getDato().getSaldo() << " "
                << actual->getDato().getFechaCreacion().getDia() << " "
                << actual->getDato().getFechaCreacion().getMes() << " "
                << actual->getDato().getFechaCreacion().getAnio() << " "
                << actual->getDato().getFechaCreacion().getHora() << " "
                << actual->getDato().getFechaCreacion().getMinutos() << " "
                << actual->getDato().getFechaCreacion().getSegundos() << " "
                << actual->getDato().getNumeroCuentaCompleto() << " " // <-- Añade esta línea
                << actual->getDato().getSucursal().getNombre() << " "
                << actual->getDato().getSucursal().getCodigo()
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
    std::string idCuenta, cedula, nombre, apellido, tipo, contrasena, numeroCuentaCompleto, sucursalNombre, codigoSucursal;
    double saldo;
    int dia, mes, anio, hora, minutos, segundos;

    // Lee los campos en el mismo orden en que se guardaron
    if (!(iss >> idCuenta >> cedula >> nombre >> apellido >> tipo 
          >> contrasena >> saldo >> dia >> mes >> anio 
          >> hora >> minutos >> segundos >> numeroCuentaCompleto >> sucursalNombre >> codigoSucursal)) {
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
    fechaCreacion.setHora(hora);
    fechaCreacion.setMinutos(minutos);
    fechaCreacion.setSegundos(segundos);

    TipoCuenta tipoCuenta(tipo);
    Persona persona(cedula, nombre, apellido);
    Sucursal sucursal(sucursalNombre, "", codigoSucursal); // Usa el objeto Sucursal
    Cuenta cuenta(idCuenta, persona, saldo, tipoCuenta, contrasena, fechaCreacion, sucursal); // Pasa el objeto Sucursal
    cuenta.setNumeroCuentaCompleto(numeroCuentaCompleto); // <-- Asigna el número de cuenta completo
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
        Fecha fecha = actual->getDato().getFechaCreacion();
        std::string nombreCuenta = actual->getDato().getNombre() + " " + actual->getDato().getApellido();
        if (nombreCuenta == nombreCompleto) {
            std::cout << "ID: " << actual->getDato().getIdCuenta()
                    << ", Cedula: " << actual->getDato().getCedula()
                    << ", Nombre: " << actual->getDato().getNombre()
                    << ", Apellido: " << actual->getDato().getApellido()
                    << ", Saldo: " << actual->getDato().getSaldo()
                    << ", Tipo: " << actual->getDato().getTipo().getTipo()
                    << ", Fecha de Creacion: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio()
                    << " " << fecha.getHora() << ":" << fecha.getMinutos() << ":" << fecha.getSegundos()
                    << ", Sucursal: " << actual->getDato().getSucursal().getNombre() // <-- Usa el objeto
                    << ", Codigo Sucursal: " << actual->getDato().getSucursal().getCodigo()
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
        Fecha fecha = actual->getDato().getFechaCreacion();
        if (actual->getDato().getCedula() == cedula) {
            std::cout << "ID: " << actual->getDato().getIdCuenta()
                      << ", Cedula: " << actual->getDato().getCedula()
                      << ", Nombre: " << actual->getDato().getNombre()
                      << ", Apellido: " << actual->getDato().getApellido()
                      << ", Saldo: " << actual->getDato().getSaldo()
                      << ", Tipo: " << actual->getDato().getTipo().getTipo()
                      << ", Fecha de Creacion: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio()
                      << " " << fecha.getHora() << ":" << fecha.getMinutos() << ":" << fecha.getSegundos()
                      << ", Sucursal: " << actual->getDato().getSucursal().getNombre() // <-- Usa el objeto
                      << ", Codigo Sucursal: " << actual->getDato().getSucursal().getCodigo()
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
        Fecha fecha = actual->getDato().getFechaCreacion();
        if (actual->getDato().getIdCuenta() == id) {
            const T& cuenta = actual->getDato();
            std::cout << "ID: " << cuenta.getIdCuenta()
                    << ", Cedula: " << cuenta.getCedula()
                    << ", Nombre: " << cuenta.getNombre()
                    << ", Apellido: " << cuenta.getApellido()
                    << ", Saldo: " << cuenta.getSaldo()
                    << ", Tipo: " << cuenta.getTipo().getTipo()
                    << ", Fecha de Creacion: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio()
                    << " " << fecha.getHora() << ":" << fecha.getMinutos() << ":" << fecha.getSegundos()
                    << ", Sucursal: " << cuenta.getSucursal().getNombre() // <-- Usa el objeto
                    << ", Codigo Sucursal: " << cuenta.getSucursal().getCodigo()
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

void buscarCuentasPorDato(const std::string& valor) const {
    if (!cabeza) {
        std::cout << "No hay cuentas en la lista." << std::endl;
        return;
    }
    NodoCuenta<T>* actual = cabeza;
    bool encontrada = false;
    do {
        Fecha fecha = actual->getDato().getFechaCreacion();
        const T& cuenta = actual->getDato();
        if (cuenta.getNombre() == valor ||
            cuenta.getApellido() == valor ||
            cuenta.getCedula() == valor ||
            cuenta.getIdCuenta() == valor ||
            cuenta.getTipo().getTipo() == valor) {
            std::cout << "ID: " << cuenta.getIdCuenta()
                      << ", Cedula: " << cuenta.getCedula()
                      << ", Nombre: " << cuenta.getNombre()
                      << ", Apellido: " << cuenta.getApellido()
                      << ", Saldo: " << cuenta.getSaldo()
                      << ", Tipo: " << cuenta.getTipo().getTipo()
                      << ", Fecha de Creacion: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio()
                      << " " << fecha.getHora() << ":" << fecha.getMinutos() << ":" << fecha.getSegundos()
                      << ", Sucursal: " << cuenta.getSucursal().getNombre() // <-- Usa el objeto
                      << ", Codigo Sucursal: " << cuenta.getSucursal().getCodigo()
                      << std::endl;
            encontrada = true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    if (!encontrada) {
        std::cout << "No se encontraron cuentas con el dato: " << valor << std::endl;
    }
}

// Ordena la lista de cuentas por nombre, apellido o fecha usando selection sort
   void ordenarPorCampo(int campo) {
    if (!cabeza || cabeza == cabeza->getSiguiente()) return; // 0 o 1 elemento

    NodoCuenta<T>* actual = cabeza;
    do {
        NodoCuenta<T>* menor = actual;
        NodoCuenta<T>* siguiente = actual->getSiguiente();

        while (siguiente != cabeza) {
            bool esMenor = false;

            switch (campo) {
                case 0: { // Nombre A-Z
                    std::string a = siguiente->getDato().getNombre();
                    std::string b = menor->getDato().getNombre();
                    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
                    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
                    esMenor = a < b;
                    break;
                }
                case 1: { // Apellido A-Z
                    std::string a = siguiente->getDato().getApellido();
                    std::string b = menor->getDato().getApellido();
                    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
                    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
                    esMenor = a < b;
                    break;
                }
                case 2: { // Fecha más antigua
                    Fecha f1 = siguiente->getDato().getFechaCreacion();
                    Fecha f2 = menor->getDato().getFechaCreacion();
                    if (f1.getAnio() != f2.getAnio()) esMenor = f1.getAnio() < f2.getAnio();
                    else if (f1.getMes() != f2.getMes()) esMenor = f1.getMes() < f2.getMes();
                    else esMenor = f1.getDia() < f2.getDia();
                    break;
                }
                case 3: { // Fecha más nueva
                Fecha f1 = siguiente->getDato().getFechaCreacion();
                Fecha f2 = menor->getDato().getFechaCreacion();
                if (f1.getAnio() != f2.getAnio()) esMenor = f1.getAnio() > f2.getAnio();
                else if (f1.getMes() != f2.getMes()) esMenor = f1.getMes() > f2.getMes();
                else esMenor = f1.getDia() > f2.getDia();
                break;
                }
                case 4: { // Nombre Z-A
                    std::string a = siguiente->getDato().getNombre();
                    std::string b = menor->getDato().getNombre();
                    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
                    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
                    esMenor = a > b;
                    break;
                }
                case 5: { // Apellido Z-A
                    std::string a = siguiente->getDato().getApellido();
                    std::string b = menor->getDato().getApellido();
                    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
                    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
                    esMenor = a > b;
                    break;
                }
            }

            if (esMenor) menor = siguiente;
            siguiente = siguiente->getSiguiente();
        }

        if (menor != actual) {
            T temp = actual->getDato();
            actual->getDato() = menor->getDato();
            menor->getDato() = temp;
        }

        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

void buscarCuentasPorSucursal(const std::string& sucursal) const {
    NodoCuenta<T>* actual = cabeza;
    bool encontrada = false;
    if (!actual) {
        std::cout << "No hay cuentas registradas." << std::endl;
        return;
    }
    do {
        if (actual->getDato().getSucursal().getNombre() == sucursal) { // <-- Usa el objeto Sucursal
            encontrada = true;
            Fecha fecha = actual->getDato().getFechaCreacion();
            std::cout << "ID: " << actual->getDato().getIdCuenta()
                      << ", Cedula: " << actual->getDato().getCedula()
                      << ", Nombre: " << actual->getDato().getNombre()
                      << ", Apellido: " << actual->getDato().getApellido()
                      << ", Saldo: " << actual->getDato().getSaldo()
                      << ", Tipo: " << actual->getDato().getTipo().getTipo()
                      << ", Fecha de Creacion: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio()
                      << " " << fecha.getHora() << ":" << fecha.getMinutos() << ":" << fecha.getSegundos()
                      << ", Sucursal: " << actual->getDato().getSucursal().getNombre() // <-- Usa el objeto
                      << ", Codigo Sucursal: " << actual->getDato().getSucursal().getCodigo()
                      << std::endl;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    if (!encontrada) {
        std::cout << "No hay cuentas en esa sucursal." << std::endl;
    }
}

void buscarCuentasPorFechaYSucursal(int dia, int mes, int anio, const std::string& nombreSucursal) const {
    if (!cabeza) {
        std::cout << "No hay cuentas en la lista." << std::endl;
        return;
    }
    // 1. Copia a vector
    std::vector<Cuenta> cuentasVec;
    NodoCuenta<T>* actual = cabeza;
    do {
        cuentasVec.push_back(actual->getDato());
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    // 2. Ordena por fecha y sucursal usando selection sort
    for (size_t i = 0; i < cuentasVec.size(); ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < cuentasVec.size(); ++j) {
            Fecha fa = cuentasVec[j].getFechaCreacion();
            Fecha fb = cuentasVec[minIdx].getFechaCreacion();
            if (fa.getAnio() < fb.getAnio() ||
                (fa.getAnio() == fb.getAnio() && fa.getMes() < fb.getMes()) ||
                (fa.getAnio() == fb.getAnio() && fa.getMes() == fb.getMes() && fa.getDia() < fb.getDia()) ||
                (fa.getAnio() == fb.getAnio() && fa.getMes() == fb.getMes() && fa.getDia() == fb.getDia() &&
                 cuentasVec[j].getSucursal().getNombre() < cuentasVec[minIdx].getSucursal().getNombre())) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(cuentasVec[i], cuentasVec[minIdx]);
        }
    }

    // 3. Objeto clave
    Fecha fechaClave; fechaClave.setDia(dia); fechaClave.setMes(mes); fechaClave.setAnio(anio);
    Sucursal sucursalClave(nombreSucursal);
    Cuenta cuentaClave(Persona(), 0, TipoCuenta(), sucursalClave);
    cuentaClave.setFechaCreacion(fechaClave);

    // Comparador igual al usado en el sort
    auto comparar = [](const Cuenta& a, const Cuenta& b) {
        Fecha fa = a.getFechaCreacion();
        Fecha fb = b.getFechaCreacion();
        if (fa.getAnio() != fb.getAnio()) return fa.getAnio() < fb.getAnio();
        if (fa.getMes() != fb.getMes()) return fa.getMes() < fb.getMes();
        if (fa.getDia() != fb.getDia()) return fa.getDia() < fb.getDia();
        return a.getSucursal().getNombre() < b.getSucursal().getNombre();
    };

    // 4. Búsqueda binaria manual para encontrar la primera coincidencia
    int left = 0, right = cuentasVec.size() - 1;
    int foundIdx = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        const Cuenta& midCuenta = cuentasVec[mid];
        Fecha f = midCuenta.getFechaCreacion();
        std::string suc = midCuenta.getSucursal().getNombre();

        // Compara fecha y sucursal
        if (f.getAnio() == anio && f.getMes() == mes && f.getDia() == dia && suc == nombreSucursal) {
            foundIdx = mid;
            // Busca si hay más a la izquierda (primer match)
            right = mid - 1;
        } else if (comparar(midCuenta, cuentaClave)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // 5. Si se encontró, muestra todas las coincidencias hacia adelante
    bool encontrada = false;
    if (foundIdx != -1) {
        // Avanza desde foundIdx mientras siga habiendo coincidencias
        for (size_t i = foundIdx; i < cuentasVec.size(); ++i) {
            Fecha f = cuentasVec[i].getFechaCreacion();
            if (f.getDia() == dia && f.getMes() == mes && f.getAnio() == anio &&
                cuentasVec[i].getSucursal().getNombre() == nombreSucursal) {
                std::cout << "ID: " << cuentasVec[i].getIdCuenta()
                          << ", Cedula: " << cuentasVec[i].getCedula()
                          << ", Nombre: " << cuentasVec[i].getNombre()
                          << ", Apellido: " << cuentasVec[i].getApellido()
                          << ", Saldo: " << cuentasVec[i].getSaldo()
                          << ", Tipo: " << cuentasVec[i].getTipo().getTipo()
                          << ", Fecha de Creacion: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio()
                          << " " << f.getHora() << ":" << f.getMinutos() << ":" << f.getSegundos()
                          << ", Sucursal: " << cuentasVec[i].getSucursal().getNombre()
                          << ", Codigo Sucursal: " << cuentasVec[i].getSucursal().getCodigo()
                          << std::endl;
                encontrada = true;
            } else {
                break;
            }
        }
    }
    if (!encontrada) {
        std::cout << "No se encontraron cuentas abiertas en esa fecha y sucursal." << std::endl;
    }
}

};

#endif