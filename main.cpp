/***********************************************************************
 * Module:  main.cpp
 * Author:  Marjorie Cedeño,Victoria Diaz, Domenika Naranjo
 * Modified: sabado, 17 de mayo de 2025 21:08:05
 * Purpose: Cuenta Bancaria
 ***********************************************************************/
#include <iostream>
#include <conio.h> // Para _getch()
#include <windows.h> // Para SetConsoleCursorPosition
#include <string>
#include "Validar.cpp"
#include "VentanaAyuda.cpp"
#include "Cuenta.cpp"
#include "Persona.cpp"
#include "TipoCuenta.cpp"
#include "ListaCuenta.h"
#include "ContrasenaUsuario.cpp"
#include "Fecha.cpp"
#include "OperacionCuenta.cpp"
using namespace std;

ListaCuenta<Cuenta> listaCuentas;

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
    bool esCorriente = cuenta->getTipo().esCorriente();
    // Añade una opción más para eliminar cuenta
    int numOpciones = esCorriente ? 9 : 6;
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
                    case 0:
                        system("cls");
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        system("pause");
                        break;
                    case 1: {
                        system("cls");
                        double monto = pedirMontoSeguro("Ingrese monto a depositar: $");
                        operacion += monto;
                        system("pause");
                        break;
                    }
                    case 2: {
                        system("cls");
                        double monto = pedirMontoSeguro("Ingrese monto a retirar: $");
                        // Llama a la nueva función para retiro en cuenta de ahorro
                        operacion.retirarAhorroSimple(monto);
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        system("pause");
                        break;
                    }
                    case 3:
                        system("cls");
                        cout << "Historial de transacciones (simulado)" << endl;
                        system("pause");
                        break;
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
                    case 0:
                        system("cls");
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        system("pause");
                        break;
                    case 1: {
                        system("cls");
                        double monto = pedirMontoSeguro("Ingrese monto a depositar: $");
                        operacion += monto;
                        system("pause");
                        break;
                    }
                    case 2: {
                        system("cls");
                        double monto = pedirMontoSeguro("Ingrese monto a retirar: $");
                        operacion -= monto;
                        cout << "Saldo actual: $" << cuenta->getSaldo() << endl;
                        system("pause");
                        break;
                    }
                    case 3:
                        system("cls");
                        cout << "Historial de transacciones (simulado)" << endl;
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        operacion.mostrarEstadoSobregiro();
                        system("pause");
                        break;
                    case 5:
                        system("cls");
                        operacion.calcularInteresSobregiro();
                        system("pause");
                        break;
                    case 6: {
                        system("cls");
                        // Solo permite pagar hasta el monto pendiente de sobregiro
                        double montoMax = operacion.operator-(0); // saldo - 0 = saldo actual
                        double montoPagar;
                        cout << "Ingrese monto a pagar de sobregiro: $";
                        while (true) {
                            montoPagar = pedirMontoSeguro("");
                            // Para obtener el monto pendiente de sobregiro:
                            // Usamos un cast a double para acceder al atributo privado (no hay getter, así que mejor pedirlo al usuario y validar en pagarSobregiro)
                            if (montoPagar > 0 && montoPagar <= 5000) { // 5000 es arbitrario, el método ya valida el monto real
                                operacion.pagarSobregiro(montoPagar);
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
