#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Vehiculo {
    string modelo, marca, placa, color, motor, ced_cliente, fecha_de_entrega;
    int ano, kilometraje;
    double precio_renta;
    bool rentado;
};

struct Cliente {
    string cedula, nombre, apellido, email, direccion;
    int cantidad_vehiculos_rentados;
    bool activo;
};

struct Repuesto {
    string modelo, marca, nombre, modelo_carro;
    int ano_carro, existencias;
    double precio;
};

// FUNCIONES DE VEHICULOS ----------------------------------------------------------------------------------

// Funcion para leer vehiculos desde csv
int leerVehiculos(const string& archivo, Vehiculo*& vehiculos) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return -1;
    }

    string linea;
    int cantidad = 0;

    while (getline(file, linea)) cantidad++; // Contar las lineas
    file.clear(); // Limpiar flag eofbit para poder leer el archivo nuevamente 
    file.seekg(0, ios::beg); // Mover el puntero al inicio para leerlo desde el principio y cargar los datos

    vehiculos = new Vehiculo[cantidad]; // Crear arreglo dinamico 
    int i = 0;

    while (getline(file, linea)) {
        stringstream ss(linea); // 'ss' Permite procesar cada valor para separarlo por comas
        string token; // Para guardar cada valor temporalmente

        getline(ss, vehiculos[i].modelo, ',');
        getline(ss, vehiculos[i].marca, ',');
        getline(ss, vehiculos[i].placa, ',');
        getline(ss, vehiculos[i].color, ',');
        ss >> vehiculos[i].ano; // Leer entero
        ss.ignore(1); // Omitir coma
        ss >> vehiculos[i].kilometraje;
        ss.ignore(1);
        ss >> vehiculos[i].rentado;
        ss.ignore(1);
        getline(ss, vehiculos[i].motor, ',');
        ss >> vehiculos[i].precio_renta;
        ss.ignore(1);
        getline(ss, vehiculos[i].ced_cliente, ',');
        getline(ss, vehiculos[i].fecha_de_entrega);

        i++;
    }
    file.close();
    return cantidad;
}

// Funcion para escribir vehiculos en csv
void escribirVehiculos(const string& archivo, Vehiculo* vehiculos, int cantidad) {
    ofstream file(archivo);
    for (int i = 0; i < cantidad; ++i) {
        file << vehiculos[i].modelo << "," << vehiculos[i].marca << "," << vehiculos[i].placa << ","
             << vehiculos[i].color << "," << vehiculos[i].ano << "," << vehiculos[i].kilometraje << ","
             << vehiculos[i].rentado << "," // Escribir rentado como 1 (true) o 0 (false)
             << vehiculos[i].motor << "," << vehiculos[i].precio_renta << ","
             << vehiculos[i].ced_cliente << "," << vehiculos[i].fecha_de_entrega << endl;
    }
    file.close();
}


// Funcion para insertar nuevo vehiculo
void insertarVehiculo(Vehiculo*& vehiculos, int& cantidad) {
    Vehiculo nuevo;
    cout << "Ingrese los detalles del nuevo vehiculo:" << endl;
    cout << "Modelo: "; cin >> nuevo.modelo;
    cout << "Marca: "; cin >> nuevo.marca;
    cout << "Placa: "; cin >> nuevo.placa;
    cout << "Color: "; cin >> nuevo.color;
    cout << "Ano: "; cin >> nuevo.ano;
    cout << "Kilometraje: "; cin >> nuevo.kilometraje;
    cout << "Rentado (1 para Si, 0 para No): "; cin >> nuevo.rentado;
    cout << "Motor: "; cin >> nuevo.motor;
    cout << "Precio de Renta: "; cin >> nuevo.precio_renta;
    cout << "Cedula Cliente: "; cin >> nuevo.ced_cliente;
    cout << "Fecha de Entrega: "; cin >> nuevo.fecha_de_entrega;
    cout << "Vehiculo registrado exitosamente." << endl;

    Vehiculo* nuevoArray = new Vehiculo[cantidad + 1]; // 'new' indica que estoy reservando memoria para un arreglo de vehiculo con 'count + 1' elementos
    for (int i = 0; i < cantidad; ++i) {
        nuevoArray[i] = vehiculos[i];
    }
    nuevoArray[cantidad] = nuevo;
    delete[] vehiculos; // Liberar el espacio asignado con new
    vehiculos = nuevoArray;
    cantidad++;
}

