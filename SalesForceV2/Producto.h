#pragma once
#include <iostream>
#include <string>
using namespace std;
class Producto
{
public:
    int id;
    string nombre;
    double precio;

    Producto(int _id = 0, string n = "", double p = 0.0)
        : id(_id), nombre(n), precio(p) {
    }

    void mostrar() const {
        cout << "ID: " << id << " | Prod: " << nombre
            << " | Precio: $" << precio << endl;
    }
};

