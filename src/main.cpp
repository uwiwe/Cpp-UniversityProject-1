#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;


// MAIN ---------------------------------------------------------------------------------------------------

int main() {
    // Inicializar punteros y variables de cantidad para Vehiculo, Cliente y Repuesto
    Vehiculo* vehiculos = nullptr;
    Cliente* clientes = nullptr;
    Repuesto* repuestos = nullptr;

    int vehiculosCantidad = leerVehiculos("vehiculos.csv", vehiculos);
    int clientesCantidad = leerClientes("clientes.csv", clientes);
    int repuestosCantidad = leerRepuestos("repuestos.csv", repuestos);

    int opcion;
    do {
        cout << "\nBienvenido al Menu. Seleccione una opcion:" << endl;
        cout << "1. Ver todos los vehiculos" << endl;
        cout << "2. Insertar vehiculo" << endl;
        cout << "3. Editar vehiculo" << endl;
        cout << "4. Eliminar vehiculo" << endl;
        cout << "5. Ver un vehiculo especifico" << endl;
        cout << "6. Ver todos los clientes" << endl;
        cout << "7. Insertar cliente" << endl;
        cout << "8. Editar cliente" << endl;
        cout << "9. Eliminar cliente" << endl;
        cout << "10. Ver un cliente especifico" << endl;
        cout << "11. Ver todos los repuestos" << endl;
        cout << "12. Insertar repuesto" << endl;
        cout << "13. Editar repuesto" << endl;
        cout << "14. Eliminar repuesto" << endl;
        cout << "15. Ver un repuesto especifico" << endl;
        cout << "16. Guardar y salir" << endl;
        cout << "17. Salir sin guardar" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarVehiculos(vehiculos, vehiculosCantidad);
                break;
            case 2:
                insertarVehiculo(vehiculos, vehiculosCantidad);
                break;
            case 3: {
                cout << "Ingrese la placa del vehiculo a editar: ";
                string placa;
                cin >> placa;
                editarVehiculo(vehiculos, vehiculosCantidad, placa);
                break;
            }
            case 4: {
                cout << "Ingrese la placa del vehiculo a eliminar: ";
                string placa;
                cin >> placa;
                eliminarVehiculo(vehiculos, vehiculosCantidad, placa);
                break;
            }
            case 5: {
                cout << "Ingrese la placa del vehiculo a buscar: ";
                string placa;
                cin >> placa;
                int index = buscarVehiculo(vehiculos, vehiculosCantidad, placa);
                if (index != -1) {
                    cout << "Vehiculo encontrado: " << endl;
                    cout << "Modelo: " << vehiculos[index].modelo << ", Marca: " << vehiculos[index].marca
                         << ", Placa: " << vehiculos[index].placa << ", Color: " << vehiculos[index].color
                         << ", Ano: " << vehiculos[index].ano << ", Kilometraje: " << vehiculos[index].kilometraje
                         << ", Rentado: " << (vehiculos[index].rentado ? "Si" : "No") << ", Motor: " << vehiculos[index].motor
                         << ", Precio de Renta: " << vehiculos[index].precio_renta << ", Cedula Cliente: "
                         << vehiculos[index].ced_cliente << ", Fecha de Entrega: " << vehiculos[index].fecha_de_entrega << endl;
                } else {
                    cout << "Vehiculo no encontrado." << endl;
                }
                break;
            }
            case 6:
                mostrarClientes(clientes, clientesCantidad);
                break;
            case 7:
                insertarCliente(clientes, clientesCantidad);
                break;
            case 8: {
                cout << "Ingrese la cedula del cliente a editar: ";
                string cedula;
                cin >> cedula;
                editarCliente(clientes, clientesCantidad, cedula);
                break;
            }
            case 9: {
                cout << "Ingrese la cedula del cliente a eliminar: ";
                string cedula;
                cin >> cedula;
                eliminarCliente(clientes, clientesCantidad, cedula);
                break;
            }
            case 10: {
                cout << "Ingrese la cedula del cliente a buscar: ";
                string cedula;
                cin >> cedula;
                int index = buscarCliente(clientes, clientesCantidad, cedula);
                if (index != -1) {
                    cout << "Cliente encontrado: " << endl;
                    cout << "Cedula: " << clientes[index].cedula << ", Nombre: " << clientes[index].nombre
                         << ", Apellido: " << clientes[index].apellido << ", Email: " << clientes[index].email
                         << ", Cantidad de Vehiculos Rentados: " << clientes[index].cantidad_vehiculos_rentados
                         << ", Direccion: " << clientes[index].direccion
                         << ", Activo: " << (clientes[index].activo ? "Si" : "No") << endl;
                } else {
                    cout << "Cliente no encontrado." << endl;
                }
                break;
            }
            case 11:
                mostrarRepuestos(repuestos, repuestosCantidad);
                break;
            case 12:
                insertarRepuesto(repuestos, repuestosCantidad);
                break;
            case 13: {
                cout << "Ingrese el ID del repuesto a editar: ";
                int id;
                cin >> id;
                editarRepuesto(repuestos, repuestosCantidad, id);
                break;
            }
            case 14: {
                cout << "Ingrese el ID del repuesto a eliminar: ";
                int id;
                cin >> id;
                eliminarRepuesto(repuestos, repuestosCantidad, id);
                break;
            }
            case 15: {
                cout << "Ingrese el ID del repuesto a buscar: ";
                int id;
                cin >> id;
                int index = buscarRepuesto(repuestos, repuestosCantidad, id);
                if (index != -1) {
                    cout << "Repuesto encontrado: " << endl;
                    cout << "ID: " << repuestos[index].id << ", Modelo: " << repuestos[index].modelo
                         << ", Marca: " << repuestos[index].marca << ", Nombre: " << repuestos[index].nombre
                         << ", Modelo del Carro: " << repuestos[index].modelo_carro
                         << ", Ano del Carro: " << repuestos[index].ano_carro << ", Precio: "
                         << repuestos[index].precio << ", Existencias: " << repuestos[index].existencias << endl;
                } else {
                    cout << "Repuesto no encontrado." << endl;
                }
                break;
            }
            case 16: {
                // Guardar los datos en los archivos csv y salir
                escribirVehiculos("vehiculos.csv", vehiculos, vehiculosCantidad);
                escribirClientes("clientes.csv", clientes, clientesCantidad);
                escribirRepuestos("repuestos.csv", repuestos, repuestosCantidad);
                cout << "Datos guardados. Saliendo del programa..." << endl;
                break;
            }
            case 17: {
                // El usuario puede elegir salir sin guardar los cambios hechos en los archivos
                cout << "Saliendo del programa sin guardar cambios..." << endl;
                break;
            }
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