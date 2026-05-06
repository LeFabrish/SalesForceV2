// Archivo: Cuenta.h
#pragma once
#include "Direccion.h"
#include <iostream>
#include <string>

using namespace std;

class Cuenta
{
private:
    int idCuenta;
    string nombreEmpresa;
    string ruc;
    string sectorIndustria;
    Direccion* direccion;

public:
    Cuenta() {
        this->idCuenta = 0;
        this->nombreEmpresa = "";
        this->ruc = "";
        this->sectorIndustria = "";
        this->direccion = nullptr;
    }

    Cuenta(int idCuenta, string nombreEmpresa, string ruc, string sectorIndustria, Direccion* direccion) {
        this->idCuenta = idCuenta;
        this->nombreEmpresa = nombreEmpresa;
        this->ruc = ruc;
        this->sectorIndustria = sectorIndustria;
        this->direccion = direccion;
    }

    ~Cuenta() {
        // Uso de composicino ya que si se destruye la cuenta, tambien la direccion
        if (direccion != nullptr) {
            delete direccion;
        }
    }

    int getIdCuenta() { return idCuenta; } 
    string getNombreEmpresa() { return nombreEmpresa; }
    string getRuc() { return ruc; }
    string getSectorIndustria() { return sectorIndustria; }
    Direccion* getDireccion() { return direccion; }

    void setIdCuenta(int idCuenta) { this->idCuenta = idCuenta; }
    void setNombreEmpresa(string nombreEmpresa) { this->nombreEmpresa = nombreEmpresa; }
    void setRuc(string ruc) { this->ruc = ruc; }
    void setSectorIndustria(string sectorIndustria) { this->sectorIndustria = sectorIndustria; }
    void setDireccion(Direccion* direccion) { this->direccion = direccion; }
};