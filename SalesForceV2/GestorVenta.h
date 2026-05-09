#pragma once
#include "iostream"
#include "string"
#include "Cola.h"
#include "ListaDoble.h"
#include "ListaSimple.h"
#include "Cliente_Potencial.h"
#include "Oportunidad.h"
#include "Producto.h"
#include "Cotizacion.h"
#include "Contrato.h"
#include "GestorArchivos.h"

using namespace std;

class GestorVenta {
private:
    Cola<Cliente_Potencial>   colaClientes;
    ListaDoble<Oportunidad>   listaOportunidades;
    ListaSimple<Producto>     catalogoProductos;
    ListaSimple<Cotizacion>   listaCotizaciones;
    ListaSimple<Contrato>     listaContratos;
    int contadorCliente;
    int contadorOportunidad;
    int contadorProducto;
    int contadorCotizacion;
    int contadorContrato;

    // Se aísla el nodo en el parámetro para permitir el avance recursivo sin perder la referencia de la lista original.
    double calcularValorEmbudoRecursivo(NodoD<Oportunidad>* nodo) {
        if (nodo == nullptr) return 0.0;
        return nodo->dato.getValorEsperado() + calcularValorEmbudoRecursivo(nodo->siguiente);
    }

public:
    GestorVenta() {
        contadorCliente = 1;
        contadorOportunidad = 1;
        contadorProducto = 1;
        contadorCotizacion = 1;
        contadorContrato = 1;
    }

    void registrarCliente() {
        Cliente_Potencial c;
        cout << "\n  === NUEVO CLIENTE POTENCIAL ===" << endl;
        c.ingresar(contadorCliente++);
        colaClientes.enqueue(c);
        cout << "  [OK] Cliente registrado en la cola." << endl;
    }

    void atenderSiguienteCliente() {
        if (colaClientes.estaVacia()) {
            cout << "  [!] No hay clientes pendientes en la cola." << endl;
            return;
        }
        cout << "\n  === ATENDIENDO CLIENTE ===" << endl;
        colaClientes.getFrente().mostrar();
        colaClientes.dequeue();
    }

    void ordenarClientesShell() {
        if (colaClientes.estaVacia()) {
            cout << "  [!] Cola vacia, no hay nada que ordenar." << endl;
            return;
        }
        auto comp = [](Cliente_Potencial a, Cliente_Potencial b) {
            return a.getId() < b.getId();
            };
        colaClientes.ordenarShell(comp);
        cout << "  [OK] Clientes pendientes ordenados usando Shell Sort." << endl;
    }

    void crearOportunidad() {
        Oportunidad o;
        cout << "\n  === NUEVA OPORTUNIDAD ===" << endl;
        o.ingresar(contadorOportunidad++);
        listaOportunidades.insertar(o);
        cout << "  [OK] Oportunidad creada." << endl;
    }

    void mostrarEmbudo() {
        cout << "\n  === EMBUDO DE VENTAS ===" << endl;
        if (listaOportunidades.estaVacia()) {
            cout << "  No hay oportunidades registradas." << endl;
            return;
        }
        listaOportunidades.mostrar();
        cout << "\n  > Valor Proyectado Total: $" << calcularValorEmbudoRecursivo(listaOportunidades.getCabeza()) << endl;
    }

    void buscarOportunidad() {
        string titulo;
        cout << "\n  Titulo a buscar: "; cin >> titulo;

        auto criterio = [titulo](Oportunidad op) {
            return op.getTitulo() == titulo;
            };

        NodoD<Oportunidad>* resultado = listaOportunidades.buscar(criterio);
        if (resultado != nullptr) {
            cout << "\n  [Encontrado]" << endl;
            resultado->dato.mostrar();
        }
        else {
            cout << "  [!] Oportunidad no encontrada." << endl;
        }
    }

    void ordenarOportunidadesPorValor() {
        auto comparar = [](Oportunidad a, Oportunidad b) {
            return a.getValorEsperado() < b.getValorEsperado();
            };
        listaOportunidades.ordenar(comparar);
        cout << "  [OK] Oportunidades ordenadas por valor." << endl;
    }

    void agregarProducto() {
        Producto p;
        cout << "\n  === NUEVO PRODUCTO ===" << endl;
        p.ingresar(contadorProducto++);
        catalogoProductos.insertar(p);
        cout << "  [OK] Producto agregado al catalogo." << endl;
    }

    void mostrarProductosPremium() {
        double precioMinimo;
        cout << "\n  Precio minimo para filtrar: "; cin >> precioMinimo;
        cout << "\n  === PRODUCTOS PREMIUM (Mayor a $" << precioMinimo << ") ===" << endl;

        auto esPremium = [precioMinimo](Producto p) {
            return p.getPrecio() >= precioMinimo;
            };

        NodoS<Producto>* actual = catalogoProductos.getCabeza();
        bool hayPremium = false;
        while (actual != nullptr) {
            if (esPremium(actual->dato)) {
                actual->dato.mostrar();
                hayPremium = true;
            }
            actual = actual->siguiente;
        }
        if (!hayPremium)
            cout << "  No hay productos que superen ese precio." << endl;
    }

