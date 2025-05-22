#include "VentanaAyuda.h"
#include "VentanaPrincipal.h"
#include <windows.h>
#include <string>
#include <iostream>

// Variables globales para la ventana de ayuda
HWND hwndAyuda = NULL;
HWND hwndModuloBtns[9];
HWND hwndTextoAyuda = NULL;
const wchar_t* textosAyuda[] = {
L"Crear nueva cuenta:\nAquí puedes crear tu propia cuenta bancaria en el sistema. Puedes elegir entre una cuenta de ahorros o una cuenta corriente, cada una con sus propias reglas:\n- La cuenta de ahorros no permite sobregiros y tiene un límite de retiros mensuales.\n- La cuenta corriente sí permite sobregiros hasta cierto monto.\nAl crear tu cuenta, se te pedirá ingresar tus datos personales como nombres, apellidos, fecha de nacimiento, número de cédula (válida), y una clave segura para proteger tu acceso. Todos los datos se almacenan de forma segura y se guardan automáticamente.",
L"Iniciar sesión para trámites:\nAntes de hacer cualquier operación en el sistema, como ver tu saldo o retirar dinero, necesitas iniciar sesión. Solo debes ingresar tu número de cuenta o tu cédula, junto con la clave que creaste al registrarte. Esto garantiza que solo tú puedas acceder a tus datos y realizar movimientos en tu cuenta.",
L"Consultas avanzadas:\n¿Quieres ver tus movimientos bancarios con más detalle? Con esta opción puedes buscar y filtrar tus transacciones por nombre, apellido, fecha, tipo de cuenta, y más. Es ideal si necesitas revisar tus depósitos, retiros o simplemente tener control total de tus operaciones. Puedes combinar varios filtros a la vez para encontrar exactamente lo que buscas.",
L"Generar Backup:\nCon esta función puedes crear una copia de seguridad de todos tus datos bancarios. El sistema guarda automáticamente una copia del archivo con la fecha y hora exacta, así nunca se pierde información importante. Puedes usar esta opción cada vez que lo necesites, sin preocuparte por sobrescribir las versiones anteriores.",
L"Restaurar Backup:\nSi en algún momento ocurre un error o necesitas volver a un estado anterior de tus datos, esta opción te permite restaurar una copia de seguridad previamente guardada. Todo quedará tal y como estaba en el momento del respaldo: cuentas, saldos, movimientos y configuración.",
L"Cifrado de datos:\nPara tu seguridad, puedes cifrar toda la información del sistema (como cuentas y transacciones), lo que la hace ilegible para cualquier persona no autorizada. Esta protección es útil si compartes tu computadora o quieres mantener tu información segura fuera del sistema.",
L"Descifrado de datos:\nSi has cifrado tu información y necesitas volver a usarla, esta opción te permitirá descifrar los datos y recuperar el acceso a tus cuentas y movimientos. Es un proceso seguro que garantiza que solo tú puedas acceder a lo que está protegido.",
L"Ayuda:\n¿Primera vez usando el sistema? No te preocupes. Aquí encontrarás una guía paso a paso que te explica cómo usar cada parte del programa: desde crear tu cuenta, iniciar sesión, hacer depósitos y retiros, hasta proteger tus datos y hacer respaldos. Todo explicado de forma sencilla para que no te pierdas.",
L"Salir:\nCuando termines de usar el sistema, utiliza esta opción para salir de manera segura. Así te aseguras de que todos tus datos queden bien guardados y no se pierda nada. El sistema se cierra correctamente y libera toda la información de forma ordenada."

};

void VentanaAyuda::Crear(HINSTANCE hInstance) {
    const wchar_t* CLASS_NAME = L"VentanaAyuda";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = VentanaAyuda::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    // Ventana más grande
    hwndAyuda = CreateWindowExW(
        0, CLASS_NAME, L"Ayuda del Sistema Bancario",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 700, 400,
        NULL, NULL, hInstance, NULL
    );

    // Barra de módulos/secciones a la izquierda
    int btnHeight = 35;
    int btnWidth = 180;
    const wchar_t* modulos[] = {
        L"Crear nueva cuenta",
        L"Iniciar sesion para tramites",
        L"Consultas avanzadas",
        L"Generar Backup",
        L"Restaurar Backup",
        L"Cifrado de datos",
        L"Descifrado de datos",
        L"Ayuda",
        L"Salir"
    };
    for (int i = 0; i < 9; i++) {
        hwndModuloBtns[i] = CreateWindowW(
            L"BUTTON", modulos[i],
            WS_VISIBLE | WS_CHILD | BS_LEFT,
            10, 10 + i * (btnHeight + 5), btnWidth, btnHeight,
            hwndAyuda, (HMENU)(100 + i), hInstance, NULL
        );
    }

    // Área de texto de ayuda a la derecha
    hwndTextoAyuda = CreateWindowW(
        L"STATIC", textosAyuda[0],
        WS_VISIBLE | WS_CHILD | SS_LEFT | SS_NOPREFIX,
        btnWidth + 30, 20, 450, 320,
        hwndAyuda, NULL, hInstance, NULL
    );

    ShowWindow(hwndAyuda, SW_SHOW);
    UpdateWindow(hwndAyuda);
}

LRESULT CALLBACK VentanaAyuda::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (id >= 100 && id < 109) {
                // Cambia el texto de ayuda según el módulo seleccionado
                SetWindowTextW(hwndTextoAyuda, textosAyuda[id - 100]);
            }
            break;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            hwndAyuda = NULL;
            break;
        case WM_DESTROY:
            hwndAyuda = NULL;
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
