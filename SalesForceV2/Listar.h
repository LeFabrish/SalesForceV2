// Archivo: Listar.h
#pragma once
#include "Nodo.h"
#include <iostream>

using namespace std;

template <typename T>
class Lista
{
private:
    Nodo<T>* inicio;
    int longitud;

public:
    Lista() {
        inicio = nullptr;
        longitud = 0;
    }

    ~Lista() {
        Nodo<T>* actual = inicio;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    void agregar(T elemento) {
        Nodo<T>* nuevoNodo = new Nodo<T>(elemento);
        if (inicio == nullptr) {
            inicio = nuevoNodo;
        }
        else {
            Nodo<T>* actual = inicio;
            while (actual->getSiguiente() != nullptr) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevoNodo);
        }
        longitud++;
    }

    T obtener(int indice) {
        // Retorna el elemento en la posicion indicada. Faltaria validacion de limites en un entorno de produccion.
        Nodo<T>* actual = inicio;
        for (int i = 0; i < indice; i++) {
            actual = actual->getSiguiente();
        }
        return actual->getDato();
    }

    int getLongitud() {
        return longitud;
    }
};