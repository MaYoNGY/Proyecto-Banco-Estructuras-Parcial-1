#ifndef __LISTATRANSACCION_H
#define __LISTATRANSACCION_H
#include "NodoTransaccion.h"
#include <vector>

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


   // Buscar transacciones por id de cuenta y fecha
   std::vector<T> buscarTransaccionesPorCuentaYFecha(int idCuenta, int dia, int mes, int anio) const {
      std::vector<T> resultados;
      if (!cabeza) return resultados;
      NodoTransaccion<T>* actual = cabeza;
      do {
         const T& trans = actual->getDato();
         if (trans.getCuenta().getIdCuenta() == idCuenta &&
             trans.getFecha().getDia() == dia &&
             trans.getFecha().getMes() == mes &&
             trans.getFecha().getAnio() == anio) {
            resultados.push_back(trans);
         }
         actual = actual->getSiguiente();
      } while (actual != cabeza);
      return resultados;
   }

   // Puedes agregar más funciones auxiliares para otros criterios si lo necesitas
};

#endif