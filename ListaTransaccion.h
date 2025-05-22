#ifndef __LISTATRANSACCION_H
#define __LISTATRANSACCION_H
#include "NodoTransaccion.h"

template<typename T>
class ListaTransaccion
{
private:
   NodoTransaccion<T>* cabeza;
   NodoTransaccion<T>* cola;
   
public:
   ListaTransaccion() : cabeza(nullptr), cola(nullptr) {}

   ~ListaTransaccion() {
      NodoTransaccion<T>* actual = cabeza;
      while (actual) {
         NodoTransaccion<T>* temp = actual;
         actual = actual->getSiguiente();
         delete temp;
      }
   }

   void insertarTransaccion(const T& transaccion) {
      NodoTransaccion<T>* nuevo = new NodoTransaccion<T>(transaccion);
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

   NodoTransaccion<T>* buscarTransaccion(const std::string& tipo, double monto) {
      if (!cabeza) {
         std::cout << "No hay transacciones en la lista." << std::endl;
         return nullptr;
      }
      NodoTransaccion<T>* actual = cabeza;
      do {
         if (actual->getDato().getTipoTransaccion().getTipo() == tipo && actual->getDato().getMonto() == monto) {
            return actual;
         }
         actual = actual->getSiguiente();
      } while (actual != cabeza);
      return nullptr;
   }

   void mostrarTransacciones() const {
       if (!cabeza) {
           std::cout << "No hay transacciones en la lista." << std::endl;
           return;
       }
       NodoTransaccion<T>* actual = cabeza;
       do {
           std::cout << "Cuenta ID: " << actual->getDato().getCuenta().getIdCuenta()
                     << ", Nombre: " << actual->getDato().getCuenta().getNombre()
                     << ", Cedula: " << actual->getDato().getCuenta().getCedula()
                     << ", Tipo de Cuenta: " << actual->getDato().getCuenta().getTipo().getTipo()
                     << ", Saldo: " << actual->getDato().getCuenta().getSaldo()
                     << ", Tipo de Transacción: " << actual->getDato().getTipoTransaccion().getTipo()
                     << ", Monto: " << actual->getDato().getMonto()
                     << ", Fecha: " << actual->getDato().getFecha().getDia() << "/"
                     << actual->getDato().getFecha().getMes() << "/"
                     << actual->getDato().getFecha().getAnio()
                     << std::endl;
           actual = actual->getSiguiente();
       } while (actual != cabeza);
   }
};

#endif