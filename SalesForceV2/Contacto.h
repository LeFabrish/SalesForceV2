#pragma once
#include "iostream"
#include "string"
#include "Direccion.h"
using namespace std;

class Contacto {
private:
    int id;
    string nombre;
    string apellido;
    string cargo;
    string telefono;
    string email;
    int idCuenta;
    Direccion direccion;

public:
    Contacto() {
        id = 0;
        nombre = "";
        apellido = "";
        cargo = "";
        telefono = "";
        email = "";
        idCuenta = 0;
    }

    Contacto(int id, string nombre, string apellido, string cargo,
        string telefono, string email, int idCuenta, Direccion direccion) {
        this->id = id;
        this->nombre = nombre;
        this->apellido = apellido;
        this->cargo = cargo;
        this->telefono = telefono;
        this->email = email;
        this->idCuenta = idCuenta;
        this->direccion = direccion;
    }

    // Getters
    int getId() { return id; }
    string getNombre() { return nombre; }
    string getApellido() { return apellido; }
    string getCargo() { return cargo; }
    string getTelefono() { return telefono; }
    string getEmail() { return email; }
    int getIdCuenta() { return idCuenta; }
    Direccion getDireccion() { return direccion; }

    // Setters
    void setId(int i) { id = i; }
    void setNombre(string n) { nombre = n; }
    void setApellido(string a) { apellido = a; }
    void setCargo(string c) { cargo = c; }
    void setTelefono(string t) { telefono = t; }
    void setEmail(string e) { email = e; }
    void setIdCuenta(int ic) { idCuenta = ic; }
    void setDireccion(Direccion d) { direccion = d; }

    void mostrar() {
        cout << "  ID        : " << id << endl;
        cout << "  Nombre    : " << nombre << " " << apellido << endl;
        cout << "  Cargo     : " << cargo << endl;
        cout << "  Telefono  : " << telefono << endl;
        cout << "  Email     : " << email << endl;
        cout << "  ID Cuenta : " << idCuenta << endl;
        cout << "  Direccion :" << endl;
        direccion.mostrar();
        cout << "  ----------------------------------------" << endl;
    }

    void ingresar(int nuevoId) {
        id = nuevoId;
        cout << "  Nombre    : "; cin >> nombre;
        cout << "  Apellido  : "; cin >> apellido;
        cout << "  Cargo     : "; cin >> cargo;
        cout << "  Telefono  : "; cin >> telefono;
        cout << "  Email     : "; cin >> email;
        cout << "  ID Cuenta : "; cin >> idCuenta;
        cout << "  Direccion :" << endl;
        direccion.ingresar();
    }
};