// Archivo: Pila.h
#pragma once
#include "Nodo.h"

template <typename T>
class Pila
{
private:
    Nodo<T>* cima;
    int tamanio;

public:
    Pila() {
        cima = nullptr;
        tamanio = 0;
    }

    ~Pila() {
        while (!estaVacia()) {
            desapilar();
        }
    }

    void apilar(T elemento) {
        Nodo<T>* nuevoNodo = new Nodo<T>(elemento);
        nuevoNodo->setSiguiente(cima);
        cima = nuevoNodo;
        tamanio++;
    }

    T desapilar() {
        if (estaVacia()) return "La pila esta vacia";
        Nodo<T>* temp = cima;
        T dato = temp->getDato();
        cima = cima->getSiguiente();
        delete temp;
        tamanio--;
        return dato;
    }

    bool estaVacia() {
        return cima == nullptr;
    }

    int getTamanio() { return tamanio; }
};