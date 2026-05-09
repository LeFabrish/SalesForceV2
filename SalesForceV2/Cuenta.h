#pragma once
#include "iostream"
#include "string"
#include "Direccion.h"
using namespace std;

class Cuenta {
private:
    int id;
    string nombre;
    string industria;
    string telefono;
    string email;
    Direccion direccion;

public:
    Cuenta() {
        id = 0;
        nombre = "";
        industria = "";
        telefono = "";
        email = "";
    }

    Cuenta(int id, string nombre, string industria, string telefono, string email, Direccion direccion) {
        this->id = id;
        this->nombre = nombre;
        this->industria = industria;
        this->telefono = telefono;
        this->email = email;
        this->direccion = direccion;
    }

    // Getters
    int getId() { return id; }
    string getNombre() { return nombre; }
    string getIndustria() { return industria; }
    string getTelefono() { return telefono; }
    string getEmail() { return email; }
    Direccion getDireccion() { return direccion; }

    // Setters
    void setId(int i) { id = i; }
    void setNombre(string n) { nombre = n; }
    void setIndustria(string i) { industria = i; }
    void setTelefono(string t) { telefono = t; }
    void setEmail(string e) { email = e; }
    void setDireccion(Direccion d) { direccion = d; }

    void mostrar() {
        cout << "  ID        : " << id << endl;
        cout << "  Nombre    : " << nombre << endl;
        cout << "  Industria : " << industria << endl;
        cout << "  Telefono  : " << telefono << endl;
        cout << "  Email     : " << email << endl;
        cout << "  Direccion :" << endl;
        direccion.mostrar();
        cout << "  ----------------------------------------" << endl;
    }

    void ingresar(int nuevoId) {
        id = nuevoId;
        cout << "  Nombre    : "; cin >> nombre;
        cout << "  Industria : "; cin >> industria;
        cout << "  Telefono  : "; cin >> telefono;
        cout << "  Email     : "; cin >> email;
        cout << "  -Direccion" << endl;
        direccion.ingresar();
    }
};