// Archivo GestorSoporte.h
#pragma once
#include <iostream>
#include <string>
#include "Pila.h"
#include "Caso.h"
#include "Solucion.h"
#include "Tarea.h"
#include "Evento.h"
#include "Historial.h"
#include "GestorArchivos.h" 

using namespace std;

class GestorSoporte {
private:
    Pila<Caso>* casos;
    Pila<Solucion>* soluciones;
    Pila<Tarea>* tareas;
    Pila<Evento>* eventos;
    Pila<Historial>* historiales;

    int contCaso;
    int contSolucion;
    int contTarea;
    int contEvento;
    int contHistorial;

    void registrarHistorialAuto(string accion) {
        Historial h;
        h.setId(to_string(contHistorial++));
        h.setAccion(accion);
        h.setFecha("Reciente");
        historiales->push(h);
    }

public:
    GestorSoporte() {
        casos = new Pila<Caso>();
        soluciones = new Pila<Solucion>();
        tareas = new Pila<Tarea>();
        eventos = new Pila<Evento>();
        historiales = new Pila<Historial>();

        contCaso = 1;
        contSolucion = 1;
        contTarea = 1;
        contEvento = 1;
        contHistorial = 1;
    }

    ~GestorSoporte() {
        delete casos;
        delete soluciones;
        delete tareas;
        delete eventos;
        delete historiales;
    }

    void agregarCaso() {
        Caso c;
        cout << "\n  === NUEVO CASO ===" << endl;
        c.ingresar(contCaso++);
        casos->push(c);
        registrarHistorialAuto("Caso registrado: " + c.getId());
        cout << "  [OK] Caso registrado." << endl;
    }

    void listarCasos() {
        cout << "\n  === LISTA DE CASOS ===" << endl;
        if (casos->estaVacia()) {
            cout << "  No hay casos registrados." << endl;
            return;
        }
        casos->mostrar();
    }

    void ordenarCasosPorID() {
        casos->ordenarBurbujaOptimizada([](const Caso& a, const Caso& b) {
            return a.getId() < b.getId();
            });
        registrarHistorialAuto("Casos ordenados por ID");
        cout << "  [OK] Casos ordenados en la pila." << endl;
    }

    void buscarCasoPorIDBinario() {
        cout << "\n  ID del caso a buscar: ";
        int idTarget;
        cin >> idTarget;

        ordenarCasosPorID();

        Caso* resultado = casos->busquedaBinaria(
            [](const Caso& c) { return stoi(c.getId()); },
            idTarget
        );

        if (resultado != nullptr) {
            cout << "\n  [Encontrado]" << endl;
            resultado->mostrar();
            delete resultado;
        }
        else {
            cout << "  [!] Caso no encontrado." << endl;
        }
    }

    void agregarSolucion() {
        Solucion s;
        cout << "\n  === NUEVA SOLUCION ===" << endl;
        s.ingresar(contSolucion++);
        soluciones->push(s);
        registrarHistorialAuto("Solucion registrada: " + s.getId());
        cout << "  [OK] Solucion registrada." << endl;
    }

    void listarSoluciones() {
        cout << "\n  === LISTA DE SOLUCIONES ===" << endl;
        soluciones->mostrar();
    }

    void agregarTarea() {
        Tarea t;
        cout << "\n  === NUEVA TAREA ===" << endl;
        t.ingresar(contTarea++);
        tareas->push(t);
        registrarHistorialAuto("Tarea registrada: " + t.getId());
        cout << "  [OK] Tarea registrada." << endl;
    }

    void listarTareas() {
        cout << "\n  === LISTA DE TAREAS ===" << endl;
        tareas->mostrar();
    }

    // Se extraen los datos apilados a una lista enlazada simple para interactuar con GestorArchivos 
    // sin perder el orden LIFO original en la estructura en memoria.
    void guardarCasosEnArchivo() {
        GestorArchivos gestor;
        ListaSimple<string>* lineas = new ListaSimple<string>();
        Pila<Caso> pilaTemporal;

        while (!casos->estaVacia()) {
            Caso c = casos->peek();

            string lineaDato = "ID:" + c.getId() + " | Asunto:" + c.getAsunto() + " | Estado:" + c.getEstado();
            lineas->insertar(lineaDato);

            pilaTemporal.push(c);
            casos->pop();
        }

        while (!pilaTemporal.estaVacia()) {
            casos->push(pilaTemporal.peek());
            pilaTemporal.pop();
        }

        gestor.guardarLineas("Casos.txt", lineas);
        registrarHistorialAuto("Casos exportados a Casos.txt");
        cout << "  [OK] Casos guardados exitosamente en 'Casos.txt'." << endl;

        delete lineas;
    }

    void menuSoporte() {
        int opcion;
        while (true) {
            cout << "\n  ========================================" << endl;
            cout << "        MODULO 3 - GESTION DE SOPORTE    " << endl;
            cout << "  ========================================" << endl;
            cout << "  --- Casos ---" << endl;
            cout << "  1. Agregar Caso" << endl;
            cout << "  2. Listar Casos (LIFO)" << endl;
            cout << "  3. Ordenar Casos por ID (Burbuja)" << endl;
            cout << "  4. Buscar Caso por ID (Binaria)" << endl;
            cout << "  --- Soluciones & Tareas ---" << endl;
            cout << "  5. Agregar Solucion" << endl;
            cout << "  6. Listar Soluciones" << endl;
            cout << "  7. Agregar Tarea" << endl;
            cout << "  8. Listar Tareas" << endl;
            cout << "  --- Sistema & Archivos ---" << endl;
            cout << "  9. Ver Historial de Acciones" << endl;
            cout << "  10. Guardar Casos en Archivo (.txt)" << endl;
            cout << "  0. Volver al menu principal" << endl;
            cout << "  ========================================" << endl;
            cout << "  Opcion: "; cin >> opcion;

            switch (opcion) {
            case 1: agregarCaso(); break;
            case 2: listarCasos(); break;
            case 3: ordenarCasosPorID(); break;
            case 4: buscarCasoPorIDBinario(); break;
            case 5: agregarSolucion(); break;
            case 6: listarSoluciones(); break;
            case 7: agregarTarea(); break;
            case 8: listarTareas(); break;
            case 9:
                cout << "\n  === HISTORIAL DEL SISTEMA ===" << endl;
                historiales->mostrar();
                break;
            case 10: guardarCasosEnArchivo(); break;
            case 0: return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
        }
    }
};