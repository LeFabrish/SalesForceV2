#pragma once
#include "iostream"
#include "string"
using namespace std;

class Cliente_Potencial {
private:
    int id;
    string nombre;
    string correo;
    string interes;

public:
    Cliente_Potencial() {
        id = 0;
        nombre = "";
        correo = "";
        interes = "";
    }

    Cliente_Potencial(int id, string nombre, string correo, string interes) {
        this->id = id;
        this->nombre = nombre;
        this->correo = correo;
        this->interes = interes;
    }

    // Getters
    int getId()          { return id; }
    string getNombre()   { return nombre; }
    string getCorreo()   { return correo; }
    string getInteres()  { return interes; }

    // Setters
    void setId(int i)           { id = i; }
    void setNombre(string n)    { nombre = n; }
    void setCorreo(string c)    { correo = c; }
    void setInteres(string i)   { interes = i; }

    void mostrar() {
        cout << "  ID      : " << id      << endl;
        cout << "  Nombre  : " << nombre  << endl;
        cout << "  Correo  : " << correo  << endl;
        cout << "  Interes : " << interes << endl;
        cout << "  ----------------------------------------" << endl;
    }

    void ingresar(int nuevoId) {
        id = nuevoId;
        cout << "  Nombre  : "; cin >> nombre;
        cout << "  Correo  : "; cin >> correo;
        cout << "  Interes : "; cin >> interes;
    }
};