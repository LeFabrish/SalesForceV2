#pragma once
#include "iostream"
#include "string"
using namespace std;

class Interaccion {
private:
    int id;
    string tipo;        // "Llamada", "Email", "Reunion"
    string descripcion;
    string fecha;
    int idContacto;
    int idUsuario;

public:
    Interaccion() {
        id = 0;
        tipo = "";
        descripcion = "";
        fecha = "";
        idContacto = 0;
        idUsuario = 0;
    }

    Interaccion(int id, string tipo, string descripcion,
        string fecha, int idContacto, int idUsuario) {
        this->id = id;
        this->tipo = tipo;
        this->descripcion = descripcion;
        this->fecha = fecha;
        this->idContacto = idContacto;
        this->idUsuario = idUsuario;
    }

    // Getters
    int getId() { return id; }
    string getTipo() { return tipo; }
    string getDescripcion() { return descripcion; }
    string getFecha() { return fecha; }
    int getIdContacto() { return idContacto; }
    int getIdUsuario() { return idUsuario; }

    // Setters
    void setId(int i) { id = i; }
    void setTipo(string t) { tipo = t; }
    void setDescripcion(string d) { descripcion = d; }
    void setFecha(string f) { fecha = f; }
    void setIdContacto(int ic) { idContacto = ic; }
    void setIdUsuario(int iu) { idUsuario = iu; }

    void mostrar() {
        cout << "  ID          : " << id << endl;
        cout << "  Tipo        : " << tipo << endl;
        cout << "  Descripcion : " << descripcion << endl;
        cout << "  Fecha       : " << fecha << endl;
        cout << "  ID Contacto : " << idContacto << endl;
        cout << "  ID Usuario  : " << idUsuario << endl;
        cout << "  ----------------------------------------" << endl;
    }

    void ingresar(int nuevoId) {
        id = nuevoId;
        cout << "  Tipo (Llamada/Email/Reunion) : "; cin >> tipo;
        cout << "  Descripcion                 : "; cin >> descripcion;
        cout << "  Fecha (DD/MM/AAAA)          : "; cin >> fecha;
        cout << "  ID Contacto                 : "; cin >> idContacto;
        cout << "  ID Usuario                  : "; cin >> idUsuario;
    }
};