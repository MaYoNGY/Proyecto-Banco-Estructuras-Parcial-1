#ifndef __NODOTRANSACCION_H
#define __NODOTRANSACCION_H

template<typename T>
class NodoTransaccion
{
private:
   T dato;
   NodoTransaccion<T>* siguiente;
   NodoTransaccion<T>* anterior;
public:
   NodoTransaccion(const T& dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}
   T& getDato() { return dato; }
   NodoTransaccion<T>* getSiguiente() const { return siguiente; }
   NodoTransaccion<T>* getAnterior() const { return anterior; }
   void setSiguiente(NodoTransaccion<T>* sig) { siguiente = sig; }
   void setAnterior(NodoTransaccion<T>* ant) { anterior = ant; }
};

#endif