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

using namespace std;

ListaCuenta<Cuenta> listaCuentas;
ListaTransaccion<Transaccion> listaTransacciones;

unsigned long long contadorId = 1;

int leerUltimoIdCuenta() {
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
        "9. Ayuda",
        "10. Salir"
    };
    for (int i = 0; i < 10; i++) {
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
        "7. Pagar sobregiro",
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
    while (!regresar && !cuentaEliminada) {
        system("cls");
        cout << "===== Menu de Transacciones =====" << endl;
        cout << "Cuenta: " << cuenta->getTipo().getTipo() << " | ID: " << cuenta->getIdCuentaStr() << endl;
        Fecha fechaCreacion = cuenta->getFechaCreacion();
        cout << "Fecha de creacion: " << fechaCreacion.getDia() << "/" << fechaCreacion.getMes() << "/" << fechaCreacion.getAnio() << endl;
        for (int i = 0; i < (esCorriente ? 9 : 6); i++) {
            if ( (esCorriente && i == opcion) || (!esCorriente && i == opcion) )
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
                        cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                             << cuenta->getFechaCreacion().getMes() << "/" 
                             << cuenta->getFechaCreacion().getAnio() << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Consulta de saldo-ahorro"), cuenta->getSaldo(), cuenta->getFechaCreacion());
                        listaTransacciones.insertarTransaccion(transaccion);
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
                                                    cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                            << cuenta->getFechaCreacion().getMes() << "/" 
                            << cuenta->getFechaCreacion().getAnio() << endl;
                            Transaccion transaccion(*cuenta, TipoTransaccion("Deposito-ahorro"), monto, cuenta->getFechaCreacion());
                            listaTransacciones.insertarTransaccion(transaccion);
                            listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                            listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                            listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        }
                        system("pause");
                        break;
                    }
                    case 2: {
                        system("cls");
                        if(double monto = pedirMontoSeguro("Ingrese monto a retirar: $")){
                        operacion.retirarAhorroSimple(monto);
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                             << cuenta->getFechaCreacion().getMes() << "/" 
                             << cuenta->getFechaCreacion().getAnio() << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Retiro-ahorro"), monto, cuenta->getFechaCreacion());
                        listaTransacciones.insertarTransaccion(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");

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
                        cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                             << cuenta->getFechaCreacion().getMes() << "/" 
                             << cuenta->getFechaCreacion().getAnio() << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Consulta de saldo-corriente"), cuenta->getSaldo(), cuenta->getFechaCreacion());
                        listaTransacciones.insertarTransaccion(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        system("pause");
                        break;}
                    case 1: {
                        system("cls");
                        if(double monto = pedirMontoSeguro("Ingrese monto a depositar: $")){
                        operacion += monto;
                        cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                             << cuenta->getFechaCreacion().getMes() << "/" 
                             << cuenta->getFechaCreacion().getAnio() << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Deposito-corriente"), monto, cuenta->getFechaCreacion());
                        listaTransacciones.insertarTransaccion(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        }
                        system("pause");
                        break;
                    }
                    case 2: {
                        system("cls");
                        if(double monto = pedirMontoSeguro("Ingrese monto a retirar: $")){
                        operacion -= monto;   
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                             << cuenta->getFechaCreacion().getMes() << "/" 
                             << cuenta->getFechaCreacion().getAnio() << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Retiro-corriente"), monto, cuenta->getFechaCreacion());
                        listaTransacciones.insertarTransaccion(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
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
                        cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                             << cuenta->getFechaCreacion().getMes() << "/" 
                             << cuenta->getFechaCreacion().getAnio() << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Estado de sobregiro-corriente"), 0, cuenta->getFechaCreacion());
                        listaTransacciones.insertarTransaccion(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        system("pause");
                        break;}
                    case 5:{
                        system("cls");
                        operacion.calcularInteresSobregiro();
                        cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                             << cuenta->getFechaCreacion().getMes() << "/" 
                             << cuenta->getFechaCreacion().getAnio() << endl;
                        Transaccion transaccion(*cuenta, TipoTransaccion("Calculo de interes de sobregiro-corriente"), 0, cuenta->getFechaCreacion());
                        listaTransacciones.insertarTransaccion(transaccion);
                        listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                        listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                        listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                        system("pause");
                        break;
                    }
                    case 6: {
                        system("cls");
                        // Solo permite pagar hasta el monto pendiente de sobregiro
                        //double montoMax = operacion.operator-(0); // saldo - 0 = saldo actual
                        double montoPagar;
                        cout << "Ingrese monto a pagar de sobregiro: $";
                        while (true) {
                            montoPagar = pedirMontoSeguro("");
                            // Para obtener el monto pendiente de sobregiro:
                            // Usamos un cast a double para acceder al atributo privado (no hay getter, así que mejor pedirlo al usuario y validar en pagarSobregiro)
                            if (montoPagar > 0 && montoPagar <= 5000) { // 5000 es arbitrario, el método ya valida el monto real
                                operacion.pagarSobregiro(montoPagar);
                                cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                                cout << "Fecha: " << cuenta->getFechaCreacion().getDia() << "/" 
                                    << cuenta->getFechaCreacion().getMes() << "/" 
                                    << cuenta->getFechaCreacion().getAnio() << endl;
                                Transaccion transaccion(*cuenta, TipoTransaccion("Pago de sobregiro-corriente"), montoPagar, cuenta->getFechaCreacion());
                                listaTransacciones.insertarTransaccion(transaccion);
                                listaTransacciones.guardarTransaccionesEnArchivo("transacciones1.txt");
                                listaTransacciones.guardarTransaccionesEnArchivoPr("transacciones.txt");
                                listaCuentas.guardarCuentasEnArchivo("cuentas.txt");
                                break;
                            } else {
                                cout << "Monto invalido. Intente de nuevo: $";
                            }
                        }

                        system("pause");
                        break;
                    }
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
        "6. Regresar"
    };
    bool regresar = false;
    while (!regresar) {
        system("cls");
        cout << "===== Consultas Avanzadas =====" << endl;
        for (int i = 0; i < 6; i++) {
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
                opcion = 5; // Si está en la primera opción, va a la última
            } else if (tecla == 80) { // Flecha abajo
            if (opcion < 5)
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
                case 5: // Regresar
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
    char nombreBackup[120];
    sprintf(nombreBackup, "transacciones_backup_%04d_%02d_%02d_%02d_%02d_%02d.txt",
        1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
        ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
  

    // Backup ahorro
    FILE* origen = fopen("transacciones.txt", "rb");
    if (origen) {
        FILE* destino = fopen(nombreBackup, "wb");
        if (destino) {
            char buffer[4096];
            size_t bytes;
            while ((bytes = fread(buffer, 1, sizeof(buffer), origen)) > 0) {
                fwrite(buffer, 1, bytes, destino);
            }
            fclose(destino);
            std::cout << "Backup generado: " << nombreBackup << std::endl;
        } else {
            std::cout << "No se pudo crear el archivo de backup de ahorro." << std::endl;
        }
        fclose(origen);
    } else {
        std::cout << "No existe transacciones.txt para respaldar." << std::endl;
    }
}

void restaurarBackupTransacciones() {
    
    std::vector<std::string> backups;
    DIR* dir = opendir(".");
    if (!dir) {
        std::cout << "No se pudo abrir el directorio actual." << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string nombre(entry->d_name);
        if (nombre.find("transacciones_backup") == 0 && nombre.find(".txt") != std::string::npos) {
            backups.push_back(nombre);
        }
    }
    closedir(dir);

    if (backups.empty()) {
        std::cout << "No hay backups disponibles." << std::endl;
        system("pause");
        return;
    }

    int seleccion = 0;
    while (true) {
        system("cls");
        std::cout << "Seleccione el backup a restaurar:" << std::endl;
        for (size_t i = 0; i < backups.size(); ++i) {
            if ((int)i == seleccion)
                std::cout << ">> " << backups[i] << std::endl;
            else
                std::cout << "   " << backups[i] << std::endl;
        }

        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) { // flecha arriba
                if (seleccion > 0) seleccion--;
                else seleccion = backups.size() - 1;
            } else if (tecla == 80) { // flecha abajo
                if (seleccion < (int)backups.size() - 1) seleccion++;
                else seleccion = 0;
            }
        } else if (tecla == 13) { // enter
            FILE* origen = fopen(backups[seleccion].c_str(), "rb");
            if (!origen) {
                std::cout << "No se pudo abrir el backup seleccionado." << std::endl;
                system("pause");
                continue;
            }

            const char* destinoNombre = "transacciones.txt";
            FILE* destino = fopen(destinoNombre, "wb");
            if (!destino) {
                std::cout << "No se pudo restaurar el archivo." << std::endl;
                fclose(origen);
                system("pause");
                continue;
            }

            char buffer[4096];
            size_t bytes;
            while ((bytes = fread(buffer, 1, sizeof(buffer), origen)) > 0) {
                fwrite(buffer, 1, bytes, destino);
            }

            fclose(origen);
            fclose(destino);
            std::cout << "Backup restaurado: " << backups[seleccion] << " -> " << destinoNombre << std::endl;
            system("pause");
            break;
        }
    }
}

int main() {
    // Cargar cuentas desde el archivo si existe
    listaCuentas.cargarCuentasDesdeArchivo("cuentas.txt");
    listaTransacciones.cargarTransaccionesDesdeArchivo("transacciones.txt"); // Inicializa
    

    int opcion = 0;
    bool salir = false;
    while (!salir) {
        imprimirMenu(opcion);
        int tecla = _getch();
        if (tecla == 224) { // Tecla especial
            tecla = _getch();
        if (tecla == 72) { // Flecha arriba
            if (opcion > 0)
                opcion--;
            else
                opcion = 9; // Ahora hay 8 opciones (0-7)
        } else if (tecla == 80) { // Flecha abajo
            if (opcion < 9)
                opcion++;
            else
                opcion = 0;
        }
        } else if (tecla == 13) { // Enter
            switch (opcion) {
                case 0: { // Crear nueva cuenta
                    int tipo = submenuTipoCuenta();
                    if (tipo == 2) // Regresar
                        break;
                    system("cls");
                    
                    string nombre, apellido, cedula;

                    // Pedir cédula con validación (ya valida dentro del método)
                    cedula = Validar::pedirCedula();

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
                        contadorId = leerUltimoIdCuenta() + 1;
                        nombre = cuentaExistente->getNombre();
                        apellido = cuentaExistente->getApellido();
                        contrasena = cuentaExistente->getContrasena();
                        cout << "Usuario ya registrado. Se usaran los datos existentes." << endl;
                    } else {
                        contadorId = leerUltimoIdCuenta() + 1;
                        nombre = Validar::pedirNombre();
                        apellido = Validar::pedirApellido();
                        contrasena = ContrasenaUsuario::generarContrasenaBancaria();
                    }

                    Persona persona(cedula, nombre, apellido);
                    double saldoInicial = 0.0; // Saldo inicial en 0
                    Cuenta cuenta(persona, saldoInicial, tipoCuenta);
                    cuenta.setContrasena(contrasena);
                    listaCuentas.insertarCuenta(cuenta);
                    listaCuentas.guardarCuentasEnArchivo("cuentas.txt"); // Guardar solo después de insertar
                    guardarUltimoIdCuenta(contadorId - 1);

                    cout << "Cuenta creada exitosamente con ID: " << cuenta.getIdCuentaStr() << endl;
                    cout << "Su contrasena bancaria es: " << contrasena << endl;

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
                case 8: // Ayuda
                    // Llama directamente a la ventana de ayuda con subsecciones
                    VentanaAyuda::Crear(GetModuleHandle(NULL));
                    break;
                case 9: // Salir
                    salir = true;
                    break;
            }
        }
    }
    system("cls");
    cout << "Gracias por usar el Sistema Bancario." << endl;
    return 0;
}