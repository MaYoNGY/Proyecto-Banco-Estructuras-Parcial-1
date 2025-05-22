/***********************************************************************
 * Module:  main.cpp
 * Author:  Marjorie Cedeño,Victoria Diaz, Domenika Naranjo
 * Modified: sabado, 17 de mayo de 2025 21:08:05
 * Purpose: Cuenta Bancaria
 ***********************************************************************/
#include <iostream>
#include <conio.h> // Para _getch()
#include <windows.h> // Para SetConsoleCursorPosition
#include "VentanaAyuda.cpp"
using namespace std;

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

// Simulación de validación de usuario (puedes reemplazar por tu lógica real)
bool validarUsuario(const std::string& cedula, const std::string& clave) {
    // Usuario y clave fijos para demo
    return (cedula == "12345678" && clave == "1234");
}

// Menú de transacciones tras login exitoso
void menuTransacciones() {
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
                    cout << "Saldo actual: $1000 (simulado)" << endl;
                    system("pause");
                    break;
                case 1:
                    system("cls");
                    cout << "Depositar dinero (simulado)" << endl;
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    cout << "Retirar dinero (simulado)" << endl;
                    system("pause");
                    break;
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
                    if (tipo == 0)
                        cout << "Seleccionaste cuenta de Ahorros." << endl;
                    else if (tipo == 1)
                        cout << "Seleccionaste cuenta Corriente." << endl;
                    system("pause");
                    break;
                }
                case 1: { // Iniciar sesion para tramites
                    system("cls");
                    string cedula, clave;
                    cout << "Ingrese su cedula: ";
                    cin >> cedula;
                    cout << "Ingrese su clave: ";
                    char ch;
                    clave = "";
                    while ((ch = _getch()) != 13) { // Enter
                        if (ch == 8 && !clave.empty()) { // Backspace
                            clave.pop_back();
                            cout << "\b \b";
                        } else if (ch != 8) {
                            clave += ch;
                            cout << '*';
                        }
                    }
                    cout << endl;
                    if (validarUsuario(cedula, clave)) {
                        menuTransacciones();
                    } else {
                        cout << "\nUsuario o clave incorrectos." << endl;
                        system("pause");
                    }
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
