#pragma once
#include "iostream"
#include "string"
using namespace std;

class UsuarioCRM {
private:
    int id;
    string nombre;
    string apellido;
    string rol;         // "Vendedor", "Soporte", "Admin"
    string username;
    string password;

public:
    UsuarioCRM() {
        id = 0;
        nombre = "";
        apellido = "";
        rol = "";
        username = "";
        password = "";
    }

    UsuarioCRM(int id, string nombre, string apellido,
        string rol, string username, string password) {
        this->id = id;
        this->nombre = nombre;
        this->apellido = apellido;
        this->rol = rol;
        this->username = username;
        this->password = password;
    }

    // Getters
    int getId() { return id; }
    string getNombre() { return nombre; }
    string getApellido() { return apellido; }
    string getRol() { return rol; }
    string getUsername() { return username; }
    string getPassword() { return password; }

    // Setters
    void setId(int i) { id = i; }
    void setNombre(string n) { nombre = n; }
    void setApellido(string a) { apellido = a; }
    void setRol(string r) { rol = r; }
    void setUsername(string u) { username = u; }
    void setPassword(string p) { password = p; }

    void mostrar() {
        cout << "  ID        : " << id << endl;
        cout << "  Nombre    : " << nombre << " " << apellido << endl;
        cout << "  Rol       : " << rol << endl;
        cout << "  Username  : " << username << endl;
        cout << "  ----------------------------------------" << endl;
    }

    void ingresar(int nuevoId) {
        id = nuevoId;
        cout << "  Nombre    : "; getline(cin, nombre);
        cout << "  Apellido  : "; getline(cin, apellido);
        cout << "  Rol (Vendedor/Soporte/Admin) : "; getline(cin, rol);
        cout << "  Username  : "; getline(cin, username);
        cout << "  Password  : "; getline(cin, password);
    }
};