#pragma once
#include <iostream>
#include <string>

using namespace std;

class Solucion {
private:
    string id;
    string idCasoAsociado;
    string descripcion;
    string fechaResolucion;

public:
    Solucion(string i = "", string idC = "", string d = "", string f = "")
        : id(i), idCasoAsociado(idC), descripcion(d), fechaResolucion(f) {
    }
    ~Solucion() {}

    string getId() const { return id; }
    void setId(string i) { id = i; }

    string getIdCasoAsociado() const { return idCasoAsociado; }
    void setIdCasoAsociado(string idC) { idCasoAsociado = idC; }

    string getDescripcion() const { return descripcion; }
    void setDescripcion(string d) { descripcion = d; }

    string getFechaResolucion() const { return fechaResolucion; }
    void setFechaResolucion(string f) { fechaResolucion = f; }

    void mostrar() const {
        cout << "Solucion [" << id << "] para Caso " << idCasoAsociado << " | Detalle: " << descripcion << " | Fecha: " << fechaResolucion << endl;
    }
};