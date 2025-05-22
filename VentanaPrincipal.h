#ifndef VENTANA_AYUDA_H
#define VENTANA_AYUDA_H

#include <windows.h>

class VentanaAyuda {
public:
    static void Crear(HINSTANCE hInstance);
private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif
