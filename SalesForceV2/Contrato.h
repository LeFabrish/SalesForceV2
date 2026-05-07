#pragma once
#include <iostream>
#include <string>
using namespace std;

class Contrato {
public:
    int idContrato;
    string fechaFirma;
    string terminos;

    Contrato(int id = 0, string fecha = "", string t = "Estándar")
        : idContrato(id), fechaFirma(fecha), terminos(t) {
    }

    void mostrar() const {
        cout << "Contrato ID: " << idContrato << " | Firmado: " << fechaFirma
            << " | Términos: " << terminos << endl;
    }
};