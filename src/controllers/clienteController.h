#ifndef CLIENTECONTROLLER_H
#define CLIENTECONTROLLER_H

#include "../models/cliente.h"
#include "../views/clienteView.h"

class ClienteController {
public:
    static void mostrarClientes(Cliente* clientes, int cantidad) {
        ClienteView::mostrarClientes(clientes, cantidad);
    }

    static void insertarCliente(Cliente*& clientes, int& cantidad) {
        Cliente::insertarCliente(clientes, cantidad);
        ClienteView::mostrarMensaje("Cliente registrado exitosamente.");
    }

    static void buscarCliente(Cliente* clientes, int cantidad, const string& cedula) {
        int index = Cliente::buscarCliente(clientes, cantidad, cedula);
        if (index != -1) {
            ClienteView::mostrarMensaje("Cliente encontrado:");
            ClienteView::mostrarCliente(clientes[index]);
        } else {
            ClienteView::mostrarMensaje("Cliente no encontrado.");
        }
    }

    static void editarCliente(Cliente* clientes, int cantidad, const string& cedula) {
        Cliente::editarCliente(clientes, cantidad, cedula);
        ClienteView::mostrarMensaje("Cliente editado exitosamente.");
    }

    static void eliminarCliente(Cliente*& clientes, int& cantidad, const string& cedula) {
        Cliente::eliminarCliente(clientes, cantidad, cedula);
        ClienteView::mostrarMensaje("Cliente eliminado exitosamente.");
    }
};

#endif
