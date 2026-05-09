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
        // Aca se añaderá la funcion del mapa con doble for.s
        cout << "  ========================================" << endl;
        cout << "  Bienvenido al Sistema CRM" << endl;
        cout << "  ========================================" << endl;
    }

    void menu() {
        int opcion;
        while (1) {
            cout << "\n  ========================================" << endl;
            cout << "                MENU PRINCIPAL  " << endl;
            cout << "  ========================================" << endl;
            cout << "  1. Gestion de clientes" << endl;
            cout << "  2. Embudo de Ventas" << endl;
            cout << "  3. Operaciones y Soporte" << endl;
            cout << "  0. Salir del sistema" << endl;
            cout << "  ========================================" << endl;
            cout << "  Seleccione una opcion: "; cin >> opcion;
            cin.ignore();
            system("cls");
            switch (opcion) {
            case 1:

                gestorCliente->menu();
                system("cls");
                break;
            case 2:
                gestorVenta->menuPrincipal();
                system("cls");
                break;
            case 3:
                gestorSoporte->menu();
                system("cls");
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