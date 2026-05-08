#pragma once
#include <iostream>
#include <string>

using namespace std;

class Evento {
private:
    string id;
    string titulo;
    string fechaHora;
    string ubicacion;

public:
    Evento(string i = "", string t = "", string f = "", string u = "")
        : id(i), titulo(t), fechaHora(f), ubicacion(u) {
    }
    ~Evento() {}

    string getId() const { return id; }
    void setId(string i) { id = i; }

    string getTitulo() const { return titulo; }
    void setTitulo(string t) { titulo = t; }

    string getFechaHora() const { return fechaHora; }
    void setFechaHora(string f) { fechaHora = f; }

    string getUbicacion() const { return ubicacion; }
    void setUbicacion(string u) { ubicacion = u; }

    void mostrar() const {
        cout << "Evento [" << id << "] " << titulo << " | Fecha: " << fechaHora << " | Ubicacion: " << ubicacion << endl;
    }
};