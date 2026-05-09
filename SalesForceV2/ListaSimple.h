#pragma once
#include "NodoS.h"
#include "iostream"
using namespace std;

template <typename T>
class ListaSimple {
private:
    NodoS<T>* cabeza;
    int tamanio;

public:
    ListaSimple() {
        cabeza = nullptr;
        tamanio = 0;
    }

    void insertar(T dato) {
        NodoS<T>* nuevo = new NodoS<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        }
        else {
            NodoS<T>* actual = cabeza;
            while (actual->siguiente != nullptr)
                actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
        tamanio++;
    }

    void eliminar(int pos) {
        if (cabeza == nullptr) return;
        if (pos == 0) {
            NodoS<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            tamanio--;
            return;
        }
        NodoS<T>* actual = cabeza;
        for (int i = 0; i < pos - 1 && actual->siguiente != nullptr; i++)
            actual = actual->siguiente;
        if (actual->siguiente == nullptr) return;
        NodoS<T>* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        tamanio--;
    }

    void mostrar() {
        NodoS<T>* actual = cabeza;
        int i = 0;
        while (actual != nullptr) {
            cout << "[" << i++ << "] ";
            actual->dato.mostrar();
            actual = actual->siguiente;
        }
    }

    template <typename Criterio>
    NodoS<T>* buscar(Criterio criterio) {
        NodoS<T>* actual = cabeza;
        while (actual != nullptr) {
            if (criterio(actual->dato)) return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    template <typename Comparador>
    void ordenar(Comparador comp) {
        if (cabeza == nullptr) return;
        bool cambio = true;
        while (cambio) {
            cambio = false;
            NodoS<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                if (comp(actual->dato, actual->siguiente->dato)) {
                    swap(actual->dato, actual->siguiente->dato);
                    cambio = true;
                }
                actual = actual->siguiente;
            }
        }
    }

    // Burbuja optimizada con template
    template <typename Comparador>
    void ordenarBurbujaOptimizada(Comparador comp) {
        if (cabeza == nullptr) return;
        bool ordenado;
        do {
            ordenado = true;
            NodoS<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                if (comp(actual->dato, actual->siguiente->dato)) {
                    swap(actual->dato, actual->siguiente->dato);
                    ordenado = false;
                }
                actual = actual->siguiente;
            }
        } while (!ordenado);
    }

    bool estaVacia() { return cabeza == nullptr; }
    int getTamanio() { return tamanio; }
    NodoS<T>* getCabeza() { return cabeza; }
};