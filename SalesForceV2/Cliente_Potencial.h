#pragma once
#include <iostream>
#include <string>
using namespace std;
class Cliente_Potencial
{
public:
	string nombre;;
	string correo;
	string interes;

	Cliente_Potencial(string n = "", string c = "", string i = "") : nombre(n), correo(c), interes(i) {}
	void mostrar() {
		cout << "Nombre del posible cliente: " << nombre << ", Correo: " << correo << ", Interes: " << interes << endl;
	}
};

