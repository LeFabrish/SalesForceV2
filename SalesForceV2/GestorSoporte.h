#pragma once
#include "Pila.h"
#include "Caso.h"
#include "Solucion.h"
#include <iostream>
#include <string>
#include <functional>

using namespace std;

class GestorSoporte {
private:
    Pila<Caso> pilaCasos;
    Pila<Solucion> pilaSoluciones;

public:
    GestorSoporte() {}
    ~GestorSoporte() {}

    void registrarCaso(const Caso& nuevoCaso) {
        pilaCasos.push(nuevoCaso);
    }

    void resolverCaso(const Solucion& nuevaSolucion) {
        pilaSoluciones.push(nuevaSolucion);
    }

    void ordenarSoporte() {
        pilaCasos.ordenarBurbujaOptimizada([](const Caso& a, const Caso& b) {
            return a.getId() > b.getId();
            });

        pilaSoluciones.ordenarBurbujaOptimizada([](const Solucion& a, const Solucion& b) {
            return a.getId() > b.getId();
            });
    }

    bool buscarCasoPorId(string id) {
        Caso casoAux(id);

        int pos = pilaCasos.busquedaBinaria(
            casoAux,
            [](const Caso& a, const Caso& b) { return a.getId() == b.getId(); },
            [](const Caso& a, const Caso& b) { return a.getId() < b.getId(); }
        );

        return pos != -1;
    }

    void mostrarPanelSoporte() {
        auto imprimirCabecera = [](const string& titulo) {
            cout << "\n============================================\n";
            cout << "       " << titulo << "\n";
            cout << "============================================\n";
            };

        imprimirCabecera("PANEL DE GESTION DE SOPORTE");

        cout << " -> Casos Activos: " << pilaCasos.getTamanio() << "\n";
        pilaCasos.mostrar();

        imprimirCabecera("HISTORIAL DE SOLUCIONES");
        cout << " -> Soluciones Emitidas: " << pilaSoluciones.getTamanio() << "\n";
        pilaSoluciones.mostrar();
        cout << "============================================\n";
    }
};