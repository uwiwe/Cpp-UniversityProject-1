#ifndef VEHICULOCONTROLLER_H
#define VEHICULOCONTROLLER_H

#include "../models/Vehiculo.h"
#include "../views/VehiculoView.h"
using namespace std;

class VehiculoController {
public:
    // Mostrar todos los vehiculos
    static void mostrarVehiculos(Vehiculo* vehiculos, int cantidad) {
        VehiculoView::mostrarVehiculos(vehiculos, cantidad);
    }

    // Insertar un vehiculo
    static void insertarVehiculo(Vehiculo*& vehiculos, int& cantidad) {
        Vehiculo::insertarVehiculo(vehiculos, cantidad);
        VehiculoView::mostrarMensaje("Vehiculo agregado exitosamente.");
    }

    // Buscar un vehiculo por placa
    static void buscarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa) {
        int index = Vehiculo::buscarVehiculo(vehiculos, cantidad, placa);
        if (index != -1) {
            VehiculoView::mostrarMensaje("Vehiculo encontrado:");
            VehiculoView::mostrarVehiculo(vehiculos[index]);
        } else {
            VehiculoView::mostrarMensaje("Vehiculo no encontrado.");
        }
    }

    // Editar un vehiculo por placa
    static void editarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa) {
        Vehiculo::editarVehiculo(vehiculos, cantidad, placa);
        VehiculoView::mostrarMensaje("Vehiculo editado exitosamente.");
    }

    // Eliminar un vehiculo por placa
    static void eliminarVehiculo(Vehiculo*& vehiculos, int& cantidad, const string& placa) {
        Vehiculo::eliminarVehiculo(vehiculos, cantidad, placa);
        VehiculoView::mostrarMensaje("Vehiculo eliminado exitosamente.");
    }
};

#endif
