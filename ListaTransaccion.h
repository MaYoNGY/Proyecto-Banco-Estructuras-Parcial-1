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
   NodoTransaccion<T>* getNodoCabeza() const { return cabeza; }

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

        if (cuenta.getIdCuenta() == idCuenta) {
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
                          << " Hora: " << fecha.getHora() << ":"
                          << fecha.getMinutos() << ":"
                          << fecha.getSegundos()
                          << std::endl;
                encontrada = true;
            } else if (tipo == "corriente" && (
                tipoTrans.getTipo() == "Consulta de saldo-corriente" ||
                tipoTrans.getTipo() == "Deposito-corriente" ||
                tipoTrans.getTipo() == "Retiro-corriente" ||
                tipoTrans.getTipo() == "Sobregiro-corriente")) {
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
                          << " Hora: " << fecha.getHora() << ":"
                          << fecha.getMinutos() << ":"
                          << fecha.getSegundos()
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
                   << " Hora: " << fecha.getHora() << ":"
                   << fecha.getMinutos() << ":"
                   << fecha.getSegundos()                   
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
                 << " Hora: " << fecha.getHora() << ":"
                 << fecha.getMinutos() << ":"
                 << fecha.getSegundos() 
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
                   << cuenta.getApellido() << " "
                   << cuenta.getCedula() << " "
                   << tipoCuenta.getTipo() << " "
                   << cuenta.getSaldo() << " "
                   << tipoTrans.getTipo() << " "
                   << trans.getMonto() << " "
                   << fecha.getDia() << " "
                   << fecha.getMes() << " "
                   << fecha.getAnio() << " "
                   << fecha.getHora() << " "
                   << fecha.getMinutos() << " "
                   << fecha.getSegundos() << " "
                   << cuenta.getSucursal().getNombre() << " "      // Guarda el nombre de la sucursal
                   << cuenta.getSucursal().getCodigo()             // Guarda el código de la sucursal
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

    limpiarLista(); // Limpia la lista antes de cargar para evitar duplicados

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::istringstream iss(linea);
        std::string idCuenta, nombre, apellido, cedula, tipoCuenta, tipoTransaccion, sucursalNombre, codigoSucursal;
        double saldo, monto;
        int dia, mes, anio, hora, minutos, segundos;

        // Leer todos los datos, incluyendo el código de sucursal
        if (!(iss >> idCuenta >> nombre >> apellido >> cedula >> tipoCuenta >> saldo >> tipoTransaccion >> monto
          >> dia >> mes >> anio >> hora >> minutos >> segundos >> sucursalNombre >> codigoSucursal)) {
            std::cerr << "Error de formato en la línea: " << linea << std::endl;
            continue;
        }

        // Crear los objetos necesarios para la transacción
        Fecha fecha;
        fecha.setDia(dia);
        fecha.setMes(mes);
        fecha.setAnio(anio);
        fecha.setHora(hora);
        fecha.setMinutos(minutos);
        fecha.setSegundos(segundos);

        TipoCuenta tipoCuentaObj(tipoCuenta);
        Persona persona(cedula, nombre, apellido);
        Sucursal sucursal(sucursalNombre, "", codigoSucursal); // Usa el objeto Sucursal
        Cuenta cuenta(idCuenta, persona, saldo, tipoCuentaObj, "", fecha, sucursal); // Pasa el objeto Sucursal
        TipoTransaccion tipoTrans(tipoTransaccion);

        T transaccion(cuenta, tipoTrans, monto, fecha);
        insertarTransaccion(transaccion);
    }
    archivo.close();
}

   void registrarTransaccionConFecha(const T& transaccion) {
    // Obtener la fecha y hora actual del sistema
    time_t now = time(0);
    tm* ltm = localtime(&now);
    Fecha fechaActual;
    fechaActual.setDia(ltm->tm_mday);
    fechaActual.setMes(1 + ltm->tm_mon);
    fechaActual.setAnio(1900 + ltm->tm_year);
    fechaActual.setHora(ltm->tm_hour);
    fechaActual.setMinutos(ltm->tm_min);
    fechaActual.setSegundos(ltm->tm_sec);

    // Crear una copia de la transacción con la fecha y hora actual
    T transaccionConFecha = transaccion;
    transaccionConFecha.setFecha(fechaActual);

    // Insertar la transacción en la lista
    insertarTransaccion(transaccionConFecha);
}
       
};

#endif