#ifndef __LISTACUENTA_H
#define __LISTACUENTA_H
#include <iostream>
#include <string>
#include "NodoCuenta.h"

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

   NodoCuenta<T>* buscarCuenta(int idCuenta, const std::string& nombre) {
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
                  << ", Nombre: " << actual->getDato().getNombre()
                  << ", Saldo: " << actual->getDato().getSaldo()
                  << ", Tipo: " << actual->getDato().getTipo().getTipo()
                  << std::endl;
        actual = actual->getSiguiente();
    } while (actual != cabeza);
   }

   void eliminarCuenta(int idCuenta) {
       if (!cabeza) {
         std::cout << "No hay cuentas en la lista." << std::endl;
         return;
      }
   
       NodoCuenta<T>* actual = cabeza;
       do {
           if (actual->getDato().getIdCuenta() == idCuenta) {
               if (actual == cabeza && actual == cola) {
                   // Solo hay un nodo
                   delete actual;
                   cabeza = cola = nullptr;
                   return;
               }
               if (actual == cabeza) {
                   cabeza = cabeza->getSiguiente();
               }
               if (actual == cola) {
                   cola = cola->getAnterior();
               }
               actual->getAnterior()->setSiguiente(actual->getSiguiente());
               actual->getSiguiente()->setAnterior(actual->getAnterior());
               delete actual;
               return;
           }
           actual = actual->getSiguiente();
       } while (actual != cabeza);
   }
};

#endif