/***********************************************************************
 * Module:  main.cpp
 * Author:  Marjorie Cedeño,Victoria Diaz, Domenika Naranjo
 * Modified: sabado, 17 de mayo de 2025 21:08:05
 * Purpose: Cuenta Bancaria
 ***********************************************************************/
#include <iostream>
#include <conio.h> // Para _getch()
#include <windows.h> // Para SetConsoleCursorPosition
#include "Validar.cpp"
#include "VentanaAyuda.cpp"
#include "Cuenta.cpp"
#include "Persona.cpp"
#include "TipoCuenta.cpp"
#include "ListaCuenta.h"
#include "ContrasenaUsuario.cpp"
#include "Fecha.cpp"
using namespace std;

ListaCuenta<Cuenta> listaCuentas;

// Función para mover el cursor a una posición específica
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
        "6. Cifrado de datos",
        "7. Descifrado de datos",
        "8. Ayuda",
        "9. Salir"
    };
    for (int i = 0; i < 9; i++) {
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
    string opciones[] = {
        "1. Consultar saldo",
        "2. Depositar dinero",
        "3. Retirar dinero",
        "4. Mostrar historial",
        "5. Salir"
    };
    bool salir = false;
    while (!salir) {
        system("cls");
        cout << "===== Menu de Transacciones =====" << endl;
        cout << "Cuenta: " << cuenta->getTipo().getTipo() << " | ID: " << cuenta->getIdCuentaStr() << endl;
        Fecha fechaCreacion = cuenta->getFechaCreacion();
        cout << "Fecha de creacion: " << fechaCreacion.getDia() << "/" << fechaCreacion.getMes() << "/" << fechaCreacion.getAnio() << endl;
        for (int i = 0; i <
             5; i++) {
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
            opcion = 4; // Si está en la primera opción, va a la última
        } else if (tecla == 80) { // Flecha abajo
            if (opcion < 4)
            opcion++;
            else
            opcion = 0; // Si está en la última opción, va a la primera
        }
        } else if (tecla == 13) {
            switch (opcion) {
                case 0:
                    system("cls");
                    cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                    system("pause");
                    break;
                case 1: {
                    system("cls");
                    double monto;
                    cout << "Ingrese monto a depositar: $";
                    cin >> monto;
                    if (monto > 0) {
                        cuenta->setSaldo(cuenta->getSaldo() + monto);
                        cout << "Deposito realizado. Nuevo saldo: $" << cuenta->getSaldo() << endl;
                    } else {
                        cout << "Monto invalido." << endl;
                    }
                    system("pause");
                    break;
                }
                case 2: {
                    system("cls");
                    double monto;
                    cout << "Ingrese monto a retirar: $";
                    cin >> monto;
                    if (monto > 0 && monto <= cuenta->getSaldo()) {
                        cuenta->setSaldo(cuenta->getSaldo() - monto);
                        cout << "Retiro realizado. Nuevo saldo: $" << cuenta->getSaldo() << endl;
                    } else {
                        cout << "Monto invalido o saldo insuficiente." << endl;
                    }
                    system("pause");
                    break;
                }
                case 3:
                    system("cls");
                    cout << "Historial de transacciones (simulado)" << endl;
                    system("pause");
                    break;
                case 4:
                    salir = true;
                    break;
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


int main() {
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
                opcion = 8; // Si está en la primera opción, va a la última
        } else if (tecla == 80) { // Flecha abajo
            if (opcion < 8)
                opcion++;
            else
                opcion = 0; // Si está en la última opción, va a la primera
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
                
                    // Verificar si ya existe una cuenta de ese tipo para esa cédula
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
                    double saldoInicial = 0.0;
                    Cuenta cuenta(persona, saldoInicial, tipoCuenta);
                    cuenta.setContrasena(contrasena);
                    listaCuentas.insertarCuenta(cuenta);
                
                    cout << "Cuenta creada exitosamente con ID: " << cuenta.getIdCuentaStr() << endl;
                    cout << "Su contrasena bancaria es: " << contrasena << endl;
                
                    system("pause");
                    break;
                }
                case 1: { // Iniciar sesion para tramites
                    system("cls");
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
                    cout << "Consultas avanzadas (no implementado)." << endl;
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    cout << "Generar Backup (no implementado)." << endl;
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    cout << "Restaurar Backup (no implementado)." << endl;
                    system("pause");
                    break;
                case 5:
                    system("cls");
                    cout << "Cifrado de datos (no implementado)." << endl;
                    system("pause");
                    break;
                case 6:
                    system("cls");
                    cout << "Descifrado de datos (no implementado)." << endl;
                    system("pause");
                    break;
                case 7:
                    // Llama directamente a la ventana de ayuda con subsecciones
                    VentanaAyuda::Crear(GetModuleHandle(NULL));
                    break;
                case 8:
                    salir = true;
                    break;
            }
        }
    }
    system("cls");
    cout << "Gracias por usar el Sistema Bancario." << endl;
    return 0;
}
