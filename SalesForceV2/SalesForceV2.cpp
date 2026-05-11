#include "pch.h"
#include "iostream"
#include "SistemaCRM.h"
using namespace std;
using namespace System;

int main() {

    SistemaCRM* crm;
    crm = new SistemaCRM();

    crm->mostrarBienvenida();
    crm->menu();

    system("pause>0");
    return 0;
}