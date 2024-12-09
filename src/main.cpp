#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "controllers/vehiculoController.h"
#include "controllers/clienteController.h"
#include "controllers/repuestoController.h"

using namespace std;

void crearBackup(const string& archivoOriginal, const string& carpetaBackup, const string& nombreArchivo) {
    string rutaBackup = carpetaBackup + "/" + nombreArchivo;

    ifstream origen(archivoOriginal, ios::binary);
    if (!origen) {
        cout << "Error al abrir el archivo original: " << archivoOriginal << endl;
        return;
    }

    ofstream destino(rutaBackup, ios::binary);
    if (!destino) {
        cout << "Error al crear el archivo de respaldo: " << rutaBackup << endl;
        return;
    }

    destino << origen.rdbuf();  // Copiar el contenido del archivo original al archivo de backup
    cout << "Copia de seguridad creada: " << rutaBackup << endl;
}

string obtenerNombreBackup(const string& nombreArchivoBase) {
    time_t t = time(0);
    struct tm* now = localtime(&t);

    stringstream nombreBackup;
    nombreBackup << nombreArchivoBase << "_" 
                 << (now->tm_year + 1900) 
                 << (now->tm_mon + 1) 
                 << now->tm_mday << "_"
                 << now->tm_hour 
                 << now->tm_min 
                 << ".csv";

    return nombreBackup.str();
}

void crearCarpetaBackup(const string& carpetaBackup) {
#ifdef _WIN32
    string comando = "mkdir " + carpetaBackup;
#endif
    system(comando.c_str());
}

