// Archivo: Contacto.h
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Contacto
{
private:
    int idContacto;
    string nombreRepresentante;
    string cargo;

public:
    Contacto() {
        idContacto = 0;
        nombreRepresentante = "";
        cargo = "";
    }

    Contacto(int idContacto, string nombreRepresentante, string cargo) {
        this->idContacto = idContacto;
        this->nombreRepresentante = nombreRepresentante;
        this->cargo = cargo;
    }

    int getIdContacto() { return idContacto; }
    string getNombreRepresentante() { return nombreRepresentante; }
    string getCargo() { return cargo; }

    void setIdContacto(int idContacto) { this->idContacto = idContacto; }
    void setNombreRepresentante(string nombreRepresentante) { this->nombreRepresentante = nombreRepresentante; }
    void setCargo(string cargo) { this->cargo = cargo; }
};