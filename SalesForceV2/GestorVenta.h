#pragma once
#include "iostream"
#include "string"
#include "Cola.h"
#include "ListaDoble.h"
#include "ListaSimple.h"
#include "Cliente_Potencial.h"
#include "GestorArchivos.h"
#include "Oportunidad.h"
#include "Producto.h"
#include "Cotizacion.h"
#include "Contrato.h"
#include "fstream"
#include "iomanip"
#include "random"
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

    // ─────────────────────────────────────────
    //  CLIENTES POTENCIALES
    // ─────────────────────────────────────────
    void registrarCliente() {
        Cliente_Potencial c;
        cout << "\n  === NUEVO CLIENTE POTENCIAL ===" << endl;
        c.ingresar(contadorCliente++);
        colaClientes.enqueue(c);
        cout << "  [OK] Cliente registrado en la cola." << endl;
    }

    void atenderSiguienteCliente() {
        if (colaClientes.estaVacia()) {
            cout << "  [!] No hay clientes pendientes." << endl;
            return;
        }
        cout << "\n  === ATENDIENDO CLIENTE ===" << endl;
        colaClientes.getFrente().mostrar();
        colaClientes.dequeue();
    }

    // ─────────────────────────────────────────
    //  OPORTUNIDADES
    // ─────────────────────────────────────────
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

    // ─────────────────────────────────────────
    //  PRODUCTOS
    // ─────────────────────────────────────────
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
        cout << "\n  === PRODUCTOS PREMIUM (Mayor a S/." << precioMinimo << ") ===" << endl;
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

    // ─────────────────────────────────────────
    //  COTIZACIONES Y CONTRATOS
    // ─────────────────────────────────────────
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

    // ─────────────────────────────────────────
    //  RECURSIVIDAD
    // ─────────────────────────────────────────
    double sumarOportunidadesRec(NodoD<Oportunidad>* nodo) {
        if (nodo == nullptr) return 0.0;
        return nodo->dato.getValorEsperado() +
            sumarOportunidadesRec(nodo->siguiente);
    }

    void mostrarValorTotalOportunidades() {
        double total = sumarOportunidadesRec(listaOportunidades.getCabeza());
        cout << "\n  Valor total en oportunidades: S/." << total << endl;
    }

    // ─────────────────────────────────────────
    //  DATASET + BURBUJA OPTIMIZADA
    // ─────────────────────────────────────────
    void generarDataSet() {
        ofstream archivo("dataset_precios.txt");
        if (!archivo.is_open()) {
            cout << "  [!] No se pudo crear el archivo." << endl;
            return;
        }
        // Semilla fija para reproducibilidad

        mt19937 rng(42);
        uniform_real_distribution<double> dist(10.0, 9999.0);

        for (int i = 0; i < 1000; i++) {
            archivo << fixed << setprecision(2) << dist(rng) << "\n";
        }
        archivo.close();
        cout << "  [OK] Archivo 'dataset_precios.txt' generado con 1000 registros." << endl;
    }

    void verDataSetDesordenado() {
        ifstream archivo("dataset_precios.txt");
        if (!archivo.is_open()) {
            cout << "  [!] No se pudo abrir dataset_precios.txt" << endl;
            return;
        }
        ListaSimple<double>* lista = new ListaSimple<double>();
        double numero;
        while (archivo >> numero) {
            lista->insertar(numero);
        }
        archivo.close();

        cout << "\n  === DATASET DESORDENADO ===" << endl;
        NodoS<double>* actual = lista->getCabeza();
        int i = 1;
        while (actual != nullptr) {
            cout << "  [" << i++ << "] S/." << actual->dato << endl;
            actual = actual->siguiente;
        }
        cout << "  Total: " << lista->getTamanio() << " registros." << endl;
        delete lista;
    }

    void verDataSetOrdenado() {
        ifstream archivo("dataset_precios.txt");
        if (!archivo.is_open()) {
            cout << "  [!] No se pudo abrir dataset_precios.txt" << endl;
            return;
        }
        ListaSimple<double>* lista = new ListaSimple<double>();
        double numero;
        while (archivo >> numero) {
            lista->insertar(numero);
        }
        archivo.close();

        // Burbuja optimizada con lambda
        auto comparar = [](double a, double b) {
            return a > b;
            };
        lista->ordenarBurbujaOptimizada(comparar);

        cout << "\n  === DATASET ORDENADO (menor a mayor) ===" << endl;
        NodoS<double>* actual = lista->getCabeza();
        int i = 1;
        while (actual != nullptr) {
            cout << "  [" << i++ << "] S/." << actual->dato << endl;
            actual = actual->siguiente;
        }
        cout << "  Total: " << lista->getTamanio() << " registros." << endl;
        delete lista;
    }

    // ─────────────────────────────────────────
    //  ARCHIVOS - PRODUCTOS
    // ─────────────────────────────────────────
    void guardarProductos() {
        ListaSimple<string>* lineas = new ListaSimple<string>();
        NodoS<Producto>* actual = catalogoProductos.getCabeza();
        while (actual != nullptr) {
            Producto p = actual->dato;
            string linea = to_string(p.getId()) + "," +
                p.getNombre() + "," +
                to_string(p.getPrecio()) + "," +
                p.getCategoria();
            lineas->insertar(linea);
            actual = actual->siguiente;
        }
        GestorArchivos gestor;
        gestor.guardarLineas("productos.txt", lineas);
        cout << "  [OK] Productos guardados en productos.txt" << endl;
    }

    void cargarProductos() {
        GestorArchivos gestor;
        ListaSimple<string>* lineas = gestor.cargarLineas("productos.txt");
        NodoS<string>* actual = lineas->getCabeza();
        while (actual != nullptr) {
            string linea = actual->dato;
            int p1 = linea.find(',');
            int p2 = linea.find(',', p1 + 1);
            int p3 = linea.find(',', p2 + 1);

            Producto p;
            p.setId(stoi(linea.substr(0, p1)));
            p.setNombre(linea.substr(p1 + 1, p2 - p1 - 1));
            p.setPrecio(stod(linea.substr(p2 + 1, p3 - p2 - 1)));
            p.setCategoria(linea.substr(p3 + 1));
            catalogoProductos.insertar(p);
            contadorProducto++;
            actual = actual->siguiente;
        }
        cout << "  [OK] Productos cargados desde productos.txt" << endl;
    }

    // ─────────────────────────────────────────
    //  SUBMENUS
    // ─────────────────────────────────────────
    void subMenuClientes() {
        int opcion;
        while (1) {
            system("cls");
            cout << "\n  ========================================" << endl;
            cout << "         Clientes Potenciales            " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Registrar cliente potencial" << endl;
            cout << "  2. Atender siguiente cliente (Cola)" << endl;
            cout << "  0. Volver al Embudo de Ventas" << endl;
            cout << "  ========================================" << endl;
            cout << "  Seleccione una opcion: "; cin >> opcion;
            cin.ignore();
            system("cls");
            switch (opcion) {
            case 1:  registrarCliente();          break;
            case 2:  atenderSiguienteCliente();   break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
            system("pause");
        }
    }

    void subMenuOportunidades() {
        int opcion;
        while (1) {
            system("cls");
            cout << "\n  ========================================" << endl;
            cout << "           Oportunidades Comerciales     " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Crear oportunidad comercial" << endl;
            cout << "  2. Ver embudo de ventas" << endl;
            cout << "  3. Buscar oportunidad" << endl;
            cout << "  4. Ordenar oportunidades por valor" << endl;
            cout << "  5. Ver valor total (Recursivo)" << endl;
            cout << "  0. Volver al Embudo de Ventas" << endl;
            cout << "  ========================================" << endl;
            cout << "  Seleccione una opcion: "; cin >> opcion;
            cin.ignore();
            system("cls");
            switch (opcion) {
            case 1:  crearOportunidad();                   break;
            case 2:  mostrarEmbudo();                      break;
            case 3:  buscarOportunidad();                  break;
            case 4:  ordenarOportunidadesPorValor();       break;
            case 5:  mostrarValorTotalOportunidades();     break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
            system("pause");
        }
    }

    void subMenuProductos() {
        int opcion;
        while (1) {
            system("cls");
            cout << "\n  ========================================" << endl;
            cout << "           Catalogo de Productos         " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Agregar producto" << endl;
            cout << "  2. Ver productos premium" << endl;
            cout << "  0. Volver al Embudo de Ventas" << endl;
            cout << "  ========================================" << endl;
            cout << "  Seleccione una opcion: "; cin >> opcion;
            cin.ignore();
            system("cls");
            switch (opcion) {
            case 1:  agregarProducto();          break;
            case 2:  mostrarProductosPremium();  break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
            system("pause");
        }
    }

    void subMenuCotizacionesContratos() {
        int opcion;
        while (1) {
            system("cls");
            cout << "\n  ========================================" << endl;
            cout << "        Cotizaciones y Contratos         " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Generar cotizacion" << endl;
            cout << "  2. Cerrar contrato" << endl;
            cout << "  0. Volver al Embudo de Ventas" << endl;
            cout << "  ========================================" << endl;
            cout << "  Seleccione una opcion: "; cin >> opcion;
            cin.ignore();
            system("cls");
            switch (opcion) {
            case 1:  generarCotizacion();  break;
            case 2:  cerrarContrato();     break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
            system("pause");
        }
    }

    void subMenuDataset() {
        int opcion;
        while (1) {
            system("cls");
            cout << "\n  ========================================" << endl;
            cout << "         Dataset y Ordenamiento          " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Generar dataset de precios" << endl;
            cout << "  2. Ver dataset desordenado" << endl;
            cout << "  3. Ver dataset ordenado (Burbuja Opt.)" << endl;
            cout << "  0. Volver al Embudo de Ventas" << endl;
            cout << "  ========================================" << endl;
            cout << "  Seleccione una opcion: "; cin >> opcion;
            cin.ignore();
            system("cls");
            switch (opcion) {
            case 1:  generarDataSet();          break;
            case 2:  verDataSetDesordenado();   break;
            case 3:  verDataSetOrdenado();      break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
            system("pause");
        }
    }

    void subMenuArchivos() {
        int opcion;
        while (1) {
            system("cls");
            cout << "\n  ========================================" << endl;
            cout << "                  Archivos                  " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Guardar productos" << endl;
            cout << "  2. Cargar productos" << endl;
            cout << "  0. Volver al Embudo de Ventas" << endl;
            cout << "  ========================================" << endl;
            cout << "  Seleccione una opcion: "; cin >> opcion;
            cin.ignore();
            system("cls");
            switch (opcion) {
            case 1:  guardarProductos();  break;
            case 2:  cargarProductos();   break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
            system("pause");
        }
    }

    // ─────────────────────────────────────────
    //  MENU PRINCIPAL
    // ─────────────────────────────────────────
    void menuPrincipal() {
        int opcion;
        while (1) {
            system("cls");
            cout << "\n  ========================================" << endl;
            cout << "             EMBUDO DE VENTAS       " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Clientes potenciales" << endl;
            cout << "  2. Oportunidades comerciales" << endl;
            cout << "  3. Catalogo de productos" << endl;
            cout << "  4. Cotizaciones y contratos" << endl;
            cout << "  5. Dataset y ordenamiento" << endl;
            cout << "  6. Productos" << endl;
            cout << "  0. Volver al menu principal" << endl;
            cout << "  ========================================" << endl;
            cout << "  Seleccione una opcion: "; cin >> opcion;
            cin.ignore();
            system("cls");
            switch (opcion) {
            case 1:  subMenuClientes();               break;
            case 2:  subMenuOportunidades();          break;
            case 3:  subMenuProductos();              break;
            case 4:  subMenuCotizacionesContratos();  break;
            case 5:  subMenuDataset();                break;
            case 6:  subMenuArchivos();               break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
        }
    }
};