int main() {
    Vehiculo* vehiculos = NULL;
    Cliente* clientes = NULL;
    Repuesto* repuestos = NULL;

    int vCantidad = 0;
    int vehiculosCantidad = Vehiculo::leerVehiculos("./vehiculos.csv", vehiculos, vCantidad);
    int cCantidad = 0;
    int clientesCantidad = Cliente::leerClientes("./clientes.csv", clientes, cCantidad);
    int rCantidad = 0;
    int repuestosCantidad = Repuesto::leerRepuestos("./repuestos.csv", repuestos, rCantidad);

    bool accesoVehiculos = false;
    bool accesoClientes = false;
    bool accesoRepuestos = false;
    bool puedeConsultar = false;
    bool puedeEditar = false;
    bool puedeEliminar = false;

    cout << "Registrese:" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Manager" << endl;
    cout << "3. Empleado" << endl;
    cout << "Seleccione una opcion: ";
    int rol;
    cin >> rol;

    switch (rol) {
        case 1: // Admin
            accesoVehiculos = true;
            accesoClientes = true;
            accesoRepuestos = true;
            puedeConsultar = true;
            puedeEditar = true;
            puedeEliminar = true;
            break;
        case 2: // Manager
            accesoVehiculos = true;
            accesoClientes = true;
            accesoRepuestos = false;
            puedeConsultar = true;
            puedeEditar = true;
            puedeEliminar = true;
            break;
        case 3: // Empleado
            accesoVehiculos = true;
            accesoClientes = true;
            accesoRepuestos = true;
            puedeConsultar = true;
            puedeEditar = false;
            puedeEliminar = false;
            break;
        default:
            cout << "Rol no valido" << endl;
            return 0;
    }

    bool cambiosRealizados = false;
    int opcion;

    const string carpetaBackup = "backups";
    crearCarpetaBackup(carpetaBackup);

    do {
        cout << "\nMenu de opciones:" << endl;
        if (accesoVehiculos) {
            cout << "1. Ver todos los vehiculos" << endl;
            if (puedeEditar) cout << "2. Insertar vehiculo" << endl;
            if (puedeEditar) cout << "3. Editar vehiculo" << endl;
            if (puedeEliminar) cout << "4. Eliminar vehiculo" << endl;
            cout << "5. Ver un vehiculo especifico" << endl;
        }
        if (accesoClientes) {
            cout << "6. Ver todos los clientes" << endl;
            if (puedeEditar) cout << "7. Insertar cliente" << endl;
            if (puedeEditar) cout << "8. Editar cliente" << endl;
            if (puedeEliminar) cout << "9. Eliminar cliente" << endl;
            cout << "10. Ver un cliente especifico" << endl;
        }
        if (accesoRepuestos) {
            cout << "11. Ver todos los repuestos" << endl;
            if (puedeEditar) cout << "12. Insertar repuesto" << endl;
            if (puedeEditar) cout << "13. Editar repuesto" << endl;
            if (puedeEliminar) cout << "14. Eliminar repuesto" << endl;
            cout << "15. Ver un repuesto especifico" << endl;
        }
        cout << "16. Guardar y salir" << endl;
        cout << "17. Salir sin guardar" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                if (accesoVehiculos) {VehiculoController::mostrarVehiculos(vehiculos, vehiculosCantidad);}
                else {cout << "No tiene permisos para consultar vehiculos." << endl;}
                break;
            case 2:
                if (puedeEditar && accesoVehiculos) {
                    VehiculoController::insertarVehiculo(vehiculos, vehiculosCantidad);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para insertar vehiculos." << endl;}
                break;
            case 3: {
                if (puedeEditar && accesoVehiculos) {
                    cout << "Ingrese la placa del vehiculo a editar: ";
                    string placa;
                    cin >> placa;
                    VehiculoController::editarVehiculo(vehiculos, vehiculosCantidad, placa);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para editar vehiculos." << endl;}
                break;
            }
            case 4: {
                if (puedeEliminar && accesoVehiculos) {
                    cout << "Ingrese la placa del vehiculo a eliminar: ";
                    string placa;
                    cin >> placa;
                    VehiculoController::eliminarVehiculo(vehiculos, vehiculosCantidad, placa);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para eliminar vehiculos." << endl;}
                break;
            }
            case 5: {
                if (accesoVehiculos) {
                    cout << "Ingrese la placa del vehiculo a buscar: ";
                    string placa;
                    cin >> placa;
                    VehiculoController::buscarVehiculo(vehiculos, vehiculosCantidad, placa);
                } else {cout << "No tiene permisos para consultar vehiculos." << endl;}
                break;
            }
            case 6:
                if (accesoClientes) {ClienteController::mostrarClientes(clientes, clientesCantidad);}
                else {cout << "No tiene permisos para consultar clientes." << endl;}
                break;
            case 7:
                if (puedeEditar && accesoClientes) {
                    ClienteController::insertarCliente(clientes, clientesCantidad);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para insertar clientes." << endl;}
                break;
            case 8: {
                if (puedeEditar && accesoClientes) {
                    cout << "Ingrese la cedula del cliente a editar: ";
                    string cedula;
                    cin >> cedula;
                    ClienteController::editarCliente(clientes, clientesCantidad, cedula);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para editar clientes." << endl;}
                break;
            }
            case 9: {
                if (puedeEliminar && accesoClientes) {
                    cout << "Ingrese la cedula del cliente a eliminar: ";
                    string cedula;
                    cin >> cedula;
                    ClienteController::eliminarCliente(clientes, clientesCantidad, cedula);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para eliminar clientes." << endl;}
                break;
            }
            case 10: {
                if (accesoClientes) {
                    cout << "Ingrese la cedula del cliente a buscar: ";
                    string cedula;
                    cin >> cedula;
                    ClienteController::buscarCliente(clientes, clientesCantidad, cedula);
                } else {cout << "No tiene permisos para consultar clientes." << endl;}
                break;
            }
            case 11:
                if (accesoRepuestos) {RepuestoController::mostrarRepuestos(repuestos, repuestosCantidad);}
                else {cout << "No tiene permisos para consultar repuestos." << endl;}
                break;
            case 12:
                if (puedeEditar && accesoRepuestos) {
                    RepuestoController::insertarRepuesto(repuestos, repuestosCantidad);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para insertar repuestos." << endl;}
                break;
            case 13: {
                if (puedeEditar && accesoRepuestos) {
                    cout << "Ingrese el ID del repuesto a editar: ";
                    int id;
                    cin >> id;
                    RepuestoController::editarRepuesto(repuestos, repuestosCantidad, id);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para editar repuestos." << endl;}
                break;
            }
            case 14: {
                if (puedeEliminar && accesoRepuestos) {
                    cout << "Ingrese el ID del repuesto a eliminar: ";
                    int id;
                    cin >> id;
                    RepuestoController::eliminarRepuesto(repuestos, repuestosCantidad, id);
                    cambiosRealizados = true;
                } else {cout << "No tiene permisos para eliminar repuestos." << endl;}
                break;
            }
            case 15: {
                if (accesoRepuestos) {
                    cout << "Ingrese el ID del repuesto a buscar: ";
                    int id;
                    cin >> id;
                    RepuestoController::buscarRepuesto(repuestos, repuestosCantidad, id);
                } else cout << "No tiene permisos para consultar repuestos." << endl;
                break;
            }
            case 16:
                if (cambiosRealizados) {
                    Vehiculo::escribirVehiculos("./vehiculos.csv", vehiculos, vehiculosCantidad);
                    Cliente::escribirClientes("./clientes.csv", clientes, clientesCantidad);
                    Repuesto::escribirRepuestos("./repuestos.csv", repuestos, repuestosCantidad);
                    crearBackup("./vehiculos.csv", carpetaBackup, obtenerNombreBackup("vehiculos"));
                    crearBackup("./clientes.csv", carpetaBackup, obtenerNombreBackup("clientes"));
                    crearBackup("./repuestos.csv", carpetaBackup, obtenerNombreBackup("repuestos"));
                    cout << "Cambios guardados. Saliendo..." << endl;
                } else {
                    cout << "No hay cambios para guardar. Saliendo..." << endl;
                }
                break;
            case 17:
                cout << "Saliendo sin guardar cambios..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        } 
    } while (opcion != 16 && opcion != 17);

    // Liberar memoria dinamica
    delete[] vehiculos;
    delete[] clientes;
    delete[] repuestos;

    return 0;
}
