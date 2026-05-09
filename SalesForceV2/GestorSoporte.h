#pragma once
#include "iostream"
#include "string"
#include "Pila.h"
#include "Cola.h"
#include "ListaSimple.h"
#include "Caso.h"
#include "Solucion.h"
#include "Tarea.h"
#include "Evento.h"
#include "Historial.h"
#include "GestorArchivos.h"
using namespace std;

class GestorSoporte {
private:
    Cola<Caso>           colaCasos;
    Pila<Solucion>       pilaSoluciones;
    Cola<Tarea>          colaTareas;
    ListaSimple<Evento>  listaEventos;
    Pila<Historial>      pilaHistorial;
    int contadorCaso;
    int contadorSolucion;
    int contadorTarea;
    int contadorEvento;
    int contadorHistorial;

public:
    GestorSoporte() {
        contadorCaso = 1;
        contadorSolucion = 1;
        contadorTarea = 1;
        contadorEvento = 1;
        contadorHistorial = 1;
    }

    // ─────────────────────────────────────────
    //  CASOS
    // ─────────────────────────────────────────
    void registrarCaso() {
        Caso c;
        cout << "\n  === NUEVO CASO ===" << endl;
        c.ingresar(contadorCaso++);
        colaCasos.enqueue(c);
        cout << "  [OK] Caso registrado en la cola." << endl;
    }

    void atenderCaso() {
        if (colaCasos.estaVacia()) {
            cout << "  [!] No hay casos pendientes." << endl;
            return;
        }
        cout << "\n  === CASO EN ATENCION ===" << endl;
        colaCasos.getFrente().mostrar();
        colaCasos.dequeue();
        cout << "  [OK] Caso atendido." << endl;
    }

    void mostrarCasos() {
        cout << "\n  === COLA DE CASOS ===" << endl;
        if (colaCasos.estaVacia()) {
            cout << "  No hay casos pendientes." << endl;
            return;
        }
        colaCasos.mostrar();
    }

    // ─────────────────────────────────────────
    //  SOLUCIONES
    // ─────────────────────────────────────────
    void registrarSolucion() {
        Solucion s;
        cout << "\n  === NUEVA SOLUCION ===" << endl;
        s.ingresar(contadorSolucion++);
        pilaSoluciones.push(s);
        cout << "  [OK] Solucion registrada." << endl;
    }

    void verUltimaSolucion() {
        if (pilaSoluciones.estaVacia()) {
            cout << "  [!] No hay soluciones registradas." << endl;
            return;
        }
        cout << "\n  === ULTIMA SOLUCION ===" << endl;
        pilaSoluciones.peek().mostrar();
    }

    void mostrarSoluciones() {
        cout << "\n  === HISTORIAL DE SOLUCIONES ===" << endl;
        if (pilaSoluciones.estaVacia()) {
            cout << "  No hay soluciones registradas." << endl;
            return;
        }
        pilaSoluciones.mostrar();
    }

    // ─────────────────────────────────────────
    //  TAREAS
    // ─────────────────────────────────────────
    void agregarTarea() {
        Tarea t;
        cout << "\n  === NUEVA TAREA ===" << endl;
        t.ingresar(contadorTarea++);
        colaTareas.enqueue(t);
        cout << "  [OK] Tarea agregada." << endl;
    }

    void atenderTarea() {
        if (colaTareas.estaVacia()) {
            cout << "  [!] No hay tareas pendientes." << endl;
            return;
        }
        cout << "\n  === TAREA EN ATENCION ===" << endl;
        colaTareas.getFrente().mostrar();
        colaTareas.dequeue();
        cout << "  [OK] Tarea completada." << endl;
    }

    void mostrarTareas() {
        cout << "\n  === COLA DE TAREAS ===" << endl;
        if (colaTareas.estaVacia()) {
            cout << "  No hay tareas pendientes." << endl;
            return;
        }
        colaTareas.mostrar();
    }

    // ─────────────────────────────────────────
    //  EVENTOS
    // ─────────────────────────────────────────
    void agregarEvento() {
        Evento e;
        cout << "\n  === NUEVO EVENTO ===" << endl;
        e.ingresar(contadorEvento++);
        listaEventos.insertar(e);
        cout << "  [OK] Evento registrado." << endl;
    }

    void mostrarEventos() {
        cout << "\n  === LISTA DE EVENTOS ===" << endl;
        if (listaEventos.estaVacia()) {
            cout << "  No hay eventos registrados." << endl;
            return;
        }
        listaEventos.mostrar();
    }

    void buscarEvento() {
        string titulo;
        cout << "\n  Titulo a buscar: "; getline(cin, titulo);
        auto criterio = [titulo](Evento e) {
            return e.getTitulo() == titulo;
            };
        NodoS<Evento>* resultado = listaEventos.buscar(criterio);
        if (resultado != nullptr) {
            cout << "\n  [Encontrado]" << endl;
            resultado->dato.mostrar();
        }
        else {
            cout << "  [!] Evento no encontrado." << endl;
        }
    }

    // ─────────────────────────────────────────
    //  HISTORIAL
    // ─────────────────────────────────────────
    void registrarHistorial() {
        Historial h;
        cout << "\n  === NUEVO REGISTRO EN HISTORIAL ===" << endl;
        h.ingresar(contadorHistorial++);
        pilaHistorial.push(h);
        cout << "  [OK] Historial registrado." << endl;
    }

