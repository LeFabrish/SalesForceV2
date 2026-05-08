#pragma once
#include <iostream>
#include <string>

using namespace std;

class Tarea {
private:
    string id;
    string descripcion;
    string estado;
    string fechaLimite;

public:
    Tarea(string i = "", string d = "", string e = "Pendiente", string f = "")
        : id(i), descripcion(d), estado(e), fechaLimite(f) {
    }
    ~Tarea() {}

    string getId() const { return id; }
    void setId(string i) { id = i; }

    string getDescripcion() const { return descripcion; }
    void setDescripcion(string d) { descripcion = d; }

    string getEstado() const { return estado; }
    void setEstado(string e) { estado = e; }

    string getFechaLimite() const { return fechaLimite; }
    void setFechaLimite(string f) { fechaLimite = f; }

    void mostrar() const {
        cout << "Tarea [" << id << "] " << descripcion << " | Limite: " << fechaLimite << " | Estado: " << estado << endl;
    }
};