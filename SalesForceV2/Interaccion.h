// Archivo: Interaccion.h
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Interaccion
{
private:
    int idInteraccion;
    string tipoComunicacion;
    string resumen;

public:
    Interaccion() {
        this->idInteraccion = 0;
        this->tipoComunicacion = "";
        this->resumen = "";
    }

    Interaccion(int idInteraccion, string tipoComunicacion, string resumen) {
        this->idInteraccion = idInteraccion;
        this->tipoComunicacion = tipoComunicacion;
        this->resumen = resumen;
    }

    int getId() { return this->idInteraccion; }
    string getResumen() { return this->resumen; }
    string getTipoComunicacion() { return this->tipoComunicacion; }

    void setId(int idInteraccion) { this->idInteraccion = idInteraccion; }
    void setResumen(string resumen) { this->resumen = resumen; }
    void setTipoComunicacion(string tipoComunicacion) { this->tipoComunicacion = tipoComunicacion; }
};