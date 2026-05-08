#pragma once
#include <iostream>
#include <string>
using namespace std;

class Cotizacion {
public:
    int numeroCotizacion;
    double total;
    string fechaVencimiento;

    Cotizacion(int n = 0, double t = 0.0, string f = "")
        : numeroCotizacion(n), total(t), fechaVencimiento(f) {
    }

    void mostrar() const {
        cout << "Cotización #" << numeroCotizacion << " | Total: $" << total
            << " | Vence: " << fechaVencimiento << endl;
    }

};