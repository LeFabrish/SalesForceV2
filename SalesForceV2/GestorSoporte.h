// GestorSoporte.h
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

    // Aprovechamos la recursividad nativa del call stack del sistema para buscar un caso 
    // extrayendo (pop) en la ida y restaurando (push) en la vuelta para no alterar la estructura de la pila.
    bool buscarCasoRecursivoEnPila(Pila<Caso>& p, string idObjetivo) {
        if (p.estaVacia()) return false;
        Caso actual = p.peek();
        if (actual.getId() == idObjetivo) {
            cout << "\n  [Encontrado recursivamente]" << endl;
            actual.mostrar();
            return true;
        }
        p.pop();
        bool encontrado = buscarCasoRecursivoEnPila(p, idObjetivo);
        p.push(actual);
        return encontrado;
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
        cout << "\n  ID del caso a buscar (Binaria): ";
        int idTarget;
        cin >> idTarget;

        ordenarCasosPorID();

        // 1. Creamos un objeto Caso falso solo con el ID que queremos buscar
        Caso casoBuscado;
        casoBuscado.setId(to_string(idTarget));

        // 2. Enviamos los 3 parámetros que exige Pila.h
        int indice = casos->busquedaBinaria(
            casoBuscado,
            [](const Caso& a, const Caso& b) { return stoi(a.getId()) == stoi(b.getId()); },
            [](const Caso& a, const Caso& b) { return stoi(a.getId()) < stoi(b.getId()); }
        );

        if (indice != -1) {
            cout << "\n  [Encontrado]" << endl;
            // Lo buscamos linealmente para mostrarlo ya que sabemos que existe
            Pila<Caso> temp;
            while (!casos->estaVacia()) {
                Caso c = casos->peek();
                casos->pop();
                temp.push(c);
                if (c.getId() == to_string(idTarget)) {
                    c.mostrar();
                }
            }
            // Restauramos la pila
            while (!temp.estaVacia()) {
                casos->push(temp.peek());
                temp.pop();
            }
        }
        else {
            cout << "  [!] Caso no encontrado." << endl;
        }
    }

    void buscarCasoPorIDRecursivo() {
        cout << "\n  ID del caso a buscar (Recursiva Pila): ";
        string idTarget;
        cin >> idTarget;
        if (!buscarCasoRecursivoEnPila(*casos, idTarget)) {
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

    void guardarCasosEnArchivo() {
        GestorArchivos gestor;
        ListaSimple<string>* lineas = new ListaSimple<string>();
        Pila<Caso> pilaTemporal;

        while (!casos->estaVacia()) {
            Caso c = casos->peek();
            string lineaDato = c.getId() + "," + c.getAsunto() + "," + c.getEstado() + "," + c.getPrioridad();
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

    void cargarCasosDesdeArchivo() {
        GestorArchivos gestor;
        ListaSimple<string>* lineas = gestor.cargarLineas("Casos.txt");
        if (lineas == nullptr || lineas->estaVacia()) return;

        // Limpiamos pila temporalmente usando una Pila para invertir el orden 
        // y conservar el último guardado en la parte inferior.
        Pila<Caso> pilaTemporal;
        NodoS<string>* actual = lineas->getCabeza();

        while (actual != nullptr) {
            string l = actual->dato;
            int p1 = l.find(',');
            int p2 = l.find(',', p1 + 1);
            int p3 = l.find(',', p2 + 1);

            if (p1 != string::npos && p2 != string::npos && p3 != string::npos) {
                Caso c(l.substr(0, p1), l.substr(p1 + 1, p2 - p1 - 1), l.substr(p2 + 1, p3 - p2 - 1), l.substr(p3 + 1));
                pilaTemporal.push(c);
                int parsedId = stoi(c.getId());
                if (parsedId >= contCaso) contCaso = parsedId + 1;
            }
            actual = actual->siguiente;
        }

        while (!pilaTemporal.estaVacia()) {
            casos->push(pilaTemporal.peek());
            pilaTemporal.pop();
        }

        registrarHistorialAuto("Casos importados desde Casos.txt");
        cout << "  [OK] Casos recuperados desde 'Casos.txt'." << endl;
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
            cout << "  5. Buscar Caso por ID (Recursiva)" << endl;
            cout << "  --- Soluciones & Tareas ---" << endl;
            cout << "  6. Agregar Solucion" << endl;
            cout << "  7. Listar Soluciones" << endl;
            cout << "  8. Agregar Tarea" << endl;
            cout << "  9. Listar Tareas" << endl;
            cout << "  --- Sistema & Archivos ---" << endl;
            cout << "  10. Ver Historial de Acciones" << endl;
            cout << "  11. Guardar Casos en Archivo (.txt)" << endl;
            cout << "  12. Cargar Casos desde Archivo (.txt)" << endl;
            cout << "  0. Volver al menu principal" << endl;
            cout << "  ========================================" << endl;
            cout << "  Opcion: "; cin >> opcion;

            switch (opcion) {
            case 1: agregarCaso(); break;
            case 2: listarCasos(); break;
            case 3: ordenarCasosPorID(); break;
            case 4: buscarCasoPorIDBinario(); break;
            case 5: buscarCasoPorIDRecursivo(); break;
            case 6: agregarSolucion(); break;
            case 7: listarSoluciones(); break;
            case 8: agregarTarea(); break;
            case 9: listarTareas(); break;
            case 10:
                cout << "\n  === HISTORIAL DEL SISTEMA ===" << endl;
                historiales->mostrar();
                break;
            case 11: guardarCasosEnArchivo(); break;
            case 12: cargarCasosDesdeArchivo(); break;
            case 0: return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
        }
    }
};