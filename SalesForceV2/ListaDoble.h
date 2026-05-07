#pragma once
#include "NodoD.h"
#include "iostream"
using namespace std;

template <typename T>
class ListaDoble {
private:
    NodoD<T>* cabeza;
    NodoD<T>* cola;
    int tamanio;

public:
    ListaDoble() {
        cabeza = nullptr;
        cola = nullptr;
        tamanio = 0;
    }

    // Insertar al final
    void insertar(T dato) {
        NodoD<T>* nuevo = new NodoD<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tamanio++;
    }

    // Eliminar por posición
    void eliminar(int pos) {
        if (cabeza == nullptr) return;
        NodoD<T>* actual = cabeza;
        for (int i = 0; i < pos && actual != nullptr; i++)
            actual = actual->siguiente;
        if (actual == nullptr) return;
        if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
        else cabeza = actual->siguiente;
        if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
        else cola = actual->anterior;
        delete actual;
        tamanio--;
    }

    // Mostrar hacia adelante
    void mostrar() {
        NodoD<T>* actual = cabeza;
        int i = 0;
        while (actual != nullptr) {
            cout << "[" << i++ << "] ";
            actual->dato.mostrar();
            actual = actual->siguiente;
        }
    }

    // Mostrar hacia atrás
    void mostrarInverso() {
        NodoD<T>* actual = cola;
        while (actual != nullptr) {
            actual->dato.mostrar();
            actual = actual->anterior;
        }
    }

    // Buscar con lambda
    template <typename Criterio>
    NodoD<T>* buscar(Criterio criterio) {
        NodoD<T>* actual = cabeza;
        while (actual != nullptr) {
            if (criterio(actual->dato)) return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // Ordenar con lambda (burbuja)
    template <typename Comparador>
    void ordenar(Comparador comp) {
        if (cabeza == nullptr) return;
        bool cambio = true;
        while (cambio) {
            cambio = false;
            NodoD<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                if (comp(actual->dato, actual->siguiente->dato)) {
                    swap(actual->dato, actual->siguiente->dato);
                    cambio = true;
                }
                actual = actual->siguiente;
            }
        }
    }

    bool estaVacia() { return cabeza == nullptr; }
    int getTamanio() { return tamanio; }
    NodoD<T>* getCabeza() { return cabeza; }
};