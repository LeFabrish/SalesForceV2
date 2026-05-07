#pragma once
#include "iostream"
#include "string"
#include "ListaDoble.h"
#include "GestorArchivos.h"
#include "Cuenta.h"
#include "Contacto.h"
#include "UsuarioCRM.h"
#include "Interaccion.h"
using namespace std;

class GestorCliente {
private:
    ListaDoble<Cuenta>* cuentas;
    ListaDoble<Contacto>* contactos;
    ListaDoble<UsuarioCRM>* usuarios;
    ListaDoble<Interaccion>* interacciones;
    GestorArchivos* gestor;
    int contadorCuenta;
    int contadorContacto;
    int contadorUsuario;
    int contadorInteraccion;

public:
    GestorCliente() {
        cuentas = new ListaDoble<Cuenta>();
        contactos = new ListaDoble<Contacto>();
        usuarios = new ListaDoble<UsuarioCRM>();
        interacciones = new ListaDoble<Interaccion>();
        gestor = new GestorArchivos();
        contadorCuenta = 1;
        contadorContacto = 1;
        contadorUsuario = 1;
        contadorInteraccion = 1;
    }

    // ------------------------------------------
    //  CUENTAS
    // ------------------------------------------
    void agregarCuenta() {
        Cuenta c;
        cout << "\n  === NUEVA CUENTA ===" << endl;
        c.ingresar(contadorCuenta++);
        cuentas->insertar(c);
        cout << "  [OK] Cuenta registrada." << endl;
    }

    void listarCuentas() {
        cout << "\n  === LISTA DE CUENTAS ===" << endl;
        if (cuentas->estaVacia()) {
            cout << "  No hay cuentas registradas." << endl;
            return;
        }
        cuentas->mostrar();
    }

    void buscarCuenta() {
        string nombre;
        cout << "\n  Nombre a buscar: "; cin >> nombre;

        // Lambda de búsqueda
        auto criterio = [nombre](Cuenta c) {
            return c.getNombre() == nombre;
            };

        NodoD<Cuenta>* resultado = cuentas->buscar(criterio);
        if (resultado != nullptr) {
            cout << "\n  [Encontrado]" << endl;
            resultado->dato.mostrar();
        }
        else {
            cout << "  [!] Cuenta no encontrada." << endl;
        }
    }

    void ordenarCuentasPorNombre() {
        // Lambda de ordenamiento
        auto comparar = [](Cuenta a, Cuenta b) {
            return a.getNombre() > b.getNombre();
            };
        cuentas->ordenar(comparar);
        cout << "  [OK] Cuentas ordenadas por nombre." << endl;
    }

    void eliminarCuenta() {
        int pos;
        cout << "\n  Posicion a eliminar: "; cin >> pos;
        cuentas->eliminar(pos);
        cout << "  [OK] Cuenta eliminada." << endl;
    }

    // ------------------------------------------
    //  CONTACTOS
    // ------------------------------------------
    void agregarContacto() {
        Contacto c;
        cout << "\n  === NUEVO CONTACTO ===" << endl;
        c.ingresar(contadorContacto++);
        contactos->insertar(c);
        cout << "  [OK] Contacto registrado." << endl;
    }

    void listarContactos() {
        cout << "\n  === LISTA DE CONTACTOS ===" << endl;
        if (contactos->estaVacia()) {
            cout << "  No hay contactos registrados." << endl;
            return;
        }
        contactos->mostrar();
    }

    void buscarContacto() {
        string nombre;
        cout << "\n  Nombre a buscar: "; cin >> nombre;

        // Lambda de búsqueda
        auto criterio = [nombre](Contacto c) {
            return c.getNombre() == nombre;
            };

        NodoD<Contacto>* resultado = contactos->buscar(criterio);
        if (resultado != nullptr) {
            cout << "\n  [Encontrado]" << endl;
            resultado->dato.mostrar();
        }
        else {
            cout << "  [!] Contacto no encontrado." << endl;
        }
    }

    void ordenarContactosPorApellido() {
        // Lambda de ordenamiento
        auto comparar = [](Contacto a, Contacto b) {
            return a.getApellido() > b.getApellido();
            };
        contactos->ordenar(comparar);
        cout << "  [OK] Contactos ordenados por apellido." << endl;
    }

    // ------------------------------------------
    //  USUARIOS CRM
    // ------------------------------------------
    void agregarUsuario() {
        UsuarioCRM u;
        cout << "\n  === NUEVO USUARIO CRM ===" << endl;
        u.ingresar(contadorUsuario++);
        usuarios->insertar(u);
        cout << "  [OK] Usuario registrado." << endl;
    }

    void listarUsuarios() {
        cout << "\n  === LISTA DE USUARIOS ===" << endl;
        if (usuarios->estaVacia()) {
            cout << "  No hay usuarios registrados." << endl;
            return;
        }
        usuarios->mostrar();
    }

    void buscarUsuarioPorRol() {
        string rol;
        cout << "\n  Rol a buscar (Vendedor/Soporte/Admin): "; cin >> rol;

        // Lambda de búsqueda por rol
        auto criterio = [rol](UsuarioCRM u) {
            return u.getRol() == rol;
            };

        NodoD<UsuarioCRM>* resultado = usuarios->buscar(criterio);
        if (resultado != nullptr) {
            cout << "\n  [Encontrado]" << endl;
            resultado->dato.mostrar();
        }
        else {
            cout << "  [!] Usuario no encontrado." << endl;
        }
    }

