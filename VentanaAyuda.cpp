#include "VentanaAyuda.h"
#include <windows.h>
#include <string>

// Variables globales para la ventana de ayuda
static HWND hwndAyuda = NULL;
static HWND hwndModuloBtns[7];
static HWND hwndTextoAyuda = NULL;
static const wchar_t* textosAyuda[] = {
L"Crear nueva cuenta:\n\nAquí puedes crear tu propia cuenta bancaria en el sistema.\nPuedes elegir entre una cuenta de ahorros o una cuenta corriente, cada una con sus propias reglas:\n- La cuenta de ahorros no permite sobregiros y tiene un límite de retiros mensuales.\n- La cuenta corriente sí permite sobregiros hasta cierto monto.\nAl crear tu cuenta, se te pedirá ingresar tus datos personales como nombres, apellidos, fecha de nacimiento, número de cédula (válida), y una clave segura para proteger tu acceso. Todos los datos se almacenan de forma segura y se guardan automáticamente.",
L"Iniciar sesión para trámites:\n\nAntes de hacer cualquier operación en el sistema, como ver tu saldo o retirar dinero,\nnecesitas iniciar sesión. Solo debes ingresar tu número de cuenta o tu cédula, junto con la clave que creaste al registrarte. Esto garantiza que solo tú puedas acceder a tus datos y realizar movimientos en tu cuenta.",
L"Consultas avanzadas:\n\n¿Quieres ver tus movimientos bancarios con más detalle? \nCon esta opción puedes buscar y filtrar tus transacciones por nombre, apellido, fecha, tipo de cuenta, y más. \nEs ideal si necesitas revisar tus depósitos, retiros o simplemente tener control total de tus operaciones. Puedes combinar varios filtros a la vez para encontrar exactamente lo que buscas.",
L"Generar Backup:\n\nCon esta función puedes crear una copia de seguridad de todos tus datos bancarios. \nEl sistema guarda automáticamente una copia del archivo con la fecha y hora exacta, así nunca se pierde información importante. \nPuedes usar esta opción cada vez que lo necesites, sin preocuparte por sobrescribir las versiones anteriores.",
L"Restaurar Backup:\n\nSi en algún momento ocurre un error o necesitas volver a un estado anterior de tus datos,\n esta opción te permite restaurar una copia de seguridad previamente guardada. Todo quedará tal y como estaba en el momento del respaldo: cuentas, saldos, movimientos y configuración.",
L"Ayuda:\n\n¿Primera vez usando el sistema? No te preocupes. Aquí encontrarás una guía paso a paso que te explica cómo usar cada parte del programa: \ndesde crear tu cuenta, iniciar sesión, hacer depósitos y retiros, hasta proteger tus datos y hacer respaldos. \nTodo explicado de forma sencilla para que no te pierdas.",
L"Salir:\n\nCuando termines de usar el sistema,\n utiliza esta opción para salir de manera segura. Así te aseguras de que todos tus datos queden bien guardados y no se pierda nada.\n El sistema se cierra correctamente y libera toda la información de forma ordenada."


};

void VentanaAyuda::Crear(HINSTANCE hInstance) {
    const wchar_t* CLASS_NAME = L"VentanaAyuda";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = VentanaAyuda::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    hwndAyuda = CreateWindowExW(
        0, CLASS_NAME, L"Ayuda del Sistema Bancario",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 500,
        NULL, NULL, hInstance, NULL
    );

    int btnHeight = 35;
    int btnWidth = 190;
    const wchar_t* modulos[] = {
        L"Crear nueva cuenta",
        L"Iniciar sesion para tramites",
        L"Consultas avanzadas",
        L"Generar Backup",
        L"Restaurar Backup",
        L"Ayuda",
        L"Salir"
    };
    for (int i = 0; i < 7; i++) {
        hwndModuloBtns[i] = CreateWindowW(
            L"BUTTON", modulos[i],
            WS_VISIBLE | WS_CHILD | BS_LEFT,
            10, 10 + i * (btnHeight + 5), btnWidth, btnHeight,
            hwndAyuda, (HMENU)(UINT_PTR)(100 + i), hInstance, NULL
        );
    }

    hwndTextoAyuda = CreateWindowW(
        L"STATIC", textosAyuda[0],
        WS_VISIBLE | WS_CHILD | SS_LEFT | SS_NOPREFIX,
        btnWidth + 30, 20, 450, 320,
        hwndAyuda, NULL, hInstance, NULL
    );

    ShowWindow(hwndAyuda, SW_SHOW);
    UpdateWindow(hwndAyuda);

    // Bucle de mensajes para la ventana de ayuda
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if (!IsDialogMessage(hwndAyuda, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (!IsWindow(hwndAyuda)) break;
    }
}

LRESULT CALLBACK VentanaAyuda::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (id >= 100 && id < 109) {
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
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

