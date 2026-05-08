#pragma once
#include <iostream>
#include <string>

using namespace std;

class Caso {
private:
    string id;
    string asunto;
    string estado;
    string prioridad;

public:
    Caso(string i = "", string a = "", string e = "Abierto", string p = "Media")
        : id(i), asunto(a), estado(e), prioridad(p) {}
    ~Caso() {}

    string getId() const { return id; }
    void setId(string i) { id = i; }
    
    string getAsunto() const { return asunto; }
    void setAsunto(string a) { asunto = a; }
    
    string getEstado() const { return estado; }
    void setEstado(string e) { estado = e; }
    
    string getPrioridad() const { return prioridad; }
    void setPrioridad(string p) { prioridad = p; }

    void mostrar() const {
        cout << "Caso [" << id << "] " << asunto << " | Prioridad: " << prioridad << " | Estado: " << estado << endl;
    }
};