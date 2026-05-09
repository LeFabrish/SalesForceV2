// Archivo: Cola.h
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

    // Como las listas enlazadas simples no tienen acceso aleatorio eficiente, volcamos temporalmente los datos a un arreglo, los ordenamos y reconstruimos la cola.
    template <typename Comparador>
    void ordenarShell(Comparador comp) {
        if (frente == nullptr || frente->siguiente == nullptr) return;

        T* arr = new T[tamanio];
        NodoS<T>* actual = frente;
        for (int i = 0; i < tamanio; i++) {
            arr[i] = actual->dato;
            actual = actual->siguiente;
        }

        for (int gap = tamanio / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < tamanio; i++) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && comp(temp, arr[j - gap]); j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }

        actual = frente;
        for (int i = 0; i < tamanio; i++) {
            actual->dato = arr[i];
            actual = actual->siguiente;
        }
        delete[] arr;
    }
};