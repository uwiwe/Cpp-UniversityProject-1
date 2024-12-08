#ifndef REPUESTOVIEW_H
#define REPUESTOVIEW_H

#include "../models/repuesto.h"
#include <iostream>
using namespace std;

class RepuestoView {
public:
    static void mostrarRepuesto(const Repuesto& repuesto) {
        cout << "ID: " << repuesto.getId() << endl;
        cout << "Modelo: " << repuesto.getModelo() << endl;
        cout << "Marca: " << repuesto.getMarca() << endl;
        cout << "Nombre: " << repuesto.getNombre() << endl;
        cout << "Modelo del Carro: " << repuesto.getModeloCarro() << endl;
        cout << "Ano del Carro: " << repuesto.getAnoCarro() << endl;
        cout << "Precio: " << repuesto.getPrecio() << endl;
        cout << "Existencias: " << repuesto.getExistencias() << endl;
    }

    static void mostrarRepuestos(Repuesto* repuestos, int cantidad) {
        for (int i = 0; i < cantidad; ++i) {
            cout << "Repuesto " << i + 1 << ":" << endl;
            mostrarRepuesto(repuestos[i]);
            cout << "---------------------" << endl;
        }
    }

    static void mostrarMensaje(const string& mensaje) {
        cout << mensaje << endl;
    }
};

#endif