    // ------------------------------------------
    //  INTERACCIONES
    // ------------------------------------------
    void agregarInteraccion() {
        Interaccion i;
        cout << "\n  === NUEVA INTERACCION ===" << endl;
        i.ingresar(contadorInteraccion++);
        interacciones->insertar(i);
        cout << "  [OK] Interaccion registrada." << endl;
    }

    void listarInteracciones() {
        cout << "\n  === LISTA DE INTERACCIONES ===" << endl;
        if (interacciones->estaVacia()) {
            cout << "  No hay interacciones registradas." << endl;
            return;
        }
        interacciones->mostrar();
    }

    void listarInteraccionesInverso() {
        cout << "\n  === INTERACCIONES (mas recientes primero) ===" << endl;
        interacciones->mostrarInverso();
    }

    // ------------------------------------------
    //  ARCHIVOS
    // ------------------------------------------
    void guardarCuentas() {
        ListaSimple<string>* lineas = new ListaSimple<string>();
        NodoD<Cuenta>* actual = cuentas->getCabeza();
        while (actual != nullptr) {
            Cuenta c = actual->dato;
            string linea = to_string(c.getId()) + "," +
                c.getNombre() + "," +
                c.getIndustria() + "," +
                c.getTelefono() + "," +
                c.getEmail();
            lineas->insertar(linea);
            actual = actual->siguiente;
        }
        gestor->guardarLineas("cuentas.txt", lineas);
        cout << "  [OK] Cuentas guardadas en cuentas.txt" << endl;
    }

    void cargarCuentas() {
        ListaSimple<string>* lineas = gestor->cargarLineas("cuentas.txt");
        NodoS<string>* actual = lineas->getCabeza();
        while (actual != nullptr) {
            string linea = actual->dato;
            // Parsear: id,nombre,industria,telefono,email
            int p1 = linea.find(',');
            int p2 = linea.find(',', p1 + 1);
            int p3 = linea.find(',', p2 + 1);
            int p4 = linea.find(',', p3 + 1);

            Cuenta c;
            c.setId(stoi(linea.substr(0, p1)));
            c.setNombre(linea.substr(p1 + 1, p2 - p1 - 1));
            c.setIndustria(linea.substr(p2 + 1, p3 - p2 - 1));
            c.setTelefono(linea.substr(p3 + 1, p4 - p3 - 1));
            c.setEmail(linea.substr(p4 + 1));
            cuentas->insertar(c);
            contadorCuenta++;
            actual = actual->siguiente;
        }
        cout << "  [OK] Cuentas cargadas desde cuentas.txt" << endl;
    }

    // ------------------------------------------
    //  MENU MODULO 1
    // ─------------------------------------------
    void menu() {
        int opcion;
        while (1) {
            cout << "\n  ========================================" << endl;
            cout << "       MODULO 1 - GESTION DE CLIENTES   " << endl;
            cout << "  ========================================" << endl;
            cout << "  --- Cuentas ---" << endl;
            cout << "  1. Agregar Cuenta" << endl;
            cout << "  2. Listar Cuentas" << endl;
            cout << "  3. Buscar Cuenta" << endl;
            cout << "  4. Ordenar Cuentas por Nombre" << endl;
            cout << "  5. Eliminar Cuenta" << endl;
            cout << "  6. Guardar Cuentas en archivo" << endl;
            cout << "  7. Cargar Cuentas desde archivo" << endl;
            cout << "  --- Contactos ---" << endl;
            cout << "  8. Agregar Contacto" << endl;
            cout << "  9. Listar Contactos" << endl;
            cout << "  10. Buscar Contacto" << endl;
            cout << "  11. Ordenar Contactos por Apellido" << endl;
            cout << "  --- Usuarios ---" << endl;
            cout << "  12. Agregar Usuario" << endl;
            cout << "  13. Listar Usuarios" << endl;
            cout << "  14. Buscar Usuario por Rol" << endl;
            cout << "  --- Interacciones ---" << endl;
            cout << "  15. Agregar Interaccion" << endl;
            cout << "  16. Listar Interacciones" << endl;
            cout << "  17. Listar Interacciones (recientes)" << endl;
            cout << "  0. Volver al menu principal" << endl;
            cout << "  ========================================" << endl;
            cout << "  Opcion: "; cin >> opcion;

            switch (opcion) {
            case 1:  agregarCuenta();               break;
            case 2:  listarCuentas();               break;
            case 3:  buscarCuenta();                break;
            case 4:  ordenarCuentasPorNombre();     break;
            case 5:  eliminarCuenta();              break;
            case 6:  guardarCuentas();              break;
            case 7:  cargarCuentas();               break;
            case 8:  agregarContacto();             break;
            case 9:  listarContactos();             break;
            case 10: buscarContacto();              break;
            case 11: ordenarContactosPorApellido(); break;
            case 12: agregarUsuario();              break;
            case 13: listarUsuarios();              break;
            case 14: buscarUsuarioPorRol();         break;
            case 15: agregarInteraccion();          break;
            case 16: listarInteracciones();         break;
            case 17: listarInteraccionesInverso();  break;
            case 0:  return;
            default: cout << "  [!] Opcion invalida." << endl;
            }
        }
    }
};