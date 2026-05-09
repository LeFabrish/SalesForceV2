// Archivo: Cola.h
#pragma once
#include "ListaSimple.h"
#include <iostream>
using namespace std;

template<typename T>
class Cola {
private:
    NodoS<T>* frente;
    NodoS<T>* fin;

public:
    Cola() : frente(nullptr), fin(nullptr) {}
    ~Cola() {
        while (!estaVacia()) dequeue();
    }

    bool estaVacia() {
        return frente == nullptr;
    }

    void enqueue(const T& dato) {
        NodoS<T>* nuevo = new NodoS<T>(dato);
        if (estaVacia()) {
            frente = fin = nuevo;
        }
        else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
    }

    void dequeue() {
        if (estaVacia()) return;
        NodoS<T>* temp = frente;
        frente = frente->siguiente;
        delete temp;
        if (frente == nullptr) fin = nullptr;
    }

    // Devuelve referencia al dato en el frente (existente en su código)
    T& getFrente() {
        return frente->dato;
    }

    // Nuevo método requerido por GestorSoporte: obtiene el nodo frontal
    NodoS<T>* getFrenteNodo() {
        return frente;
    }

    // Mostrar elementos (usa el método mostrar() del tipo T)
    void mostrar() {
        NodoS<T>* actual = frente;
        while (actual != nullptr) {
            actual->dato.mostrar();
            actual = actual->siguiente;
        }
    }
};