// Función para mostrar todos los vehiculos
void mostrarVehiculos(Vehiculo* vehiculos, int cantidad) {
    for (int i = 1; i < cantidad; ++i) {
        cout << "Vehiculo " << i << ": " << vehiculos[i].modelo << ", " << vehiculos[i].marca
             << ", " << vehiculos[i].placa << ", " << vehiculos[i].color << ", " << vehiculos[i].ano
             << ", " << vehiculos[i].kilometraje << ", " << (vehiculos[i].rentado ? "Activo" : "Inactivo") << ", "
             << vehiculos[i].motor << ", " << vehiculos[i].precio_renta << ", "
             << vehiculos[i].ced_cliente << ", " << vehiculos[i].fecha_de_entrega << endl;
    }
}

// FUNCIONES DE CLIENTES ----------------------------------------------------------------------------------

// Funcion para leer clientes desde csv
int leerClientes(const string& archivo, Cliente*& clientes) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return -1;
    }
    string linea;
    int cantidad = 0;
    while (getline(file, linea)) cantidad++;
    file.clear();
    file.seekg(0, ios::beg);

    clientes = new Cliente[cantidad];
    int i = 0;
    while (getline(file, linea)) {
        stringstream ss(linea);
        getline(ss, clientes[i].cedula, ',');
        getline(ss, clientes[i].nombre, ',');
        getline(ss, clientes[i].apellido, ',');
        getline(ss, clientes[i].email, ',');
        ss >> clientes[i].cantidad_vehiculos_rentados;
        ss.ignore(1);
        getline(ss, clientes[i].direccion, ',');
        ss >> clientes[i].activo;
        i++;
    }
    file.close();
    return cantidad;
}

// Funcion para escribir clientes en csv
void escribirClientes(const string& archivo, Cliente* clientes, int cantidad) {
    ofstream file(archivo);
    for (int i = 0; i < cantidad; ++i) {
        file << clientes[i].cedula << "," << clientes[i].nombre << "," << clientes[i].apellido << ","
             << clientes[i].email << "," << clientes[i].cantidad_vehiculos_rentados << ","
             << clientes[i].direccion << "," << clientes[i].activo << endl;
    }
    file.close();
}

// Funcion para insertar nuevo cliente
void insertarCliente(Cliente*& clientes, int& cantidad) {
    Cliente nuevo;
    cout << "Ingrese los detalles del nuevo cliente:" << endl;
    cout << "Cedula: "; cin >> nuevo.cedula;
    cout << "Nombre: "; cin >> nuevo.nombre;
    cout << "Apellido: "; cin >> nuevo.apellido;
    cout << "Email: "; cin >> nuevo.email;
    cout << "Cantidad de Vehiculos Rentados: "; cin >> nuevo.cantidad_vehiculos_rentados;
    cout << "Direccion: "; cin >> nuevo.direccion;
    cout << "Activo (1 para Si, 0 para No): "; cin >> nuevo.activo;
    Cliente* nuevoArray = new Cliente[cantidad + 1];
    for (int i = 0; i < cantidad; ++i) nuevoArray[i] = clientes[i];
    nuevoArray[cantidad] = nuevo;
    delete[] clientes;
    clientes = nuevoArray;
    cantidad++;
}

// Funcion para mostrar todos los clientes
void mostrarClientes(Cliente* clientes, int cantidad) {
    for (int i = 1; i < cantidad; ++i) {
        cout << "Cliente " << i << ": " << clientes[i].cedula << ", " << clientes[i].nombre << ", "
             << clientes[i].apellido << ", " << clientes[i].email << ", "
             << clientes[i].cantidad_vehiculos_rentados << ", " << clientes[i].direccion << ", "
             << (clientes[i].activo ? "Activo" : "Inactivo") << endl;
    }
}

// FUNCIONES DE REPUESTOS ----------------------------------------------------------------------------------

int leerRepuestos(const string& archivo, Repuesto*& repuestos) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return -1;
    }
    string linea;
    int cantidad = 0;
    while (getline(file, linea)) cantidad++;
    file.clear();
    file.seekg(0, ios::beg);

    repuestos = new Repuesto[cantidad];
    int i = 0;
    while (getline(file, linea)) {
        stringstream ss(linea);
        getline(ss, repuestos[i].modelo, ',');
        getline(ss, repuestos[i].marca, ',');
        getline(ss, repuestos[i].nombre, ',');
        getline(ss, repuestos[i].modelo_carro, ',');
        ss >> repuestos[i].ano_carro;
        ss.ignore(1);
        ss >> repuestos[i].precio;
        ss.ignore(1);
        ss >> repuestos[i].existencias;
        i++;
    }
    file.close();
    return cantidad;
}

