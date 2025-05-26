#ifndef __LISTATRANSACCION_H
#define __LISTATRANSACCION_H
#include "NodoTransaccion.h"
#include "Cuenta.h"
#include "TipoTransaccion.h"
#include "Fecha.h"
#include "Persona.h"
#include "TipoCuenta.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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

   void mostrarTransacciones(string tipo) const {

    if (!cabeza) {
        std::cout << "No hay transacciones en la lista." << std::endl;
        return;
    }
    
    NodoTransaccion<T>* actual = cabeza;
    do {
        T trans = actual->getDato();  // copia
        auto cuenta = trans.getCuenta();  // copia
        auto tipoCuenta = cuenta.getTipo();  // copia
        auto tipoTrans = trans.getTipoTransaccion();  // copia
        auto fecha = trans.getFecha();  // copia

        while (tipo =="ahorro" && tipoTrans.getTipo() == "Consulta de saldo-ahorro"
            || tipoTrans.getTipo() == "Deposito-ahorro"
            || tipoTrans.getTipo() == "Retiro-ahorro") {
            std::cout << "Cuenta ID: " << cuenta.getIdCuenta()
            << ", Nombre: " << cuenta.getNombre()
            << ", Cedula: " << cuenta.getCedula()
            << ", Tipo de Cuenta: " << tipoCuenta.getTipo()
            << ", Saldo: " << cuenta.getSaldo()
            << ", Tipo de Transaccion: " << tipoTrans.getTipo()
            << ", Monto: " << trans.getMonto()
            << ", Fecha: " << fecha.getDia() << "/"
            << fecha.getMes() << "/"
            << fecha.getAnio()
            << std::endl;
            break;  // Salir del bucle si se encuentra una transacción de ahorro
        }

      while (tipo != "ahorro" && tipoTrans.getTipo() == "Consulta de saldo-corriente"
            || tipoTrans.getTipo() == "Deposito-corriente"
            || tipoTrans.getTipo() == "Retiro-corriente"
            || tipoTrans.getTipo() == "Estado de sobregiro-corriente"
            || tipoTrans.getTipo() == "Calculo de interes de sobregiro-corriente"
            || tipoTrans.getTipo() == "Pago de sobregiro-corriente") {
            std::cout << "Cuenta ID: " << cuenta.getIdCuenta()
            << ", Nombre: " << cuenta.getNombre()
            << ", Cedula: " << cuenta.getCedula()
            << ", Tipo de Cuenta: " << tipoCuenta.getTipo()
            << ", Saldo: " << cuenta.getSaldo()
            << ", Tipo de Transaccion: " << tipoTrans.getTipo()
            << ", Monto: " << trans.getMonto()
            << ", Fecha: " << fecha.getDia() << "/"
            << fecha.getMes() << "/"
            << fecha.getAnio()
            << std::endl;  
            break;
         }
            actual = actual->getSiguiente();
      
      

    } while (actual != cabeza);
}


      void mostrarTransaccionesPorFecha(int dia, int mes, int anio) const {
       if (!cabeza) {
           std::cout << "No hay transacciones en la lista." << std::endl;
           return;
       }
   
       bool encontrado = false;
       NodoTransaccion<T>* actual = cabeza;
       do {
           T trans = actual->getDato();
           auto cuenta = trans.getCuenta();
           auto tipoCuenta = cuenta.getTipo();
           auto tipoTrans = trans.getTipoTransaccion();
           auto fecha = trans.getFecha();
   
           if (fecha.getDia() == dia && fecha.getMes() == mes && fecha.getAnio() == anio) {
               std::cout << "Cuenta ID: " << cuenta.getIdCuenta()
                   << ", Nombre: " << cuenta.getNombre()
                   << ", Cedula: " << cuenta.getCedula()
                   << ", Tipo de Cuenta: " << tipoCuenta.getTipo()
                   << ", Saldo: " << cuenta.getSaldo()
                   << ", Tipo de Transaccion: " << tipoTrans.getTipo()
                   << ", Monto: " << trans.getMonto()
                   << ", Fecha: " << fecha.getDia() << "/"
                   << fecha.getMes() << "/"
                   << fecha.getAnio()
                   << std::endl;
               encontrado = true;
           }
   
           actual = actual->getSiguiente();
       } while (actual != cabeza);
   
       if (!encontrado) {
           std::cout << "No se encontraron transacciones para esa fecha." << std::endl;
       }
   }

   // Guarda todas las transacciones en un archivo de texto (modo append para no sobrescribir)
   void guardarTransaccionesEnArchivo(const std::string& nombreArchivo) const {
      std::ofstream archivo(nombreArchivo, std::ios::app); // Modo append
      if (!archivo.is_open()) {
         std::cout << "No se pudo abrir el archivo para guardar transacciones." << std::endl;
         return;
      }
      if (!cabeza) {
         archivo << "No hay transacciones en la lista." << std::endl;
         archivo.close();
         return;
      }
      NodoTransaccion<T>* actual = cabeza;
      do {
         T trans = actual->getDato();
         auto cuenta = trans.getCuenta();
         auto tipoCuenta = cuenta.getTipo();
         auto tipoTrans = trans.getTipoTransaccion();
         auto fecha = trans.getFecha();
         archivo << "Cuenta ID: " << cuenta.getIdCuenta()
                 << ", Nombre: " << cuenta.getNombre()
                 << ", Cedula: " << cuenta.getCedula()
                 << ", Tipo de Cuenta: " << tipoCuenta.getTipo()
                 << ", Saldo: " << cuenta.getSaldo()
                 << ", Tipo de Transaccion: " << tipoTrans.getTipo()
                 << ", Monto: " << trans.getMonto()
                 << ", Fecha: " << fecha.getDia() << "/"
                 << fecha.getMes() << "/"
                 << fecha.getAnio()
                 << std::endl;
         actual = actual->getSiguiente();
      } while (actual != cabeza);
      archivo.close();
   }

   // Guarda solo las transacciones de una fecha específica en un archivo de texto (modo append)
   void guardarTransaccionesPorFechaEnArchivo(const std::string& nombreArchivo, int dia, int mes, int anio) const {
      std::ofstream archivo(nombreArchivo, std::ios::app); // Modo append
      if (!archivo.is_open()) {
         std::cout << "No se pudo abrir el archivo para guardar transacciones por fecha." << std::endl;
         return;
      }
      if (!cabeza) {
         archivo << "No hay transacciones en la lista." << std::endl;
         archivo.close();
         return;
      }
      bool encontrado = false;
      NodoTransaccion<T>* actual = cabeza;
      do {
         T trans = actual->getDato();
         auto cuenta = trans.getCuenta();
         auto tipoCuenta = cuenta.getTipo();
         auto tipoTrans = trans.getTipoTransaccion();
         auto fecha = trans.getFecha();
         if (fecha.getDia() == dia && fecha.getMes() == mes && fecha.getAnio() == anio) {
            archivo << "Cuenta ID: " << cuenta.getIdCuenta()
                    << ", Nombre: " << cuenta.getNombre()
                    << ", Cedula: " << cuenta.getCedula()
                    << ", Tipo de Cuenta: " << tipoCuenta.getTipo()
                    << ", Saldo: " << cuenta.getSaldo()
                    << ", Tipo de Transaccion: " << tipoTrans.getTipo()
                    << ", Monto: " << trans.getMonto()
                    << ", Fecha: " << fecha.getDia() << "/"
                    << fecha.getMes() << "/"
                    << fecha.getAnio()
                    << std::endl;
            encontrado = true;
         }
         actual = actual->getSiguiente();
      } while (actual != cabeza);
      if (!encontrado) {
         archivo << "No se encontraron transacciones para esa fecha." << std::endl;
      }
      archivo.close();
   }
};

#endif