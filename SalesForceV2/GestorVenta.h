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
    }

    void buscarOportunidad() {
        string titulo;
        cout << "\n  Titulo a buscar: "; cin >> titulo;

        // Lambda de búsqueda por título
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
        // Lambda de ordenamiento mayor a menor
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

        // Lambda de filtro premium
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

    void menuPrincipal() {
        int opcion;
        while (1) {
            cout << "\n  ========================================" << endl;
            cout << "     MODULO 2 - EMBUDO DE VENTAS         " << endl;
            cout << "  ========================================" << endl;
            cout << "  --- Clientes Potenciales ---" << endl;
            cout << "  1. Registrar Cliente Potencial" << endl;
            cout << "  2. Atender siguiente Cliente (Cola)" << endl;
            cout << "  --- Oportunidades ---" << endl;
            cout << "  3. Crear Oportunidad Comercial" << endl;
            cout << "  4. Ver Embudo de Ventas" << endl;
            cout << "  5. Buscar Oportunidad" << endl;
            cout << "  6. Ordenar Oportunidades por Valor" << endl;
            cout << "  --- Productos ---" << endl;
            cout << "  7. Agregar Producto" << endl;
            cout << "  8. Ver Productos Premium" << endl;
            cout << "  --- Cotizaciones y Contratos ---" << endl;
            cout << "  9. Generar Cotizacion" << endl;
            cout << "  10. Cerrar Contrato" << endl;
            cout << "  0. Volver al menu principal" << endl;
            cout << "  ========================================" << endl;
            cout << "  Opcion: "; cin >> opcion;

            switch (opcion) {
            case 1:  registrarCliente();            break;
            case 2:  atenderSiguienteCliente();     break;
            case 3:  crearOportunidad();            break;
            case 4:  mostrarEmbudo();               break;
            case 5:  buscarOportunidad();           break;
            case 6:  ordenarOportunidadesPorValor(); break;
            case 7:  agregarProducto();             break;
            case 8:  mostrarProductosPremium();     break;
            case 9:  generarCotizacion();           break;
            case 10: cerrarContrato();              break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
        }
    }
};