    void generarCotizacion() {
        Cotizacion c;
        cout << "\n  === NUEVA COTIZACION ===" << endl;
        c.ingresar(contadorCotizacion++);
        listaCotizaciones.insertar(c);
        cout << "  [OK] Cotizacion generada." << endl;
    }

    void cerrarContrato() {
        Contrato c;
        cout << "\n  === NUEVO CONTRATO ===" << endl;
        c.ingresar(contadorContrato++);
        listaContratos.insertar(c);
        cout << "  [OK] Contrato cerrado." << endl;
    }

    void guardarProductos() {
        GestorArchivos gestor;
        ListaSimple<string>* lineas = new ListaSimple<string>();
        NodoS<Producto>* actual = catalogoProductos.getCabeza();
        while (actual != nullptr) {
            Producto p = actual->dato;
            string linea = to_string(p.getId()) + "," + p.getNombre() + "," + to_string(p.getPrecio()) + "," + p.getCategoria();
            lineas->insertar(linea);
            actual = actual->siguiente;
        }
        gestor.guardarLineas("productos.txt", lineas);
        cout << "  [OK] Productos almacenados en 'productos.txt'" << endl;
        delete lineas;
    }

    void cargarProductos() {
        GestorArchivos gestor;
        ListaSimple<string>* lineas = gestor.cargarLineas("productos.txt");
        if (lineas == nullptr || lineas->estaVacia()) return;

        NodoS<string>* actual = lineas->getCabeza();
        while (actual != nullptr) {
            string linea = actual->dato;
            int p1 = linea.find(',');
            int p2 = linea.find(',', p1 + 1);
            int p3 = linea.find(',', p2 + 1);

            if (p1 != string::npos && p2 != string::npos && p3 != string::npos) {
                Producto p;
                p.setId(stoi(linea.substr(0, p1)));
                p.setNombre(linea.substr(p1 + 1, p2 - p1 - 1));
                p.setPrecio(stod(linea.substr(p2 + 1, p3 - p2 - 1)));
                p.setCategoria(linea.substr(p3 + 1));
                catalogoProductos.insertar(p);
                contadorProducto++;
            }
            actual = actual->siguiente;
        }
        cout << "  [OK] Productos recuperados desde 'productos.txt'" << endl;
        delete lineas;
    }

    void menuPrincipal() {
        int opcion;
        while (1) {
            cout << "\n  ========================================" << endl;
            cout << "     MODULO 2 - EMBUDO DE VENTAS         " << endl;
            cout << "  ========================================" << endl;
            cout << "  --- Clientes Potenciales ---" << endl;
            cout << "  1. Registrar Cliente Potencial" << endl;
            cout << "  2. Atender siguiente Cliente (Cola)" << endl;
            cout << "  3. Ordenar Cola de Clientes (Shell Sort)" << endl;
            cout << "  --- Oportunidades ---" << endl;
            cout << "  4. Crear Oportunidad Comercial" << endl;
            cout << "  5. Ver Embudo de Ventas (Con total recursivo)" << endl;
            cout << "  6. Buscar Oportunidad" << endl;
            cout << "  7. Ordenar Oportunidades por Valor" << endl;
            cout << "  --- Productos ---" << endl;
            cout << "  8. Agregar Producto" << endl;
            cout << "  9. Ver Productos Premium" << endl;
            cout << "  10. Guardar Productos en Archivo" << endl;
            cout << "  11. Cargar Productos desde Archivo" << endl;
            cout << "  --- Cotizaciones y Contratos ---" << endl;
            cout << "  12. Generar Cotizacion" << endl;
            cout << "  13. Cerrar Contrato" << endl;
            cout << "  0. Volver al menu principal" << endl;
            cout << "  ========================================" << endl;
            cout << "  Opcion: "; cin >> opcion;

            switch (opcion) {
            case 1:  registrarCliente();            break;
            case 2:  atenderSiguienteCliente();     break;
            case 3:  ordenarClientesShell();        break;
            case 4:  crearOportunidad();            break;
            case 5:  mostrarEmbudo();               break;
            case 6:  buscarOportunidad();           break;
            case 7:  ordenarOportunidadesPorValor(); break;
            case 8:  agregarProducto();             break;
            case 9:  mostrarProductosPremium();     break;
            case 10: guardarProductos();            break;
            case 11: cargarProductos();             break;
            case 12: generarCotizacion();           break;
            case 13: cerrarContrato();              break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
        }
    }
};