// Archivo: Direccion.h
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Direccion
{
private:
    string distrito;
    string calle;
    string referencia;

public:
    Direccion() {
        this->distrito = "";
        this->calle = "";
        this->referencia = "";
    }

    Direccion(string distrito, string calle, string referencia) {
        this->distrito = distrito;
        this->calle = calle;
        this->referencia = referencia;
    }

    string getDistrito() { return this->distrito; }
    string getCalle() { return this->calle; }
    string getReferencia() { return this->referencia; }

    void setDistrito(string distrito) { this->distrito = distrito; }
    void setCalle(string calle) { this->calle = calle; }
    void setReferencia(string referencia) { this->referencia = referencia; }
};