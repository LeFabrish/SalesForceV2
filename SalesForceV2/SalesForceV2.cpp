#include "pch.h"
#include <iostream>
#include "GestorCliente.h"
#include "GestorVenta.h"
#include "GestorSoporte.h"

using namespace System;
using namespace std;

int main(cli::array<System::String^>^ args)
{
    GestorCliente gestorCliente;
    GestorVenta gestorVenta;
    GestorSoporte gestorSoporte;

    int opcion;

    while (true) {
        cout << "\n  ========================================" << endl;
        cout << "          SISTEMA CRM GLOBAL (V2)         " << endl;
        cout << "  ========================================" << endl;
        cout << "  1. Modulo de Gestion de Clientes" << endl;
        cout << "  2. Modulo de Embudo de Ventas" << endl;
        cout << "  3. Modulo de Gestion de Soporte" << endl;
        cout << "  0. Salir del Sistema" << endl;
        cout << "  ========================================" << endl;
        cout << "  Seleccione un modulo: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            gestorCliente.menu();
            break;
        case 2:
            gestorVenta.menuPrincipal();
            break;
        case 3:
            gestorSoporte.menuSoporte();
            break;
        case 0:
            cout << "\n  [OK] Guardando datos y cerrando el sistema CRM..." << endl;
            return 0;
        default:
            cout << "  [!] Opcion invalida. Intente nuevamente." << endl;
        }
    }
    return 0;
}