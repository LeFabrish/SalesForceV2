// Archivo: Cola.h
#pragma once
#include "Nodo.h"

template <typename T>
class Cola
{
private:
    Nodo<T>* frente;
    Nodo<T>* final;
    int tamanio;

public:
    Cola() {
        frente = nullptr;
        final = nullptr;
        tamanio = 0;
    }

    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    void encolar(T elemento) {
        Nodo<T>* nuevoNodo = new Nodo<T>(elemento);
        if (estaVacia()) {
            frente = nuevoNodo;
        }
        else {
            final->setSiguiente(nuevoNodo);
        }
        final = nuevoNodo;
        tamanio++;
    }

    T desencolar() {
        if (estaVacia()) throw "La cola esta vacia";
        Nodo<T>* temp = frente;
        T dato = temp->getDato();
        frente = frente->getSiguiente();
        if (frente == nullptr) {
            final = nullptr;
        }
        delete temp;
        tamanio--;
        return dato;
    }

    bool estaVacia() {
        return frente == nullptr;
    }

    int getTamanio() { return tamanio; }
};