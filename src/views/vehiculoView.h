#ifndef VEHICULOVIEW_H
#define VEHICULOVIEW_H

#include "../models/vehiculo.h"
#include <iostream>
using namespace std;

class VehiculoView {
public:
    // Mostrar un vehiculo
    static void mostrarVehiculo(const Vehiculo& vehiculo) {
        cout << "Modelo: " << vehiculo.getModelo() << endl;
        cout << "Marca: " << vehiculo.getMarca() << endl;
        cout << "Placa: " << vehiculo.getPlaca() << endl;
        cout << "Color: " << vehiculo.getColor() << endl;
        cout << "Ano: " << vehiculo.getAno() << endl;
        cout << "Kilometraje: " << vehiculo.getKilometraje() << endl;
        cout << "Rentado: " << (vehiculo.isRentado() ? "Si" : "No") << endl;
        cout << "Motor: " << vehiculo.getMotor() << endl;
        cout << "Precio de Renta: " << vehiculo.getPrecioRenta() << endl;
        cout << "Cedula Cliente: " << vehiculo.getCedCliente() << endl;
        cout << "Fecha de Entrega: " << vehiculo.getFechaDeEntrega() << endl;
    }

    // Mostrar una lista de vehiculos
    static void mostrarVehiculos(Vehiculo* vehiculos, int cantidad) {
        for (int i = 0; i < cantidad; i++) {
            cout << "Vehiculo " << i + 1 << ":" << endl;
            mostrarVehiculo(vehiculos[i]);
            cout << "---------------------" << endl;
        }
    }

    // Mostrar un mensaje
    static void mostrarMensaje(const string& mensaje) {
        cout << mensaje << endl;
    }
};

#endif
