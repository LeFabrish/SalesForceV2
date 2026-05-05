#pragma once
#include "NodoS.h"
#include "iostream"
using namespace std;

template <typename T>
class Cola {
private:
    NodoS<T>* frente;
    NodoS<T>* final;
    int tamanio;

public:
    Cola() {
        frente = nullptr;
        final = nullptr;
        tamanio = 0;
    }

    void enqueue(T dato) {
        NodoS<T>* nuevo = new NodoS<T>(dato);
        if (final == nullptr) {
            frente = nuevo;
            final = nuevo;
        }
        else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        tamanio++;
    }

    void dequeue() {
        if (frente == nullptr) return;
        NodoS<T>* temp = frente;
        frente = frente->siguiente;
        if (frente == nullptr) final = nullptr;
        delete temp;
        tamanio--;
    }

    T& getFrente() { return frente->dato; }
    bool estaVacia() { return frente == nullptr; }
    int getTamanio() { return tamanio; }

    void mostrar() {
        NodoS<T>* actual = frente;
        while (actual != nullptr) {
            actual->dato.mostrar();
            actual = actual->siguiente;
        }
    }
};