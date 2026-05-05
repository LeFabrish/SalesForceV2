#pragma once
#include "iostream"
using namespace std;

template <typename T>
class NodoD {
public:
    T dato;
    NodoD<T>* siguiente;
    NodoD<T>* anterior;

    NodoD(T dato) {
        this->dato = dato;
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }
};