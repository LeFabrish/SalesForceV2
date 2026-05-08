// Archivo: Pila.h
#pragma once
#include "NodoS.h"
#include <iostream>
#include <functional> // Para pasar como parametro la función lambda.

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

    ~Pila() {
        while (!estaVacia()) {
            pop();
        }
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
    bool estaVacia() const { return tope == nullptr; }
    int getTamanio() const { return tamanio; }

    void mostrar() const {
        NodoS<T>* actual = tope;
        while (actual != nullptr) {
            actual->dato.mostrar();
            actual = actual->siguiente;
        }
    }

    // Comparador para delegar la responsabilidad de evaluar qué objeto es mayor.
    void ordenarBurbujaOptimizada(std::function<bool(const T&, const T&)> comparadorMayor) {
        if (tamanio <= 1) return;
        bool intercambiado;
        NodoS<T>* actual;
        NodoS<T>* ultimo = nullptr;

        do {
            intercambiado = false;
            actual = tope;

            while (actual->siguiente != ultimo) {
                if (comparadorMayor(actual->dato, actual->siguiente->dato)) {
                    T temp = actual->dato;
                    actual->dato = actual->siguiente->dato;
                    actual->siguiente->dato = temp;
                    intercambiado = true;
                }
                actual = actual->siguiente;
            }
            ultimo = actual;
        } while (intercambiado);
    }

    // Necesitamos inyectar funciones para evaluar la igualdad y el orden
    int busquedaBinaria(const T& valorABuscar,
        std::function<bool(const T&, const T&)> esIgual,
        std::function<bool(const T&, const T&)> esMenor) const {
        if (estaVacia()) return -1;

        T* arr = new T[tamanio];
        NodoS<T>* actual = tope;
        for (int i = 0; i < tamanio; ++i) {
            arr[i] = actual->dato;
            actual = actual->siguiente;
        }

        int izquierda = 0;
        int derecha = tamanio - 1;
        int resultado = -1;

        while (izquierda <= derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;

            if (esIgual(arr[medio], valorABuscar)) {
                resultado = medio;
                break;
            }
            if (esMenor(arr[medio], valorABuscar)) {
                izquierda = medio + 1;
            }
            else {
                derecha = medio - 1;
            }
        }

        delete[] arr;
        return resultado;
    }
};