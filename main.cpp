/***********************************************************************
 * Module:  main.cpp
 * Author:  Marjorie Cedeño, Victoria Diaz, Domenika Naranjo
 * Modified: sabado, 17 de mayo de 2025 21:08:05
 * Purpose: Cuenta Bancaria
 ***********************************************************************/
#include <iostream>
#include <conio.h> // Para _getch()
#include <windows.h> // Para SetConsoleCursorPosition
#include <string>
#include <ctime>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "Validar.cpp"
#include "VentanaAyuda.cpp"
#include "Cuenta.cpp"
#include "Persona.cpp"
#include "TipoCuenta.cpp"
#include "ListaCuenta.h"
#include "ContrasenaUsuario.cpp"
#include "Fecha.cpp"
#include "OperacionCuenta.cpp"
#include "ListaTransaccion.h"
#include "Transaccion.cpp"
#include "TipoTransaccion.cpp"
#include "CuentaBinario.h"
#include "CifradoCesar.h"
#include "AccesoUsuario.h" // Incluye la clase de acceso de usuario
#include "TransaccionesUsuario.h"
#include "SimuladorSobregiro.h"
#include "Sucursal.h" // Incluye la clase Sucursal
#include "Cita.h"
#include "Cita.cpp"
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>


using namespace std;

ListaCuenta<Cuenta> listaCuentas;
ListaTransaccion<Transaccion> listaTransacciones;
std::map<std::string, std::vector<Cita>> citasPorSucursal;

unsigned long long contadorId = 1;

std::vector<Sucursal> sucursales = {
    Sucursal("Quito", "Av. Amazonas y NN", "0001"),
    Sucursal("Sangolqui", "Av. General Enríquez", "0002"),
    Sucursal("Cumbaya", "Plaza Cumbaya", "0003")
};


int leerUltimoIdCuenta() {
    // Primero verificamos si hay cuentas
    if (!listaCuentas.getNodoCabeza()) {
        // No hay cuentas, reiniciamos el contador
        std::ofstream archivo("ultimo_id.txt", std::ios::trunc);
        if (archivo.is_open()) {
            archivo << 0;
            archivo.close();
        }
        return 0;
    }

    // Si hay cuentas, procedemos normalmente
    std::ifstream archivo("ultimo_id.txt");
    int ultimoId = 0;
    if (archivo.is_open()) {
        archivo >> ultimoId;
        archivo.close();
    }
    return ultimoId;
}

void guardarUltimoIdCuenta(int ultimoId) {
    std::ofstream archivo("ultimo_id.txt", std::ios::trunc);
    if (archivo.is_open()) {
        archivo << ultimoId;
        archivo.close();
    }
}

// Función para mover el cursor a una posición específica
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

double pedirMontoSeguro(const std::string& mensaje) {
    std::cout << mensaje;
    std::string montoStr = Validar::pedirMonto();
    return std::stod(montoStr);
}

Sucursal seleccionarSucursal(const std::vector<Sucursal>& sucursales) {
    int opcion = 0;
    while (true) {
        system("cls");
        std::cout << "=== Seleccione la sucursal ===" << std::endl;
        for (size_t i = 0; i < sucursales.size(); i++) {
            if ((int)i == opcion)
                std::cout << ">> " << sucursales[i].getNombre() << std::endl;
            else
                std::cout << "   " << sucursales[i].getNombre() << std::endl;
        }
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) { // Flecha arriba
                if (opcion > 0) opcion--;
                else opcion = sucursales.size() - 1;
            } else if (tecla == 80) { // Flecha abajo
                if (opcion < (int)sucursales.size() - 1) opcion++;
                else opcion = 0;
            }
        } else if (tecla == 13) {
            return sucursales[opcion];
        }
    }
}


// Imprime el menú y resalta la opción seleccionada
void imprimirMenu(int opcionSeleccionada) {
    system("cls");
    cout << "========== Sistema Bancario ==========" << endl;
    string opciones[] = {
        "1. Crear nueva cuenta",
        "2. Iniciar sesion para tramites",
        "3. Consultas avanzadas",
        "4. Generar Backup",
        "5. Restaurar Backup",
        "6. Generar archivo binario",
        "7. Cifrar backup",
        "8. Decifrar backup",
        "9. Ordenar cuentas",
        "10. Ayuda",
        "11. Pico de acceso de usuario", // Nueva opción
        "12. Pico de transacciones de usuario",
        "13. Asignar cita para apertura de cuenta",
        "14. Mostrar distancia de una cita especifica",
        "15. Salir"
    };
    for (int i = 0; i < 15; i++) {
        if (i == opcionSeleccionada)
            cout << ">> " << opciones[i] << endl;
        else
            cout << "   " << opciones[i] << endl;
    }
}

// Imprime el submenú para tipo de cuenta
int submenuTipoCuenta() {
    int opcion = 0;
    string opciones[] = {
        "1. Ahorros",
        "2. Corriente",
        "3. Regresar"
    };
    while (true) {
        system("cls");
        cout << "=== Seleccione tipo de cuenta ===" << endl;
        for (int i = 0; i < 3; i++) {
            if (i == opcion)
                cout << ">> " << opciones[i] << endl;
            else
                cout << "   " << opciones[i] << endl;
        }
        int tecla = _getch();
        if (tecla == 224) { // Tecla especial
            tecla = _getch();
        if (tecla == 72) { // Flecha arriba
            if (opcion > 0)
                opcion--;
            else
                opcion = 2; // Si está en la primera opción, va a la última
        } else if (tecla == 80) { // Flecha abajo
            if (opcion < 2)
                opcion++;
            else
            opcion = 0; // Si está en la última opción, va a la primera
        }
        } else if (tecla == 13) { // Enter
            return opcion;
        }
    }
}

