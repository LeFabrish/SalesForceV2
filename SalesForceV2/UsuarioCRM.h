// Archivo: UsuarioCRM.h
#pragma once
#include <iostream>
#include <string>

using namespace std;

class UsuarioCRM
{
private:
    int idUsuario;
    string nombreUsuario;
    string contrasenia;

public:
    UsuarioCRM() {
        this->idUsuario = 0;
        this->nombreUsuario = "";
        this->contrasenia = "";
    }

    UsuarioCRM(int id, string nombre, string contrasenia) {
        this->idUsuario = id;
        this->nombreUsuario = nombre;
        this->contrasenia = contrasenia;
    }

    // Se agregaron los tipos de retorno que faltaban
    int getIdUsuario() { return this->idUsuario; }
    string getNombreUsuario() { return this->nombreUsuario; }
    string getContrasenia() { return this->contrasenia; }

    void setIdUsuario(int id) { this->idUsuario = id; }
    void setNombreUsuario(string nombre) { this->nombreUsuario = nombre; }
    void setContrasenia(string contrasenia) { this->contrasenia = contrasenia; }
};