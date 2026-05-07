// Archivo: Pila.h
#pragma once
#include "NodoS.h"
#include "iostream"
using namespace std;

template <typename T>
class Pila {
private:
    NodoS<T>* tope;
    int tamanio;

public:
    Pila() {
        tope = nullptr;
        tamanio = 0;
    }

    void push(T dato) {
        NodoS<T>* nuevo = new NodoS<T>(dato);
        nuevo->siguiente = tope;
        tope = nuevo;
        tamanio++;
    }

    void pop() {
        if (tope == nullptr) return;
        NodoS<T>* temp = tope;
        tope = tope->siguiente;
        delete temp;
        tamanio--;
    }

    T& peek() { return tope->dato; }
    bool estaVacia() { return tope == nullptr; }
    int getTamanio() { return tamanio; }

    void mostrar() {
        NodoS<T>* actual = tope;
        while (actual != nullptr) {
            actual->dato.mostrar();
            actual = actual->siguiente;
        }
    }
};