void escribirRepuestos(const string& archivo, Repuesto* repuestos, int cantidad) {
    ofstream file(archivo);
    for (int i = 0; i < cantidad; ++i) {
        file << repuestos[i].modelo << "," << repuestos[i].marca << "," << repuestos[i].nombre << ","
             << repuestos[i].modelo_carro << "," << repuestos[i].ano_carro << "," << repuestos[i].precio << ","
             << repuestos[i].existencias << endl;
    }
    file.close();
}

void insertarRepuesto(Repuesto*& repuestos, int& cantidad) {
    Repuesto nuevo;
    cout << "Ingrese los detalles del nuevo repuesto:" << endl;
    cout << "Modelo: "; cin >> nuevo.modelo;
    cout << "Marca: "; cin >> nuevo.marca;
    cout << "Nombre: "; cin >> nuevo.nombre;
    cout << "Modelo del Carro: "; cin >> nuevo.modelo_carro;
    cout << "Ano del Carro: "; cin >> nuevo.ano_carro;
    cout << "Precio: "; cin >> nuevo.precio;
    cout << "Existencias: "; cin >> nuevo.existencias;
    Repuesto* nuevoArray = new Repuesto[cantidad + 1];
    for (int i = 0; i < cantidad; ++i) nuevoArray[i] = repuestos[i];
    nuevoArray[cantidad] = nuevo;
    delete[] repuestos;
    repuestos = nuevoArray;
    cantidad++;
}

// Funcion para mostrar todos los repuestos
void mostrarRepuestos(Repuesto* repuestos, int cantidad) {
    for (int i = 1; i < cantidad; ++i) {
        cout << "Repuesto " << i << ": " << repuestos[i].modelo << ", " << repuestos[i].marca << ", "
             << repuestos[i].nombre << ", " << repuestos[i].modelo_carro << ", "
             << repuestos[i].ano_carro << ", " << repuestos[i].precio << ", "
             << repuestos[i].existencias << endl;
    }
}

int main() {
    // Inicializar punteros y variables de cantidad para vehiculo, cliente y repuesto
    Vehiculo* vehiculos = nullptr;
    Cliente* clientes = nullptr;
    Repuesto* repuestos = nullptr;

    int vehiculosCantidad = leerVehiculos("../../bin/vehiculos.csv", vehiculos);
    int clientesCantidad = leerClientes("../../bin/clientes.csv", clientes);
    int repuestosCantidad = leerRepuestos("../../bin/repuestos.csv", repuestos);

    int opcion;
    do {
        cout << "\nBienvenido al Menu. Seleccione una opcion:" << endl;
        cout << "1. Ver vehiculos" << endl;
        cout << "2. Insertar vehiculo" << endl;
        cout << "3. Ver clientes" << endl;
        cout << "4. Insertar cliente" << endl;
        cout << "5. Ver repuestos" << endl;
        cout << "6. Insertar repuesto" << endl;
        cout << "7. Guardar y salir (Se eliminaran los datos anteriores)" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarVehiculos(vehiculos, vehiculosCantidad);
                break;
            case 2:
                insertarVehiculo(vehiculos, vehiculosCantidad);
                break;
            case 3:
                mostrarClientes(clientes, clientesCantidad);
                break;
            case 4:
                insertarCliente(clientes, clientesCantidad);
                break;
            case 5:
                mostrarRepuestos(repuestos, repuestosCantidad);
                break;
            case 6:
                insertarRepuesto(repuestos, repuestosCantidad);
                break;
            case 7:
                // Guardar los datos en los archivos csv y salir
                escribirVehiculos("../../bin/vehiculos.csv", vehiculos, vehiculosCantidad);
                escribirClientes("../../bin/clientes.csv", clientes, clientesCantidad);
                escribirRepuestos("../../bin/repuestos.csv", repuestos, repuestosCantidad);
                cout << "Datos guardados. Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while(opcion != 7);

    // Liberar memoria asignada dinamicamente
    delete[] vehiculos;
    delete[] clientes;
    delete[] repuestos;

    return 0;
}

