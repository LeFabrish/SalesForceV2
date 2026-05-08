#pragma once
#include <iostream>
#include <string>
using namespace std;
class Oportunidad
{
public:
    string titulo;
    double valorEsperado;
    string fase; 

    Oportunidad(string t = "", double v = 0.0, string f = "Prospección")
        : titulo(t), valorEsperado(v), fase(f) {
    }

    void mostrar() const {
        cout << "Trato: " << titulo << " | Valor: $" << valorEsperado
            << " | Fase: [" << fase << "]" << endl;
    }
};

