#ifndef REPUESTOCONTROLLER_H
#define REPUESTOCONTROLLER_H

#include "../models/repuesto.h"
#include "../views/repuestoView.h"

class RepuestoController {
public:
    static void mostrarRepuestos(Repuesto* repuestos, int cantidad) {
        RepuestoView::mostrarRepuestos(repuestos, cantidad);
    }

    static void insertarRepuesto(Repuesto*& repuestos, int& cantidad) {
        Repuesto::insertarRepuesto(repuestos, cantidad);
        RepuestoView::mostrarMensaje("Repuesto agregado exitosamente.");
    }

    static void buscarRepuesto(Repuesto* repuestos, int cantidad, int id) {
        int index = Repuesto::buscarRepuesto(repuestos, cantidad, id);
        if (index != -1) {
            RepuestoView::mostrarMensaje("Repuesto encontrado:");
            RepuestoView::mostrarRepuesto(repuestos[index]);
        } else {
            RepuestoView::mostrarMensaje("Repuesto no encontrado.");
        }
    }

    static void editarRepuesto(Repuesto* repuestos, int cantidad, int id) {
        Repuesto::editarRepuesto(repuestos, cantidad, id);
        RepuestoView::mostrarMensaje("Repuesto editado exitosamente.");
    }

    static void eliminarRepuesto(Repuesto*& repuestos, int& cantidad, int id) {
        Repuesto::eliminarRepuesto(repuestos, cantidad, id);
        RepuestoView::mostrarMensaje("Repuesto eliminado exitosamente.");
    }
};

#endif
