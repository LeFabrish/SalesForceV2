// Archivo: ListaDoble.h
#pragma once
#include "Nodo.h"
#include <iostream>
#include <stdexcept> // Para manejo de excepciones basicas

using namespace std;

template <typename T>
class ListaDoble
{
private:
    Nodo<T>* inicio;
    Nodo<T>* fin;    // Vital en lista doble para insertar al final u optimizar busquedas inversas
    int longitud;

public:
    ListaDoble() {
        inicio = nullptr;
        fin = nullptr;
        longitud = 0;
    }

    ~ListaDoble() {
        Nodo<T>* actual = inicio;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    // Agrega un elemento siempre al final de la lista
    void agregar(T elemento) {
        Nodo<T>* nuevoNodo = new Nodo<T>(elemento);

        if (estaVacia()) {
            inicio = nuevoNodo;
            fin = nuevoNodo;
        }
        else {
            // Se enlaza el ultimo nodo actual con el nuevo
            fin->setSiguiente(nuevoNodo);
            // El nuevo nodo apunta hacia atras al antiguo fin
            nuevoNodo->setAnterior(fin);
            // Se actualiza el puntero fin
            fin = nuevoNodo;
        }
        longitud++;
    }

    // Obtener elemento por indice (Navegacion basica)
    T obtener(int indice) {
        if (indice < 0 || indice >= longitud) {
            throw out_of_range("Indice fuera de los limites de la lista");
        }

        Nodo<T>* actual = inicio;
        for (int i = 0; i < indice; i++) {
            actual = actual->getSiguiente();
        }
        return actual->getDato();
    }

    // Elimina un elemento por su posicion, reconectando los punteros anterior y siguiente
    void eliminar(int indice) {
        if (indice < 0 || indice >= longitud) return;

        Nodo<T>* aEliminar = inicio;
        for (int i = 0; i < indice; i++) {
            aEliminar = aEliminar->getSiguiente();
        }

        // Si hay un nodo antes, su 'siguiente' ahora debe saltarse el nodo a eliminar
        if (aEliminar->getAnterior() != nullptr) {
            aEliminar->getAnterior()->setSiguiente(aEliminar->getSiguiente());
        }
        else {
            // Si no hay nodo antes, estamos eliminando el inicio
            inicio = aEliminar->getSiguiente();
        }

        // Si hay un nodo despues, su 'anterior' ahora debe apuntar al nodo previo al eliminado
        if (aEliminar->getSiguiente() != nullptr) {
            aEliminar->getSiguiente()->setAnterior(aEliminar->getAnterior());
        }
        else {
            // Si no hay nodo despues, estamos eliminando el fin
            fin = aEliminar->getAnterior();
        }

        delete aEliminar;
        longitud--;
    }

    bool estaVacia() {
        return inicio == nullptr;
    }

    int getLongitud() {
        return longitud;
    }

    // Estos getters son clave para la navegacion manual bidireccional. 
    // Un gestor externo puede pedir el nodo inicio o fin y usar getSiguiente() o getAnterior() libremente.
    Nodo<T>* getInicio() {
        return inicio;
    }

    Nodo<T>* getFin() {
        return fin;
    }
};