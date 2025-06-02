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

   void mostrarTransacciones(const std::string& idCuenta, const std::string& tipo) const {
       if (!cabeza) {
           std::cout << "No hay transacciones en la lista." << std::endl;
           return;
       }
       NodoTransaccion<T>* actual = cabeza;
       bool encontrada = false;
       do {
           T trans = actual->getDato();
           auto cuenta = trans.getCuenta();
           auto tipoCuenta = cuenta.getTipo();
           auto tipoTrans = trans.getTipoTransaccion();
           auto fecha = trans.getFecha();
   
           // Solo muestra si el ID de cuenta coincide
           if (cuenta.getIdCuenta() == idCuenta) {
               // Filtra por tipo de transacción si lo deseas
               if (tipo == "ahorro" && (
                   tipoTrans.getTipo() == "Consulta de saldo-ahorro" ||
                   tipoTrans.getTipo() == "Deposito-ahorro" ||
                   tipoTrans.getTipo() == "Retiro-ahorro")) {
                   std::cout << "Cuenta ID: " << cuenta.getIdCuenta()
                       << ", Nombre: " << cuenta.getNombre()
                       << ", Apellido: " << cuenta.getApellido()
                       << ", Cedula: " << cuenta.getCedula()
                       << ", Tipo de Cuenta: " << tipoCuenta.getTipo()
                       << ", Saldo: " << cuenta.getSaldo()
                       << ", Tipo de Transaccion: " << tipoTrans.getTipo()
                       << ", Monto: " << trans.getMonto()
                       << ", Fecha: " << fecha.getDia() << "/"
                       << fecha.getMes() << "/"
                       << fecha.getAnio()
                       << std::endl;
                   encontrada = true;
               }
               if (tipo == "corriente" && (
                   tipoTrans.getTipo() == "Consulta de saldo-corriente" ||
                   tipoTrans.getTipo() == "Deposito-corriente" ||
                   tipoTrans.getTipo() == "Retiro-corriente" ||
                   tipoTrans.getTipo() == "Estado de sobregiro-corriente" ||
                   tipoTrans.getTipo() == "Calculo de interes de sobregiro-corriente" ||
                   tipoTrans.getTipo() == "Pago de sobregiro-corriente")) {
                   std::cout << "Cuenta ID: " << cuenta.getIdCuenta()
                       << ", Nombre: " << cuenta.getNombre()
                       << ", Apellido: " << cuenta.getApellido()
                       << ", Cedula: " << cuenta.getCedula()
                       << ", Tipo de Cuenta: " << tipoCuenta.getTipo()
                       << ", Saldo: " << cuenta.getSaldo()
                       << ", Tipo de Transaccion: " << tipoTrans.getTipo()
                       << ", Monto: " << trans.getMonto()
                       << ", Fecha: " << fecha.getDia() << "/"
                       << fecha.getMes() << "/"
                       << fecha.getAnio()
                       << std::endl;
                   encontrada = true;
               }
           }
           actual = actual->getSiguiente();
       } while (actual != cabeza);
       if (!encontrada) {
           std::cout << "No se encontraron transacciones para esa cuenta." << std::endl;
       }
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
                   << ", Apellido: " << cuenta.getApellido()
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
                 << ", Apellido: " << cuenta.getApellido()
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


   void guardarTransaccionesEnArchivoPr(const std::string& nombreArchivo) const {
       std::ofstream archivo(nombreArchivo, std::ios::out); // Sobrescribe el archivo
       if (!archivo.is_open()) {
           std::cout << "No se pudo abrir el archivo para guardar transacciones." << std::endl;
           return;
       }
       if (!cabeza) {
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
           archivo << cuenta.getIdCuenta() << " "
                   << cuenta.getNombre() << " "
                   << cuenta.getCedula() << " "
                   << tipoCuenta.getTipo() << " "
                   << cuenta.getSaldo() << " "
                   << tipoTrans.getTipo() << " "
                   << trans.getMonto() << " "
                   << fecha.getDia() << " "
                   << fecha.getMes() << " "
                   << fecha.getAnio()
                   << std::endl;
           actual = actual->getSiguiente();
       } while (actual != cabeza);
       archivo.close();
   }

     // Limpia la lista antes de cargar para evitar duplicados
   void limpiarLista() {
      NodoTransaccion<T>* actual = cabeza;
      if (!actual) return;
      do {
         NodoTransaccion<T>* temp = actual;
         actual = actual->getSiguiente();
         delete temp;
      } while (actual != cabeza);
      cabeza = nullptr;
      cola = nullptr;
   }

      void cargarTransaccionesDesdeArchivo(const std::string& nombreArchivo) {
       std::ifstream archivo(nombreArchivo);
       if (!archivo.is_open()) {
           std::cerr << "Error al abrir el archivo " << nombreArchivo << " para lectura.\n";
           return;
       }
   
       limpiarLista();
   
       std::string linea;
       while (std::getline(archivo, linea)) {
           if (linea.empty()) continue;
   
           std::istringstream iss(linea);
           std::string idCuenta, nombre, cedula, tipoCuenta, tipoTransaccion;
           double saldo, monto;
           int dia, mes, anio;
   
           if (!(iss >> idCuenta >> nombre >> cedula >> tipoCuenta >> saldo >> tipoTransaccion >> monto >> dia >> mes >> anio)) {
               std::cerr << "Error de formato en la línea: " << linea << std::endl;
               continue;
           }
   
           Fecha fecha;
           fecha.setDia(dia);
           fecha.setMes(mes);
           fecha.setAnio(anio);
   
           TipoCuenta tipoCuentaObj(tipoCuenta);
           Persona persona(cedula, nombre, ""); // Apellido vacío si no lo guardas
           Cuenta cuenta(idCuenta, persona, saldo, tipoCuentaObj, "", fecha);
           TipoTransaccion tipoTrans(tipoTransaccion);
   
           T transaccion(cuenta, tipoTrans, monto, fecha);
           insertarTransaccion(transaccion);
       }
       archivo.close();
   }
       
};

#endif