// Menú de transacciones tras login exitoso
void menuTransacciones(Cuenta* cuenta) {
    int opcion = 0;
    bool esCorriente = cuenta->getTipo().esCorriente();
    // Añade una opción más para eliminar cuenta
    //int numOpciones = esCorriente ? 9 : 6;
    string opcionesCorriente[9] = {
        "1. Consultar saldo",
        "2. Depositar dinero",
        "3. Retirar dinero",
        "4. Mostrar historial",
        "5. Mostrar estado de sobregiro",
        "6. Calcular intereses de sobregiro",
        "7. Simular sobregiro",
        "8. Regresar",
        "9. Eliminar cuenta"
    };
    string opcionesAhorro[6] = {
        "1. Consultar saldo",
        "2. Depositar dinero",
        "3. Retirar dinero",
        "4. Mostrar historial",
        "5. Regresar",
        "6. Eliminar cuenta"
    };
    bool regresar = false;
    bool cuentaEliminada = false;
    OperacionCuenta operacion(*cuenta);

    if (cuenta->getSaldo() < 0) {
        // Buscar la transacción de sobregiro más reciente para esta cuenta
        Fecha fechaSobregiro;
        bool encontrada = false;
        NodoTransaccion<Transaccion>* actual = listaTransacciones.getNodoCabeza();
        if (actual) {
            do {
                Transaccion trans = actual->getDato();
                if (trans.getCuenta().getIdCuenta() == cuenta->getIdCuenta() &&
                    trans.getTipoTransaccion().getTipo().find("Retiro-corriente") != std::string::npos) {
                    fechaSobregiro = trans.getFecha();
                    encontrada = true;
                }
                actual = actual->getSiguiente();
            } while (actual != listaTransacciones.getNodoCabeza());
        }
        if (encontrada) {
            std::tm tmFecha = {};
            tmFecha.tm_mday = fechaSobregiro.getDia();
            tmFecha.tm_mon = fechaSobregiro.getMes() - 1;
            tmFecha.tm_year = fechaSobregiro.getAnio() - 1900;
            tmFecha.tm_hour = fechaSobregiro.getHora();
            tmFecha.tm_min = fechaSobregiro.getMinutos();
            tmFecha.tm_sec = fechaSobregiro.getSegundos();
            std::time_t t = std::mktime(&tmFecha);

            operacion.setFechaInicioSobregiro(t);
        }
    }
    while (!regresar && !cuentaEliminada) {
        system("cls");
        cout << "===== Menu de Transacciones =====" << endl;
        cout << "Cuenta: " << cuenta->getTipo().getTipo() << " | ID: " << cuenta->getIdCuentaStr() << endl;
        cout << "Numero de cuenta bancario completo: " << cuenta->getNumeroCuentaCompleto() << endl;

        // Mostrar la fecha y hora actual del sistema
        Fecha fechaActual;
        fechaActual.inicializarConFechaActual();
        cout << "Fecha y hora actual: ";
        fechaActual.mostrarFechaHora();
        cout << endl;

        for (int i = 0; i < (esCorriente ? 9 : 6); i++) {
            if ((esCorriente && i == opcion) || (!esCorriente && i == opcion))
                cout << ">> " << (esCorriente ? opcionesCorriente[i] : opcionesAhorro[i]) << endl;
            else
                cout << "   " << (esCorriente ? opcionesCorriente[i] : opcionesAhorro[i]) << endl;
        }
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) { // Flecha arriba
                if (opcion > 0)
                    opcion--;
                else
                    opcion = (esCorriente ? 8 : 5);
            } else if (tecla == 80) { // Flecha abajo
                if (opcion < (esCorriente ? 8 : 5))
                    opcion++;
                else
                    opcion = 0;
            }
        } else if (tecla == 13) {
            if (!esCorriente) {
                switch (opcion) {
                    case 0:{
                        system("cls");
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        cout <<"tipo de transaccion: consulta de saldo" << endl;
                        // Mostrar la fecha y hora actual del sistema
                        Fecha fechaActual;
                        fechaActual.inicializarConFechaActual();
                        cout << "Fecha y hora actual: ";
                        fechaActual.mostrarFechaHora();
                        cout << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Consulta de saldo-ahorro"), cuenta->getSaldo(), cuenta->getFechaCreacion());
                        listaTransacciones.registrarTransaccionConFecha(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");

                        system("pause");
                    break;
                    }
                    case 1: {
                        system("cls");
                        if(double monto = pedirMontoSeguro("Ingrese monto a depositar: $")){
                            operacion += monto;
                            // Mostrar la fecha y hora actual del sistema
                            Fecha fechaActual;
                            fechaActual.inicializarConFechaActual();
                            cout << "Fecha y hora actual: ";
                            fechaActual.mostrarFechaHora();
                            cout << endl;
                            Transaccion transaccion(*cuenta, TipoTransaccion("Deposito-ahorro"), monto, cuenta->getFechaCreacion());
                            listaTransacciones.registrarTransaccionConFecha(transaccion);
                            listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                            listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                            listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                            TransaccionesUsuario::registrarTransaccion(cuenta->getIdCuenta(), monto);
                        }
                        system("pause");
                        break;
                    }
                    case 2: {
                        system("cls");
                        if(double monto = pedirMontoSeguro("Ingrese monto a retirar: $")){
                        operacion.retirarAhorroSimple(monto);
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        // Mostrar la fecha y hora actual del sistema
                        Fecha fechaActual;
                        fechaActual.inicializarConFechaActual();
                        cout << "Fecha y hora actual: ";
                        fechaActual.mostrarFechaHora();
                        cout << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Retiro-ahorro"), monto, cuenta->getFechaCreacion());
                        listaTransacciones.registrarTransaccionConFecha(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        TransaccionesUsuario::registrarTransaccion(cuenta->getIdCuenta(), -monto);
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        }
                        system("pause");
                        break;
                    }
                    case 3:{
                        system("cls");
                        cout << "Historial de transacciones" << endl;
                        listaTransacciones.mostrarTransacciones(cuenta->getIdCuenta(), "ahorro");
                        system("pause");
                        break;
                    }
                    case 4:
                        regresar = true;
                        break;
                    case 5: { // Eliminar cuenta
                        int confirmOpcion = 0;
                        string opcionesConfirm[] = {"Confirmar eliminacion", "Regresar"};
                        bool confirmar = false;
                        while (!confirmar) {
                            system("cls");
                            cout << "¿Seguro que desea eliminar su cuenta? Esta accion no se puede deshacer." << endl;
                            for (int i = 0; i < 2; i++) {
                                if (i == confirmOpcion)
                                    cout << ">> " << opcionesConfirm[i] << endl;
                                else
                                    cout << "   " << opcionesConfirm[i] << endl;
                            }
                            int teclaConf = _getch();
                            if (teclaConf == 224) {
                                teclaConf = _getch();
                                if (teclaConf == 72) { // arriba
                                    if (confirmOpcion > 0)
                                        confirmOpcion--;
                                    else
                                        confirmOpcion = 1;
                                } else if (teclaConf == 80) { // abajo
                                    if (confirmOpcion < 1)
                                        confirmOpcion++;
                                    else
                                        confirmOpcion = 0;
                                }
                            } else if (teclaConf == 13) {
                                if (confirmOpcion == 0) {
                                    bool eliminada = listaCuentas.eliminarCuentaPorCedulaYTipo(
                                        cuenta->getCedula(),
                                        cuenta->getTipo().getTipo()
                                    );
                                    if (eliminada) {
                                        cout << "Cuenta eliminada exitosamente." << endl;
                                        cuentaEliminada = true;
                                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                                    } else {
                                        cout << "No se pudo eliminar la cuenta." << endl;
                                    }
                                    system("pause");
                                }
                                confirmar = true;
                            }
                        }
                        break;
                    }
                }
            } else {
                switch (opcion) {
                    case 0:{
                        system("cls");
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        // Mostrar la fecha y hora actual del sistema
                        Fecha fechaActual;
                        fechaActual.inicializarConFechaActual();
                        cout << "Fecha y hora actual: ";
                        fechaActual.mostrarFechaHora();
                        cout << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Consulta de saldo-corriente"), cuenta->getSaldo(), cuenta->getFechaCreacion());
                        listaTransacciones.registrarTransaccionConFecha(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        system("pause");
                        break;}
                    case 1: {
                        system("cls");
                        if(double monto = pedirMontoSeguro("Ingrese monto a depositar: $")){
                        operacion += monto;
                        // Mostrar la fecha y hora actual del sistema
                        Fecha fechaActual;
                        fechaActual.inicializarConFechaActual();
                        cout << "Fecha y hora actual: ";
                        fechaActual.mostrarFechaHora();
                        cout << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Deposito-corriente"), monto, cuenta->getFechaCreacion());
                        listaTransacciones.registrarTransaccionConFecha(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        TransaccionesUsuario::registrarTransaccion(cuenta->getIdCuenta(), monto);
                        }
                        system("pause");
                        break;
                    }
                    case 2: {
                        system("cls");
                        if(double monto = pedirMontoSeguro("Ingrese monto a retirar: $")){
                        operacion -= monto;   
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        // Mostrar la fecha y hora actual del sistema
                        Fecha fechaActual;
                        fechaActual.inicializarConFechaActual();
                        cout << "Fecha y hora actual: ";
                        fechaActual.mostrarFechaHora();
                        cout << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Retiro-corriente"), monto, cuenta->getFechaCreacion());
                        listaTransacciones.registrarTransaccionConFecha(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        TransaccionesUsuario::registrarTransaccion(cuenta->getIdCuenta(), -monto);
                        }
                        system("pause");
                        break;
                    } 
                    case 3:{
                        system("cls");
                        cout << "Historial de transacciones" << endl;
                        listaTransacciones.mostrarTransacciones(cuenta->getIdCuenta(), "corriente");
                        system("pause");
                        break;}
                    case 4:{
                        system("cls");
                        operacion.mostrarEstadoSobregiro();
                        // Mostrar la fecha y hora actual del sistema
                        Fecha fechaActual;
                        fechaActual.inicializarConFechaActual();
                        cout << "Fecha y hora actual: ";
                        fechaActual.mostrarFechaHora();
                        cout << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Estado de sobregiro-corriente"), 0, cuenta->getFechaCreacion());
                        listaTransacciones.registrarTransaccionConFecha(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        system("pause");
                        break;}
                    case 5:{
                        system("cls");
                        operacion.mostrarEstadoSobregiro();
                        operacion.calcularInteresSobregiro();
                        // Mostrar la fecha y hora actual del sistema
                        Fecha fechaActual;
                        fechaActual.inicializarConFechaActual();
                        cout << "Fecha y hora actual: ";
                        fechaActual.mostrarFechaHora();
                        cout << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Calculo de interes de sobregiro-corriente"), 0, cuenta->getFechaCreacion());
                        listaTransacciones.registrarTransaccionConFecha(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        system("pause");
                        break;
                    }

                    case 6:
                        system("cls");
                        SimuladorSobregiro::calcularPagoSobregiro(cuenta);
                        system("pause");
                        break;

                    case 7:
                        regresar = true;
                        break;
                        
                    case 8: { // Eliminar cuenta
                        int confirmOpcion = 0;
                        string opcionesConfirm[] = {"Confirmar eliminacion", "Regresar"};
                        bool confirmar = false;
                        while (!confirmar) {
                            system("cls");
                            cout << "¿Seguro que desea eliminar su cuenta? Esta accion no se puede deshacer." << endl;
                            for (int i = 0; i < 2; i++) {
                                if (i == confirmOpcion)
                                    cout << ">> " << opcionesConfirm[i] << endl;
                                else
                                    cout << "   " << opcionesConfirm[i] << endl;
                            }
                            int teclaConf = _getch();
                            if (teclaConf == 224) {
                                teclaConf = _getch();
                                if (teclaConf == 72) { // arriba
                                    if (confirmOpcion > 0)
                                        confirmOpcion--;
                                    else
                                        confirmOpcion = 1;
                                } else if (teclaConf == 80) { // abajo
                                    if (confirmOpcion < 1)
                                        confirmOpcion++;
                                    else
                                        confirmOpcion = 0;
                                }
                            } else if (teclaConf == 13) {
                                if (confirmOpcion == 0) {
                                    bool eliminada = listaCuentas.eliminarCuentaPorCedulaYTipo(
                                        cuenta->getCedula(),
                                        cuenta->getTipo().getTipo()
                                    );
                                    if (eliminada) {
                                        cout << "Cuenta eliminada exitosamente." << endl;
                                        cuentaEliminada = true;
                                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                                    } else {
                                        cout << "No se pudo eliminar la cuenta." << endl;
                                    }
                                    system("pause");
                                }
                                confirmar = true;
                            }
                        }
                        break;
                    }
                    case 9:
                        regresar = true;
                        break;
                }
            }
        }
    }
}

Cuenta* submenuTipoCuentaUsuario(Cuenta* cuentasUsuario[2], int cuentaCount) {
    if (cuentaCount == 1) {
        return cuentasUsuario[0];
    }
    int opcion = 0;
    while (true) {
        system("cls");
        cout << "=== Seleccione la cuenta para operar ===" << endl;
        for (int i = 0; i < cuentaCount; i++) {
            string tipo = cuentasUsuario[i]->getTipo().getTipo();
            string id = cuentasUsuario[i]->getIdCuentaStr();
            if (i == opcion)
                cout << ">> " << tipo << "    | ID: " << id << endl;
            else
                cout << "   " << tipo << "  | ID: " << id << endl;
        }
        int tecla = _getch();
        if (tecla == 224) { // Tecla especial
            tecla = _getch();
        if (tecla == 72) { // Flecha arriba
            if (opcion > 0)
                opcion--;
            else
                opcion = 1; // Si está en la primera opción, va a la última
        } else if (tecla == 80) { // Flecha abajo
            if (opcion < 1)
                opcion++;
            else
            opcion = 0; // Si está en la última opción, va a la primera
        }
        } else if (tecla == 13) { // Enter
            return cuentasUsuario[opcion];
        }
    }
}

void menuConsultasAvanzadas() {
    int opcion = 0;
    string opciones[] = {
        "1. Buscar cuenta por nombre y apellido",
        "2. Buscar cuenta por ID",
        "3. Buscar cuenta por cedula",
        "4. Buscar transacciones por fecha",
        "5. Buscar transacciones por dato",
        "6. Buscar cuentas por sucursal",
        "7. Buscar cuentas por fecha y sucursal",
        "8. Regresar"
    };
    bool regresar = false;
    while (!regresar) {
        system("cls");
        cout << "===== Consultas Avanzadas =====" << endl;
        for (int i = 0; i < 8; i++) {
            if (i == opcion)
                cout << ">> " << opciones[i] << endl;
            else
                cout << "   " << opciones[i] << endl;
        }
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) { // Flecha arriba
            if (opcion > 0)
                opcion--;
            else
                opcion = 7; // Si está en la primera opción, va a la última
            } else if (tecla == 80) { // Flecha abajo
            if (opcion < 7)
                opcion++;
            else
            opcion = 0; // Si está en la última opción, va a la primera
            }
        } else if (tecla == 13) {
            system("cls");
            switch (opcion) {
                case 0: { // Buscar por nombre

                    string nombre = Validar::pedirNombre() + " " + Validar::pedirApellido();
                    listaCuentas.buscarCuentasPorNombre(nombre); // Debes implementar este método en ListaCuenta
                    system("pause");
                    break;
                }

                case 1: { // Buscar por ID
                    string idStr = Validar::pedirIdCuenta();
                    Cuenta* cuenta = listaCuentas.buscarCuentaPorId(idStr); // Debes implementar este método en ListaCuenta
                    if (cuenta) {
                        listaCuentas.mostrarCuentaPorId(idStr); // Solo muestra la cuenta encontrada
                    } else {
                        cout << "No se encontro ninguna cuenta con ese ID." << endl;
                    }
                    system("pause");
                    break;
                }
                case 2: { // Buscar por cedula
                    string cedula = Validar::pedirCedula();
                    listaCuentas.buscarCuentasPorCedula(cedula); // Debes implementar este método en ListaCuenta

                    system("pause");
                    break;
                }
                case 3: { // Buscar transacciones por fecha
                    Fecha fecha = Validar::pedirFecha();
                    
                    listaTransacciones.mostrarTransaccionesPorFecha(fecha.getDia(), fecha.getMes(), fecha.getAnio());
                    system("pause");
                    break;
                }
                case 4: { // Buscar transacciones por cuenta y fecha
                    string dato = Validar::pedirDato();
                    listaCuentas.buscarCuentasPorDato(dato); // Debes implementar este método en ListaTransaccion
                    system("pause");

                    break;
                }
                case 5: { // Buscar cuentas por sucursal
                    Sucursal sucursal = seleccionarSucursal(sucursales);
                    listaCuentas.buscarCuentasPorSucursal(sucursal.getNombre()); // Debes implementar este método en ListaCuenta
                    system("pause");
                    break;
                }
                case 6: { 
                    Fecha fecha = Validar::pedirFecha();
                    Sucursal sucursal = seleccionarSucursal(sucursales);
                    listaCuentas.buscarCuentasPorFechaYSucursal(fecha.getDia(), fecha.getMes(), fecha.getAnio(), sucursal.getNombre());
                    system("pause");
                    break;
                }
                case 7: // Regresar
                    regresar = true;
                    break;
            }
        }
    }
}

// Genera un backup de transacciones.txt  con fecha y hora en el nombre
void generarBackupTransacciones() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    // Generar nombres de backup con fecha y hora
    char nombreBackup1[120];
    sprintf(nombreBackup1, "transacciones1_backup_%04d_%02d_%02d_%02d_%02d_%02d.txt",
        1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
        ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    char nombreBackup2[120];
    sprintf(nombreBackup2, "transacciones_backup_%04d_%02d_%02d_%02d_%02d_%02d.txt",
        1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
        ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    // Backup para transacciones1.txt
    FILE* origen1 = fopen("transacciones1.txt", "rb");
    if (origen1) {
        FILE* destino1 = fopen(nombreBackup1, "wb");
        if (destino1) {
            char buffer[4096];
            size_t bytes;
            while ((bytes = fread(buffer, 1, sizeof(buffer), origen1)) > 0) {
                fwrite(buffer, 1, bytes, destino1);
            }
            fclose(destino1);
            std::cout << "Backup generado: " << nombreBackup1 << std::endl;
        } else {
            std::cout << "No se pudo crear el archivo de backup para transacciones1.txt." << std::endl;
        }
        fclose(origen1);
    } else {
        std::cout << "No existe transacciones1.txt para respaldar." << std::endl;
    }

    // Backup para transacciones.txt
    FILE* origen2 = fopen("transacciones.txt", "rb");
    if (origen2) {
        FILE* destino2 = fopen(nombreBackup2, "wb");
        if (destino2) {
            char buffer[4096];
            size_t bytes;
            while ((bytes = fread(buffer, 1, sizeof(buffer), origen2)) > 0) {
                fwrite(buffer, 1, bytes, destino2);
            }
            fclose(destino2);
            std::cout << "Backup generado: " << nombreBackup2 << std::endl;
        } else {
            std::cout << "No se pudo crear el archivo de backup para transacciones.txt." << std::endl;
        }
        fclose(origen2);
    } else {
        std::cout << "No existe transacciones.txt para respaldar." << std::endl;
    }
}

void abrirAyuda() {
    system("\"C:\\Users\\anatu\\Documents\\Estructuras\\Proyecto Version 1.4\\Proyecto-Banco-Estructuras-Parcial-1\\abrirAyuda.exe\"");
}

void restaurarBackupTransacciones() {
    std::vector<std::string> backups1, backups2;
    DIR* dir = opendir(".");
    if (!dir) {
        std::cout << "No se pudo abrir el directorio actual." << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string nombre(entry->d_name);
        if (nombre.find("transacciones1_backup") == 0 && nombre.find(".txt") != std::string::npos) {
            backups1.push_back(nombre);
        } else if (nombre.find("transacciones_backup") == 0 && nombre.find(".txt") != std::string::npos) {
            backups2.push_back(nombre);
        }
    }
    closedir(dir);

    if (backups1.empty() && backups2.empty()) {
        std::cout << "No hay backups disponibles." << std::endl;
        system("pause");
        return;
    }

    // Restaurar transacciones1.txt
    if (!backups1.empty()) {
        int seleccion1 = 0;
        while (true) {
            system("cls");
            std::cout << "Seleccione el backup para transacciones1.txt a restaurar:" << std::endl;
            for (size_t i = 0; i < backups1.size(); ++i) {
                if ((int)i == seleccion1)
                    std::cout << ">> " << backups1[i] << std::endl;
                else
                    std::cout << "   " << backups1[i] << std::endl;
            }

            int tecla = _getch();
            if (tecla == 224) {
                tecla = _getch();
                if (tecla == 72) { // flecha arriba
                    if (seleccion1 > 0) seleccion1--;
                    else seleccion1 = backups1.size() - 1;
                } else if (tecla == 80) { // flecha abajo
                    if (seleccion1 < (int)backups1.size() - 1) seleccion1++;
                    else seleccion1 = 0;
                }
            } else if (tecla == 13) { // enter
                FILE* origen1 = fopen(backups1[seleccion1].c_str(), "rb");
                if (!origen1) {
                    std::cout << "No se pudo abrir el backup seleccionado." << std::endl;
                    system("pause");
                    continue;
                }

                const char* destinoNombre1 = "transacciones1.txt";
                FILE* destino1 = fopen(destinoNombre1, "wb");
                if (!destino1) {
                    std::cout << "No se pudo restaurar el archivo." << std::endl;
                    fclose(origen1);
                    system("pause");
                    continue;
                }

                char buffer[4096];
                size_t bytes;
                while ((bytes = fread(buffer, 1, sizeof(buffer), origen1)) > 0) {
                    fwrite(buffer, 1, bytes, destino1);
                }

                fclose(origen1);
                fclose(destino1);
                std::cout << "Backup restaurado: " << backups1[seleccion1] << " -> " << destinoNombre1 << std::endl;
                system("pause");
                break;
            }
        }
    }

    // Restaurar transacciones.txt
    if (!backups2.empty()) {
        int seleccion2 = 0;
        while (true) {
            system("cls");
            std::cout << "Seleccione el backup para transacciones.txt a restaurar:" << std::endl;
            for (size_t i = 0; i < backups2.size(); ++i) {
                if ((int)i == seleccion2)
                    std::cout << ">> " << backups2[i] << std::endl;
                else
                    std::cout << "   " << backups2[i] << std::endl;
            }

            int tecla = _getch();
            if (tecla == 224) {
                tecla = _getch();
                if (tecla == 72) { // flecha arriba
                    if (seleccion2 > 0) seleccion2--;
                    else seleccion2 = backups2.size() - 1;
                } else if (tecla == 80) { // flecha abajo
                    if (seleccion2 < (int)backups2.size() - 1) seleccion2++;
                    else seleccion2 = 0;
                }
            } else if (tecla == 13) { // enter
                FILE* origen2 = fopen(backups2[seleccion2].c_str(), "rb");
                if (!origen2) {
                    std::cout << "No se pudo abrir el backup seleccionado." << std::endl;
                    system("pause");
                    continue;
                }

                const char* destinoNombre2 = "transacciones.txt";
                FILE* destino2 = fopen(destinoNombre2, "wb");
                if (!destino2) {
                    std::cout << "No se pudo restaurar el archivo." << std::endl;
                    fclose(origen2);
                    system("pause");
                    continue;
                }

                char buffer[4096];
                size_t bytes;
                while ((bytes = fread(buffer, 1, sizeof(buffer), origen2)) > 0) {
                    fwrite(buffer, 1, bytes, destino2);
                }

                fclose(origen2);
                fclose(destino2);
                std::cout << "Backup restaurado: " << backups2[seleccion2] << " -> " << destinoNombre2 << std::endl;
                system("pause");
                break;
            }
        }
    }
}

void menuOrdenarCuentas() {
    int opcion = 0;
    std::string opciones[] = {
        "1. Ordenar por nombre A-Z",
        "2. Ordenar por nombre Z-A",
        "3. Ordenar por apellido A-Z",
        "4. Ordenar por apellido Z-A",
        "5. Ordenar por fecha mas antigua de creacion",
        "6. Ordenar por fecha mas nueva de creacion",
        "7. Regresar"
    };
    bool regresar = false;
    while (!regresar) {
        system("cls");
        std::cout << "===== Ordenar cuentas =====" << std::endl;
        for (int i = 0; i < 7; i++) {
            if (i == opcion)
                std::cout << ">> " << opciones[i] << std::endl;
            else
                std::cout << "   " << opciones[i] << std::endl;
        }
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) { // Flecha arriba
                if (opcion > 0)
                    opcion--;
                else
                    opcion = 6;
            } else if (tecla == 80) { // Flecha abajo
                if (opcion < 6)
                    opcion++;
                else
                    opcion = 0;
            }
        } else if (tecla == 13) {
            switch (opcion) {
                case 0:
                    listaCuentas.ordenarPorCampo(0);
                    std::cout << "Cuentas ordenadas por nombre A-Z:" << std::endl;
                    listaCuentas.mostrarCuentasConFecha();
                    system("pause");
                    break;
                case 1:
                    listaCuentas.ordenarPorCampo(4);
                    std::cout << "Cuentas ordenadas por nombre Z-A:" << std::endl;
                    listaCuentas.mostrarCuentasConFecha();
                    system("pause");
                    break;
                case 2:
                    listaCuentas.ordenarPorCampo(1);
                    std::cout << "Cuentas ordenadas por apellido A-Z:" << std::endl;
                    listaCuentas.mostrarCuentasConFecha();
                    system("pause");
                    break;
                case 3:
                    listaCuentas.ordenarPorCampo(5);
                    std::cout << "Cuentas ordenadas por apellido Z-A:" << std::endl;
                    listaCuentas.mostrarCuentasConFecha();
                    system("pause");
                    break;                   
                case 4:
                    listaCuentas.ordenarPorCampo(2);
                    std::cout << "Cuentas ordenadas por fecha mas antigua de creacion:" << std::endl;
                    listaCuentas.mostrarCuentasConFecha();
                    system("pause");
                    break;
                case 5:
                    listaCuentas.ordenarPorCampo(3);
                    std::cout << "Cuentas ordenadas por fecha mas nueva de creacion:" << std::endl;
                    listaCuentas.mostrarCuentasConFecha();
                    system("pause");
                    break;
                case 6:
                    regresar = true;
                    break;
            }
        }
    }
}

void calcularHashArchivo(const std::string& nombreArchivo) {
    std::string comando = "CertUtil -hashfile \"" + nombreArchivo + "\" SHA256 > hash_temp.txt";
    system(comando.c_str());

    std::ifstream hashFile("hash_temp.txt");
    std::string linea;
    std::cout << "Hash SHA-256 del archivo " << nombreArchivo << ":\n";
    int lineCount = 0;
    while (std::getline(hashFile, linea)) {
        lineCount++;
        if (lineCount == 2) { // La segunda línea contiene el hash
            std::cout << linea << std::endl;
        }
    }
    hashFile.close();
    std::remove("hash_temp.txt");
}

void guardarHashArchivo(const std::string& nombreArchivo) {
    std::string comando = "CertUtil -hashfile \"" + nombreArchivo + "\" SHA256 > hash_temp.txt";
    system(comando.c_str());

    std::ifstream hashFile("hash_temp.txt");
    std::string linea, hash;
    int lineCount = 0;
    while (std::getline(hashFile, linea)) {
        lineCount++;
        if (lineCount == 2) { // La segunda línea contiene el hash
            hash = linea;
            break;
        }
    }
    hashFile.close();
    std::remove("hash_temp.txt");

    // Guardar el hash en un archivo .hash.txt junto al archivo cifrado
    std::string hashFileName = nombreArchivo + ".hash.txt";
    std::ofstream out(hashFileName);
    out << "SHA-256: " << hash << std::endl;
    out.close();
}

int main() {
    // Cargar cuentas desde el archivo si existe
    listaCuentas.cargarCuentasDesdeArchivo("cuentas.txt");
    listaTransacciones.cargarTransaccionesDesdeArchivo("transacciones.txt"); // Inicializa
    cargarCitasDesdeArchivo("citas.txt", sucursales);

    // Verificar si hay cuentas y establecer el contador adecuadamente
    if (!listaCuentas.getNodoCabeza()) {
        contadorId = 1; // Reiniciar el contador si no hay cuentas
        guardarUltimoIdCuenta(0);
    } else {
        contadorId = leerUltimoIdCuenta() + 1;
    }
    
    int opcion = 0;
    bool salir = false;
    while (!salir) {
        imprimirMenu(opcion);
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) {
                if (opcion > 0)
                    opcion--;
                else
                    opcion = 14; // Ahora hay 12 opciones (0-11)
            } else if (tecla == 80) {
                if (opcion < 14)
                    opcion++;
                else
                    opcion = 0;
            }
        } else if (tecla == 13) {
            switch (opcion) {
                case 0: { // Crear nueva cuenta
                    int tipo = submenuTipoCuenta();
                    if (tipo == 2) // Regresar
                        break;

                    Sucursal sucursalSeleccionada = seleccionarSucursal(sucursales);
                    
                    string nombre, apellido, cedula;

                    cedula = Validar::pedirCedula();
                    
                    // Busca cita para este cliente en la sucursal seleccionada
                    std::vector<Cita>& citasSucursal = citasPorSucursal[sucursalSeleccionada.getCodigo()];
                    bool tieneCita = false;
                    Fecha fechaCita;
                    for (const auto& cita : citasSucursal) {
                        if (cita.getCedula() == (cedula)) {
                            tieneCita = true;
                            fechaCita = cita.getFecha();
                            break;
                        }
                    }

                    Fecha fechaActual;
                    fechaActual.inicializarConFechaActual();

                    if (!tieneCita) {
                        cout << "No tiene una cita asignada para apertura de cuenta en esta sucursal.\n";
                        cout << "Por favor, solicite una cita antes de crear su cuenta.\n";
                        system("pause");
                        break;
                    } else if (fechaActual < fechaCita) {
                        cout << "Su cita para apertura de cuenta es el ";
                        fechaCita.mostrarFechaHora();
                        cout << ".\nPor favor, espere hasta la fecha y hora de su cita.\n";
                        system("pause");
                        break;
                    }

                    system("cls");
                    // Pedir cédula con validación (ya valida dentro del método)
                    cout << "Tiene una cita para apertura de cuenta en esta sucursal.\n";
                    cout << "Fecha de la cita: ";
                    fechaCita.mostrarFechaHora();
                    cout << endl;

                    // Determinar tipo de cuenta
                    TipoCuenta tipoCuenta(tipo == 0 ? "ahorros" : "corriente");

                    // Verificar si ya existe una cuenta de ese tipo para esa cedula
                    Cuenta* cuentaMismaTipo = listaCuentas.buscarCuentaPorCedulaYTipo(cedula, tipoCuenta.getTipo());
                    if (cuentaMismaTipo) {
                        cout << "Ya existe una cuenta de tipo " << tipoCuenta.getTipo() << " para esta cedula." << endl;
                        system("pause");
                        break;
                    }

                    // Buscar si ya existe alguna cuenta con esa cédula (para usar datos)
                    Cuenta* cuentaExistente = listaCuentas.buscarCuentaPorCedula(cedula);

                    string contrasena;
                    if (cuentaExistente) {
                        nombre = cuentaExistente->getNombre();
                        apellido = cuentaExistente->getApellido();
                        contrasena = cuentaExistente->getContrasena();
                        cout << "Usuario ya registrado. Se usaran los datos existentes." << endl;
                    } else {
                        nombre = Validar::pedirNombre();
                        apellido = Validar::pedirApellido();
                        contrasena = ContrasenaUsuario::generarContrasenaBancaria();
                    }

                    Persona persona(cedula, nombre, apellido);
                    double saldoInicial = 0.0; // Saldo inicial en 0
                    Cuenta cuenta(persona, saldoInicial, tipoCuenta, sucursalSeleccionada); // <-- Pasa el objeto Sucursal aquí
                    cuenta.setContrasena(contrasena);
                    listaCuentas.insertarCuenta(cuenta);
                    listaCuentas.guardarCuentasEnArchivo("cuentas.txt"); // Guardar solo después de insertar
                    guardarUltimoIdCuenta(contadorId - 1);

                    cout << "Cuenta creada exitosamente con ID: " << cuenta.getIdCuentaStr() << endl;
                    cout << "Sucursal: " << cuenta.getSucursal().getNombre() << endl; // Muestra el nombre de la sucursal
                    cout << "Numero de cuenta bancario completo: " << cuenta.getNumeroCuentaCompleto() << endl;
                    cout << "Su contrasena bancaria es: " << contrasena << endl;
                    
                    // Eliminar la cita de la sucursal (por cédula)
                    for (auto it = citasSucursal.begin(); it != citasSucursal.end(); ++it) {
                        if (it->getCedula() == cedula) {
                            citasSucursal.erase(it);
                            break;
                        }
                    }
                    guardarCitasEnArchivo("citas.txt");

                    system("pause");
                    break;
                }
                case 1: { // Iniciar sesion para tramites
                    system("cls");
                    // Verifica si hay cuentas
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    string cedula, contrasena;
                    // Pedir cedula
                    cedula = Validar::pedirCedula();
                    // Pedir contraseña
                    contrasena = Validar::pedirContrasena();
                
                    Cuenta* cuentasUsuario[2] = {nullptr, nullptr};
                    int cuentaCount = listaCuentas.buscarCuentasPorCedulaYContrasena(cedula, contrasena, cuentasUsuario);
                    if (cuentaCount == 0) {
                        cout << "\nUsuario o contrasena incorrectos." << endl;
                        system("pause");
                        break;
                    }
                    // Registrar acceso exitoso
                    AccesoUsuario::registrarAcceso(cedula);
                    Cuenta* cuentaSeleccionada = nullptr;
                    if (cuentaCount == 1) {
                        cuentaSeleccionada = cuentasUsuario[0];
                    } else {
                        cuentaSeleccionada = submenuTipoCuentaUsuario(cuentasUsuario, cuentaCount);
                    }
                    menuTransacciones(cuentaSeleccionada);
                    break;
                }
                case 2:
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    menuConsultasAvanzadas();
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    generarBackupTransacciones();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    restaurarBackupTransacciones();
                    system("pause");
                    break;
                case 5: // Generar archivo binario
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    CuentaBinario::txtACuentasBinario("cuentas.txt", "cuentas.dat");
                    cout << "Archivo binario generado exitosamente." << endl;
                    system("pause");
                    break;
                case 6: { // Cifrar Backup
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    std::string archivoOriginal = Validar::pedirNombreArchivoBackup(); 
                    std::string archivoCifrado = Validar::pedirNombreArchivoCifrado(); 
                    int clave = Validar::pedirClaveNumerica();

                    CifradoCesar::cifrarArchivo(archivoOriginal, archivoCifrado, clave);
                    std::cout << "Archivo cifrado correctamente." << std::endl;

                    // Guardar el hash del archivo cifrado
                    guardarHashArchivo(archivoCifrado);

                    std::cout << "Hash SHA-256 guardado en: " << archivoCifrado << ".hash.txt" << std::endl;

                    system("pause");
                    break;
                }
                case 7: { // Descifrar Backup
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    std::string archivoCifrado = Validar::pedirNombreArchivoBackupCi();
                    std::string archivoDescifrado = Validar::pedirNombreArchivoDecifrado();
                    int clave = Validar::pedirClaveNumerica();
                    CifradoCesar::descifrarArchivo(archivoCifrado, archivoDescifrado, clave);
                    std::cout << "Archivo descifrado correctamente." << std::endl;
                    system("pause");
                    break;
                }
                case 8: // Ordenar cuentas
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    menuOrdenarCuentas();
                    break;
                case 9: // Ayuda
                    abrirAyuda();
                    break;
                case 10: { // Pico de acceso de usuario
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    std::string cedula = Validar::pedirCedula();
                    AccesoUsuario::mostrarPicoAcceso(cedula);
                    system("pause");
                    break;
                }
                case 11: { // Pico de transacciones de usuario
                    system("cls");
                    if (!listaCuentas.getNodoCabeza()) {
                        cout << "No hay cuentas registradas en el sistema." << endl;
                        system("pause");
                        break;
                    }
                    std::string idCuenta = Validar::pedirIdCuenta();
                    TransaccionesUsuario::mostrarPicoTransacciones(idCuenta);
                    system("pause");
                    break;
                }
                
                case 12: { // Asignar cita para apertura de cuenta
                    Sucursal sucursal = seleccionarSucursal(sucursales);
                    system("cls");
                    std::string cedula = Validar::pedirCedula();

                    bool yaTieneCita = false;
                    for (const auto& par : citasPorSucursal) {
                        for (const auto& cita : par.second) {
                            if (cita.getCedula() == cedula) {
                                yaTieneCita = true;
                                break;
                            }
                        }
                        if (yaTieneCita) break;
                    }
                    if (yaTieneCita) {
                        std::cout << "Ya tiene una cita registrada en alguna sucursal. No puede agendar otra.\n";
                        system("pause");
                        break;
                    }

                    std::string cliente = Validar::pedirApellido() + " " + Validar::pedirNombre();
                    Fecha fechaDeseada = Validar::pedirFecha(); // Debe incluir hora y minutos
                    int intervalo = 30; // minutos entre citas
                    fechaDeseada.inicializarConFechaActual();
                    asignarCitaSucursal(sucursal, cliente, cedula, fechaDeseada, intervalo);
                    guardarCitasEnArchivo("citas.txt");
                    // Mostrar distancias entre citas de esa sucursal
                    mostrarDistanciasEntreCitas(citasPorSucursal[sucursal.getCodigo()]);
                    
                    system("pause");
                    break;
                }
                case 13: { // Mostrar distancia D de una cita específica
                    Sucursal sucursal = seleccionarSucursal(sucursales);
                    Fecha fechaBuscada = Validar::pedirFecha();
                    mostrarDistanciaBinariaEntreCitas(citasPorSucursal[sucursal.getCodigo()], fechaBuscada);
                    system("pause");
                    break;
                }
                case 14: // Salir
                    salir = true;
                    break;
            }
        }
    }
    system("cls");
    cout << "Gracias por usar el Sistema Bancario." << endl;
    return 0;
}