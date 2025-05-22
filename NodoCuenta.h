
#ifndef __NODOCUENTA_H
#define __NODOCUENTA_H

template <typename T>
class NodoCuenta
{
private:
    T dato;
    NodoCuenta<T>* siguiente;
    NodoCuenta<T>* anterior;
public:
    NodoCuenta(const T& dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}
    T& getDato() { return dato; }
    NodoCuenta<T>* getSiguiente() const { return siguiente; }
    NodoCuenta<T>* getAnterior() const { return anterior; }
    void setSiguiente(NodoCuenta<T>* sig) { siguiente = sig; }
    void setAnterior(NodoCuenta<T>* ant) { anterior = ant; }
};

#endif