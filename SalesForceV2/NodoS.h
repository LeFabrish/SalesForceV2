#pragma once
#include "iostream"
using namespace std;

template <typename T>
class NodoS {
public:
    T dato;
    NodoS<T>* siguiente;

    NodoS(T dato) {
        this->dato = dato;
        this->siguiente = nullptr;
    }
};