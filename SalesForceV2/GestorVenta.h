#pragma once
#include <iostream>
#include <string>
#include "Cola.h"
#include "ListaDoble.h"
#include "ListaSimple.h"
#include "Cliente_Potencial.h"
#include "Oportunidad.h"
#include "Producto.h"
#include "Cotizacion.h"
#include "Contrato.h"
class GestorVenta
{
private:
    Cola<Cliente_Potencial> colaClientes;
    ListaDoble<Oportunidad> listaOportunidades;
    ListaSimple<Producto> catalogoProductos;
    ListaSimple<Cotizacion> listaCotizaciones;
    ListaSimple<Contrato> listaContratos;
public:
    GestorVenta() {
      
	}

    void registrarClientes(string nombre, string correo, string interes) {
        colaClientes.enqueue(Cliente_Potencial(nombre, correo, interes));
        cout << "[+] Cliente registrado en la fila de atencion.\n";
    }

    void atenderSiguienteCliente() {
        if (colaClientes.estaVacia()) {
            cout << "[-] No hay clientes pendientes en la cola.\n";
            return;
        }
        cout << "\n>>> Atendiendo al siguiente prospecto:\n";
        colaClientes.getFrente().mostrar();
        colaClientes.dequeue();
    }

    void crearOportunidad(string titulo, double valor, string fase = "Prospeccion") {
        listaOportunidades.insertar(Oportunidad(titulo, valor, fase));
        cout << "[+] Nueva oportunidad comercial creada.\n";
    }

    void mostrarEmbudo() {
        cout << endl<<"--- EMBUDO DE VENTAS (Oportunidades) ---"<<endl;
        listaOportunidades.mostrar();
    }


    void buscarOportunidadPorTitulo(string tituloBuscado) {
        auto criterioBusqueda = [tituloBuscado](Oportunidad op) {
            return op.titulo == tituloBuscado;
            };

        auto nodoEncontrado = listaOportunidades.buscar(criterioBusqueda);
        if (nodoEncontrado) {
            cout << endl<<"[!] Oportunidad Encontrada:"<<endl;
            nodoEncontrado->dato.mostrar();
        }
        else {
            cout << endl<<"[-] Oportunidad '" << tituloBuscado << "' no encontrada."<<endl;
        }
    }


    void ordenarOportunidadesPorValor() {
       
        auto comparadorMayorMenor = [](Oportunidad a, Oportunidad b) {
            return a.valorEsperado < b.valorEsperado;
            };

        listaOportunidades.ordenar(comparadorMayorMenor);
        cout << "[+] Oportunidades ordenadas por valor esperado."<<endl;
    }



    void agregarProducto(int id, string nombre, double precio) {
        catalogoProductos.insertar(Producto(id, nombre, precio));
        cout << "[+] Producto '" << nombre << "' agregado al catalogo."<<endl;
    }

    void generarCotizacion(int num, double total, string fecha) {
        listaCotizaciones.insertar(Cotizacion(num, total, fecha));
        cout << "[+] Cotizacion #" << num << " generada."<<endl;
    }

    void cerrarContrato(int id, string fecha, string terminos) {
        listaContratos.insertar(Contrato(id, fecha, terminos));
        cout << "[+] Contrato ID " << id << " firmado y cerrado con exito."<<endl;
    }

    void mostrarProductosPremium(double precioMinimo) {
        cout << "\n--- PRODUCTOS PREMIUM (Mayor a S/. " << precioMinimo << ") ---"<<endl;
        auto actual = catalogoProductos.getCabeza();

      
        auto esPremium = [precioMinimo](Producto p) {
            return p.precio >= precioMinimo;
            };

        bool hayPremium = false;
        while (actual != nullptr) {
            if (esPremium(actual->dato)) {
                actual->dato.mostrar();
                hayPremium = true;
            }
            actual = actual->siguiente;
        }
        if (!hayPremium) cout << "No hay productos que superen ese precio."<<endl;
    }
    void menuPrincipal() {
        int opcion;
        string respuesta1, respuesta2, respuesta3;
        double respuestaD;
        int respuestaI;

        do {
    
            cout << "==========================================\n";
            cout << "       SALESFORCE - MODULO 2 (VENTAS)     \n";
            cout << "==========================================\n";
            cout << " 1. Registrar nuevo Cliente\n";
            cout << " 2. Atender siguiente Cliente (Cola)\n";
            cout << " 3. Crear Oportunidad Comercial\n";
            cout << " 4. Ver Embudo de Ventas\n";
            cout << " 5. Buscar Oportunidad\n";
            cout << " 6. Ordenar Oportunidades por Valor\n";
            cout << " 7. Agregar Producto\n";
            cout << " 8. Ver Productos Premium\n";
            cout << " 9. Generar Cotizacion\n";
            cout << " 10. Cerrar Contrato\n";
            cout << " 0. Salir\n";
            cout << "==========================================\n";
            cout << "Seleccione una opcion: ";

            cin >> opcion;
            cin.ignore(); 

            cout << "\n";
            switch (opcion) {
            case 1:
                cout << "Nombre del cliente: "; getline(cin, respuesta1);
                cout << "Correo: "; getline(cin, respuesta2);
                cout << "Interes: "; getline(cin, respuesta3);
                registrarClientes(respuesta1, respuesta2, respuesta3);
                break;
            case 2:
                atenderSiguienteCliente();
                break;
            case 3:
                cout << "Titulo del trato: "; getline(cin, respuesta1);
                cout << "Valor esperado (S/.): "; cin >> respuestaD; cin.ignore();
                cout << "Fase: "; getline(cin, respuesta2);
                crearOportunidad(respuesta1, respuestaD, respuesta2);
                break;
            case 4:
                mostrarEmbudo();
                break;
            case 5:
                cout << "Ingrese el titulo exacto a buscar: "; getline(cin, respuesta1);
                buscarOportunidadPorTitulo(respuesta1);
                break;
            case 6:
                ordenarOportunidadesPorValor();
                break;
            case 7:
                cout << "ID del Producto: "; cin >> respuestaI; cin.ignore();
                cout << "Nombre del Producto: "; getline(cin, respuesta1);
                cout << "Precio (S/.): "; cin >> respuestaD; cin.ignore();
                agregarProducto(respuestaI, respuesta1, respuestaD);
                break;
            case 8:
                cout << "Ingrese el precio minimo para filtrar: S/."; cin >> respuestaD; cin.ignore();
                mostrarProductosPremium(respuestaD);
                break;
            case 9:
                cout << "Numero de Cotizacion: "; cin >> respuestaI; cin.ignore();
                cout << "Total (S/.): "; cin >> respuestaD; cin.ignore();
                cout << "Fecha de Vencimiento: "; getline(cin, respuesta1);
                generarCotizacion(respuestaI, respuestaD, respuesta1);
                break;
            case 10:
                cout << "ID del Contrato: "; cin >> respuestaI; cin.ignore();
                cout << "Fecha de Firma: "; getline(cin, respuesta1);
                cout << "Terminos: "; getline(cin, respuesta2);
                cerrarContrato(respuestaI, respuesta1, respuesta2);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
            }
           

        } while (opcion != 0);
    }
};

