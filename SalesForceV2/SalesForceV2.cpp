#include "pch.h"
#include "iostream"
#include "SistemaCRM.h"
using namespace std;
using namespace System;

int main() {
    Console::SetWindowSize(80, 31);

    SistemaCRM* crm;
    crm = new SistemaCRM();

    crm->mostrarBienvenida();
    crm->menu();

    system("pause>0");
    return 0;
}