    void verUltimoHistorial() {
        if (pilaHistorial.estaVacia()) {
            cout << "  [!] Historial vacio." << endl;
            return;
        }
        cout << "\n  === ULTIMO REGISTRO ===" << endl;
        pilaHistorial.peek().mostrar();
    }

    void mostrarHistorial() {
        cout << "\n  === HISTORIAL COMPLETO ===" << endl;
        if (pilaHistorial.estaVacia()) {
            cout << "  No hay registros." << endl;
            return;
        }
        pilaHistorial.mostrar();
    }

    // ─────────────────────────────────────────
    //  RECURSIVIDAD
    // ─────────────────────────────────────────
    bool buscarCasoRec(NodoS<Caso>* nodo, int idBuscado) {
        if (nodo == nullptr) return false;
        if (nodo->dato.getId() == idBuscado) return true;
        return buscarCasoRec(nodo->siguiente, idBuscado);
    }

    void buscarCasoPorId() {
        int id;
        cout << "\n  ID del Caso a buscar: ";cin>> id;
        bool encontrado = buscarCasoRec(colaCasos.getFrenteNodo(), id);
        if (encontrado)
            cout << "  [OK] Caso #" << id << " encontrado." << endl;
        else
            cout << "  [!] Caso #" << id << " no encontrado." << endl;
    }

    // ─────────────────────────────────────────
    //  ARCHIVOS - CASOS
    // ─────────────────────────────────────────
    void guardarCasos() {
        ListaSimple<string>* lineas = new ListaSimple<string>();
        NodoS<Caso>* actual = colaCasos.getFrenteNodo();
        while (actual != nullptr) {
            Caso c = actual->dato;
            string linea = to_string(c.getId()) + "," +
                c.getAsunto() + "," +
                c.getEstado() + "," +
                c.getPrioridad();
            lineas->insertar(linea);
            actual = actual->siguiente;
        }
        GestorArchivos gestor;
        gestor.guardarLineas("casos.txt", lineas);
        cout << "  [OK] Casos guardados en casos.txt" << endl;
    }

    void cargarCasos() {
        GestorArchivos gestor;
        ListaSimple<string>* lineas = gestor.cargarLineas("casos.txt");
        NodoS<string>* actual = lineas->getCabeza();
        while (actual != nullptr) {
            string linea = actual->dato;
            int p1 = linea.find(',');
            int p2 = linea.find(',', p1 + 1);
            int p3 = linea.find(',', p2 + 1);

            Caso c;
            c.setId(stoi(linea.substr(0, p1)));
            c.setAsunto(linea.substr(p1 + 1, p2 - p1 - 1));
            c.setEstado(linea.substr(p2 + 1, p3 - p2 - 1));
            c.setPrioridad(linea.substr(p3 + 1));
            colaCasos.enqueue(c);
            contadorCaso++;
            actual = actual->siguiente;
        }
        cout << "  [OK] Casos cargados desde casos.txt" << endl;
    }

    // ─────────────────────────────────────────
    //  MENU
    // ─────────────────────────────────────────
    void menu() {
        int opcion;
        while (1) {
            cout << "\n  ========================================" << endl;
            cout << "     MODULO 3 - OPERACIONES Y SOPORTE   " << endl;
            cout << "  ========================================" << endl;
            cout << "  --- Casos ---" << endl;
            cout << "  1. Registrar Caso" << endl;
            cout << "  2. Atender siguiente Caso (Cola)" << endl;
            cout << "  3. Ver Casos pendientes" << endl;
            cout << "  4. Buscar Caso por ID (Recursivo)" << endl;
            cout << "  --- Soluciones ---" << endl;
            cout << "  5. Registrar Solucion" << endl;
            cout << "  6. Ver ultima Solucion" << endl;
            cout << "  7. Ver todas las Soluciones" << endl;
            cout << "  --- Tareas ---" << endl;
            cout << "  8. Agregar Tarea" << endl;
            cout << "  9. Atender siguiente Tarea (Cola)" << endl;
            cout << "  10. Ver Tareas pendientes" << endl;
            cout << "  --- Eventos ---" << endl;
            cout << "  11. Agregar Evento" << endl;
            cout << "  12. Ver Eventos" << endl;
            cout << "  13. Buscar Evento" << endl;
            cout << "  --- Historial ---" << endl;
            cout << "  14. Registrar en Historial" << endl;
            cout << "  15. Ver ultimo registro" << endl;
            cout << "  16. Ver Historial completo" << endl;
            cout << "  --- Archivos ---" << endl;
            cout << "  17. Guardar Casos" << endl;
            cout << "  18. Cargar Casos" << endl;
            cout << "  0. Volver al menu principal" << endl;
            cout << "  ========================================" << endl;
            cout << "  Opcion: "; cin >> opcion;
            cin.ignore();
            switch (opcion) {
            case 1:  registrarCaso();      break;
            case 2:  atenderCaso();        break;
            case 3:  mostrarCasos();       break;
            case 4:  buscarCasoPorId();    break;
            case 5:  registrarSolucion();  break;
            case 6:  verUltimaSolucion();  break;
            case 7:  mostrarSoluciones();  break;
            case 8:  agregarTarea();       break;
            case 9:  atenderTarea();       break;
            case 10: mostrarTareas();      break;
            case 11: agregarEvento();      break;
            case 12: mostrarEventos();     break;
            case 13: buscarEvento();       break;
            case 14: registrarHistorial(); break;
            case 15: verUltimoHistorial(); break;
            case 16: mostrarHistorial();   break;
            case 17: guardarCasos();       break;
            case 18: cargarCasos();        break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
        }
    }
};