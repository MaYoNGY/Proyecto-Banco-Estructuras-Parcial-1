#ifndef VENTANAAYUDA_H
#define VENTANAAYUDA_H

#include <windows.h>

class VentanaAyuda {
public:
    static void Crear(HINSTANCE hInstance);
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif // VENTANAAYUDA_H
