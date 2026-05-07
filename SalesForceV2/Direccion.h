// Archivo: Direccion.h
#pragma once
#include "iostream"
#include "string"
using namespace std;

class Direccion {
private:
    string pais;
    string ciudad;
    string distrito;
    string calle;

public:
    // Constructor vacío
    Direccion() {
        pais = "";
        ciudad = "";
        distrito = "";
        calle = "";
    }

    // Constructor con parámetros
    Direccion(string pais, string ciudad, string distrito, string calle) {
        this->pais = pais;
        this->ciudad = ciudad;
        this->distrito = distrito;
        this->calle = calle;
    }

    // Getters
    string getPais() { return pais; }
    string getCiudad() { return ciudad; }
    string getDistrito() { return distrito; }
    string getCalle() { return calle; }

    // Setters
    void setPais(string p) { pais = p; }
    void setCiudad(string c) { ciudad = c; }
    void setDistrito(string d) { distrito = d; }
    void setCalle(string ca) { calle = ca; }

    // Mostrar
    void mostrar() {
        cout << "   Pais     : " << pais << endl;
        cout << "   Ciudad   : " << ciudad << endl;
        cout << "   Distrito : " << distrito << endl;
        cout << "   Calle    : " << calle << endl;
    }

    // Ingresar por consola
    void ingresar() {
        cout << "   Pais     : "; cin >> pais;
        cout << "   Ciudad   : "; cin >> ciudad;
        cout << "   Distrito : "; cin >> distrito;
        cout << "   Calle    : "; cin >> calle;
    }
};