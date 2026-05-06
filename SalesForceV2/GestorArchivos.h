// Archivo: GestorArchivos.h
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Listar.h" // Para el manejo de lineas reemplazamos el vector.h por nuestra estructura de datos

using namespace std;

class GestorArchivos
{
public:
    GestorArchivos() {}
    ~GestorArchivos() {}

    Lista<string>* cargarLineas(string rutaArchivo) {
        Lista<string>* lineas = new Lista<string>();
        ifstream archivo(rutaArchivo);
        string linea;

        if (archivo.is_open()) {
            while (getline(archivo, linea)) {
                lineas->agregar(linea);
            }
            archivo.close();
        }
        else {
            cout << "No se pudo abrir el archivo " << rutaArchivo << " para lectura." << endl;
        }
        return lineas;
    }

    void guardarLineas(string rutaArchivo, Lista<string>* lineas) {
        ofstream archivo(rutaArchivo); // Esto sobrescribe el archivo con la información más reciente

        if (archivo.is_open()) {
            for (int i = 0; i < lineas->getLongitud(); i++) {
                archivo << lineas->obtener(i) << "\n";
            }
            archivo.close();
        }
        else {
            cout << "No se pudo abrir el archivo " << rutaArchivo << " para escritura." << endl;
        }
    }
};