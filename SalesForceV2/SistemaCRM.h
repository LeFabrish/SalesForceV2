#pragma once
#include "iostream"
#include "string"
#include "GestorCliente.h"
#include "GestorVenta.h"
#include "GestorSoporte.h"
using namespace std;

class SistemaCRM {
private:
    GestorCliente* gestorCliente;
    GestorVenta* gestorVenta;
    GestorSoporte* gestorSoporte;

public:
    SistemaCRM() {
        gestorCliente = new GestorCliente();
        gestorVenta = new GestorVenta();
        gestorSoporte = new GestorSoporte();
    }

    void mostrarBienvenida() {
        cout << "\n";
        cout << "  ========================================" << endl;
        cout << "  ||                                    ||" << endl;
        cout << "  ||        SALESFORCE CRM v1.0         ||" << endl;
        cout << "  ||    Gestion Global de Clientes      ||" << endl;
        cout << "  ||                                    ||" << endl;
        cout << "  ========================================" << endl;
        cout << "  Bienvenido al Sistema CRM" << endl;
        cout << "  ========================================" << endl;
    }

    void menu() {
        int opcion;
        while (1) {
            cout << "\n  ========================================" << endl;
            cout << "         SALESFORCE CRM - MENU PRINCIPAL  " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Modulo 1 - Gestion de Identidad" << endl;
            cout << "  2. Modulo 2 - Embudo de Ventas" << endl;
            cout << "  3. Modulo 3 - Operaciones y Soporte" << endl;
            cout << "  0. Salir del sistema" << endl;
            cout << "  ========================================" << endl;
            cout << "  Opcion: "; cin >> opcion;
            cin.ignore();

            switch (opcion) {
            case 1:
                gestorCliente->menu();
                break;
            case 2:
                gestorVenta->menuPrincipal();
                break;
            case 3:
                gestorSoporte->menu();
                break;
            case 0:
                cout << "\n  Cerrando SalesForce CRM..." << endl;
                cout << "  Hasta luego." << endl;
                return;
            default:
                cout << "  [!] Opcion invalida." << endl;
            }
        }
    }
};