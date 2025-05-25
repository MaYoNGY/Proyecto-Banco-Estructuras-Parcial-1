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
            if (tecla == 72 && opcion > 0) // Flecha arriba
                opcion--;
            else if (tecla == 80 && opcion < 2) // Flecha abajo
                opcion++;
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
        for (int i = 0; i < 5; i++) {
            if (i == opcion)
                cout << ">> " << opciones[i] << endl;
            else
                cout << "   " << opciones[i] << endl;
        }
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72 && opcion > 0)
                opcion--;
            else if (tecla == 80 && opcion < 4)
                opcion++;
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
                cout << ">> " << tipo << " | ID: " << id << endl;
            else
                cout << "   " << tipo << " | ID: " << id << endl;
        }
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72 && opcion > 0) // Flecha arriba
                opcion--;
            else if (tecla == 80 && opcion < cuentaCount - 1) // Flecha abajo
                opcion++;
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
            if (tecla == 72 && opcion > 0) // Flecha arriba
                opcion--;
            else if (tecla == 80 && opcion < 8) // Flecha abajo
                opcion++;
        } else if (tecla == 13) { // Enter
            switch (opcion) {
                case 0: { // Crear nueva cuenta
                    int tipo = submenuTipoCuenta();
                    if (tipo == 2) // Regresar
                        break;
                    system("cls");
                    string nombre, cedula, direccion;
                
                    // Pedir cédula con validación
                    while (true) {
                        cout << "Ingrese su cedula: ";
                        cedula = "";
                        char c;
                        while (true) {
                            c = _getch();
                            if (c == 13) { // Enter
                                cout << endl;
                                break;
                            }
                            if (c == 8) { // Backspace
                                if (!cedula.empty()) {
                                    cedula.pop_back();
                                    cout << "\b \b";
                                }
                            } else if (c >= '0' && c <= '9' && cedula.length() < 10) {
                                cedula += c;
                                cout << c;
                            }
                        }
                        if (cedula.length() == 10) {
                            if (validarCedulaEcuatoriana(cedula)) {
                                break;
                            } else {
                                cout << "Cedula invalida. Intente de nuevo." << endl;
                            }
                        } else {
                            cout << "Cedula invalida. Intente de nuevo." << endl;
                        }
                    }
                
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
                        contrasena = cuentaExistente->getContrasena();
                        cout << "Usuario ya registrado. Se usaran los datos existentes." << endl;
                    } else {
                        // Si no existe, pide nombre y dirección y genera contraseña
                        cout << "Ingrese su nombre: ";
                        nombre = "";
                        char c;
                        while (true) {
                            c = _getch();
                            if (c == 13) { // Enter
                                cout << endl;
                                if (!nombre.empty()) break;
                            }
                            else if (c == 8) { // Backspace
                                if (!nombre.empty()) {
                                    nombre.pop_back();
                                    cout << "\b \b";
                                }
                            }
                            else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
                                nombre += c;
                                cout << c;
                            }
                        }
                        contrasena = ContrasenaUsuario::generarContrasenaBancaria();
                    }
                
                    Persona persona(cedula, nombre);
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
                    // Pedir cédula
                    while (true) {
                        cout << "Ingrese su cedula: ";
                        cedula = "";
                        char c;
                        while (true) {
                            c = _getch();
                            if (c == 13) { cout << endl; break; }
                            if (c == 8) {
                                if (!cedula.empty()) { cedula.pop_back(); cout << "\b \b"; }
                            } else if (c >= '0' && c <= '9' && cedula.length() < 10) {
                                cedula += c; cout << c;
                            }
                        }
                        break;
                    }
                    // Pedir contraseña
                    cout << "Ingrese su contrasena: ";
                    char ch;
                    contrasena = "";
                    while ((ch = _getch()) != 13) {
                        if (ch == 8 && !contrasena.empty()) {
                            contrasena.pop_back(); cout << "\b \b";
                        } else if (ch != 8) {
                            contrasena += ch; cout << '*';
                        }
                    }
                    cout << endl;
                
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
