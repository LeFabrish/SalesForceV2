#pragma once
#include "iostream"
#include "fstream"
#include "string"
#include "ListaSimple.h"
using namespace std;

class GestorArchivos {
public:
    GestorArchivos() {}
    ~GestorArchivos() {}

    // Carga líneas de un archivo .txt en una ListaSimple<string>
    ListaSimple<string>* cargarLineas(string rutaArchivo) {
        ListaSimple<string>* lineas = new ListaSimple<string>();
        ifstream archivo(rutaArchivo);
        string linea;

        if (archivo.is_open()) {
            while (getline(archivo, linea)) {
                lineas->insertar(linea);
            }
            archivo.close();
        }
        else {
            cout << "  [!] No se pudo abrir: " << rutaArchivo << endl;
        }
        return lineas;
    }

    // Guarda todas las líneas de la lista en un archivo .txt
    void guardarLineas(string rutaArchivo, ListaSimple<string>* lineas) {
        ofstream archivo(rutaArchivo);

        if (archivo.is_open()) {
            NodoS<string>* actual = lineas->getCabeza();
            while (actual != nullptr) {
                archivo << actual->dato << "\n";
                actual = actual->siguiente;
            }
            archivo.close();
        }
        else {
            cout << "   No se pudo guardar en: " << rutaArchivo << endl;
        }
    }
};