#pragma once
#include <iostream>
#include <string>

using namespace std;

class Historial {
private:
    string id;
    string moduloAsociado;
    string accion;
    string fecha;

public:
    Historial(string i = "", string m = "", string a = "", string f = "")
        : id(i), moduloAsociado(m), accion(a), fecha(f) {
    }
    ~Historial() {}

    string getId() const { return id; }
    void setId(string i) { id = i; }

    string getModuloAsociado() const { return moduloAsociado; }
    void setModuloAsociado(string m) { moduloAsociado = m; }

    string getAccion() const { return accion; }
    void setAccion(string a) { accion = a; }

    string getFecha() const { return fecha; }
    void setFecha(string f) { fecha = f; }

    void mostrar() const {
        cout << "Historial [" << id << "] Modulo: " << moduloAsociado << " | Accion: " << accion << " | Fecha: " << fecha << endl;
    }

    bool operator>(const Historial& h) const { return id > h.id; }
    bool operator<(const Historial& h) const { return id < h.id; }
    bool operator==(const Historial& h) const { return id == h.id; }
};