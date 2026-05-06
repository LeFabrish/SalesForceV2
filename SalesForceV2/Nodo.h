// Archivo: Nodo.h
#pragma once

// Se usa template para que el Nodo pueda almacenar cualquier tipo de objeto (Cuenta, Contacto, etc.)
// Esto sirve como generalizacion y aplica la programación generica
template <typename T>
class Nodo
{
private:
    T dato;
    Nodo<T>* siguiente;

public:
    Nodo(T dato) {
        this->dato = dato;
        this->siguiente = nullptr;
    }

    T getDato() { return dato; }
    void setDato(T dato) { this->dato = dato; }

    Nodo<T>* getSiguiente() { return siguiente; }
    void setSiguiente(Nodo<T>* siguiente) { this->siguiente = siguiente; }
};