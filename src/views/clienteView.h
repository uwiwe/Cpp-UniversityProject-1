#ifndef CLIENTEVIEW_H
#define CLIENTEVIEW_H

#include "../models/cliente.h"
#include <iostream>
using namespace std;

class ClienteView {
public:
    // Mostrar un cliente
    static void mostrarCliente(const Cliente& cliente) {
        cout << "Cedula: " << cliente.getCedula() << endl;
        cout << "Nombre: " << cliente.getNombre() << endl;
        cout << "Apellido: " << cliente.getApellido() << endl;
        cout << "Email: " << cliente.getEmail() << endl;
        cout << "Cantidad de Vehiculos Rentados: " << cliente.getCantidadVehiculosRentados() << endl;
        cout << "Dirección: " << cliente.getDireccion() << endl;
        cout << "Activo: " << (cliente.isActivo() ? "Si" : "No") << endl;
    }

    // Mostrar lista de clientes
    static void mostrarClientes(Cliente* clientes, int cantidad) {
        for (int i = 0; i < cantidad; ++i) {
            cout << "Cliente " << i + 1 << ":" << endl;
            mostrarCliente(clientes[i]);
            cout << "---------------------" << endl;
        }
    }

    // Mostrar mensaje
    static void mostrarMensaje(const string& mensaje) {
        cout << mensaje << endl;
    }
};

#endif
