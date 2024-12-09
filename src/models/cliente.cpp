#include "cliente.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Cliente::Cliente()
    : cedula(""), nombre(""), apellido(""), email(""),
      cantidad_vehiculos_rentados(0), direccion(""), activo(false) {}

// Gets y sets
string Cliente::getCedula() const {
    return cedula;
}

void Cliente::setCedula(const string& cedula) {
    this->cedula = cedula;
}

string Cliente::getNombre() const {
    return nombre;
}

void Cliente::setNombre(const string& nombre) {
    this->nombre = nombre;
}

string Cliente::getApellido() const {
    return apellido;
}

void Cliente::setApellido(const string& apellido) {
    this->apellido = apellido;
}

string Cliente::getEmail() const {
    return email;
}

void Cliente::setEmail(const string& email) {
    this->email = email;
}

int Cliente::getCantidadVehiculosRentados() const {
    return cantidad_vehiculos_rentados;
}

void Cliente::setCantidadVehiculosRentados(int cantidad) {
    cantidad_vehiculos_rentados = cantidad;
}

string Cliente::getDireccion() const {
    return direccion;
}

void Cliente::setDireccion(const string& direccion) {
    this->direccion = direccion;
}

bool Cliente::isActivo() const {
    return activo;
}

void Cliente::setActivo(bool activo) {
    this->activo = activo;
}

// Funcion para leer clientes desde csv
int Cliente::leerClientes(const string& archivo, Cliente*& clientes, int& cantidad) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return -1;
    }

    string linea;

    // Omitir encabezado
    if (!getline(file, linea)) {
        cerr << "Error: Archivo vacio o falta encabezado: " << archivo << endl;
        file.close();
        return -1;
    }

    // Contar lineas restantes para determinar la cantidad de clientes
    // cantidad = 0;
    streampos inicioDatos = file.tellg(); // Guardar posicion actual (despues del encabezado)
    while (getline(file, linea)) {
        cantidad++;
    }

    clientes = new Cliente[cantidad];

    file.clear(); // Limpiar flag eof
    file.seekg(inicioDatos);

    int i = 0;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string temp;

        getline(ss, temp, ',');
        clientes[i].setCedula(temp);

        getline(ss, temp, ',');
        clientes[i].setNombre(temp);

        getline(ss, temp, ',');
        clientes[i].setApellido(temp);

        getline(ss, temp, ',');
        clientes[i].setEmail(temp);

        if (getline(ss, temp, ',')) clientes[i].setCantidadVehiculosRentados(stoi(temp));

        getline(ss, temp, ',');
        clientes[i].setDireccion(temp);

        if (getline(ss, temp, ',')) clientes[i].setActivo(temp == "1");

        i++;
    }

    file.close();
    return cantidad;
}

// Funcion para escribir clientes en csv
void Cliente::escribirClientes(const string& archivo, Cliente* clientes, int cantidad) {
    ofstream file(archivo, ios::trunc); // Limpiar el archivo antes de escribir
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para escribir los clientes." << endl;
        return;
    }

    // Escribir encabezado
    file << "cedula,nombre,apellido,email,cantidad_vehiculos_rentados,direccion,activo\n";

    // Escribir datos de cada cliente
    for (int i = 0; i < cantidad; ++i) {
        if (!clientes[i].getCedula().empty()) { // Validar que la cedula no este vacia
            file << clientes[i].getCedula() << ","
                 << clientes[i].getNombre() << ","
                 << clientes[i].getApellido() << ","
                 << clientes[i].getEmail() << ","
                 << clientes[i].getCantidadVehiculosRentados() << ","
                 << clientes[i].getDireccion() << ","
                 << (clientes[i].isActivo() ? "1" : "0") << "\n";
        }
    }

    file.close();
}

// Funcion para insertar nuevo cliente
void Cliente::insertarCliente(Cliente*& clientes, int& cantidad) {
    Cliente nuevo;
    cout << "Ingrese los detalles del nuevo cliente:" << endl;

    string temp;
    cout << "Cedula: ";
    getline(cin >> ws, temp);
    nuevo.setCedula(temp);

    cout << "Nombre: ";
    getline(cin >> ws, temp);
    nuevo.setNombre(temp);

    cout << "Apellido: ";
    getline(cin >> ws, temp);
    nuevo.setApellido(temp);

    cout << "Email: ";
    getline(cin >> ws, temp);
    nuevo.setEmail(temp);

    int valInt;
    cout << "Cantidad de Vehiculos Rentados: ";
    cin >> valInt;
    nuevo.setCantidadVehiculosRentados(valInt);

    cout << "Direccion: ";
    getline(cin >> ws, temp);
    nuevo.setDireccion(temp);

    bool valBool;
    cout << "Activo (1 para Si, 0 para No): ";
    cin >> valBool;
    nuevo.setActivo(valBool);

    Cliente* nuevoArray = new Cliente[cantidad + 1];
    for (int i = 0; i < cantidad; ++i) {
        nuevoArray[i] = clientes[i];
    }
    nuevoArray[cantidad] = nuevo;

    delete[] clientes;
    clientes = nuevoArray;
    cantidad++;

    cout << "Cliente registrado exitosamente." << endl;
}

// Funcion para mostrar todos los clientes
void Cliente::mostrarClientes(Cliente* clientes, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cout << "Cliente " << i + 1 << ": " 
             << clientes[i].getCedula() << ", " 
             << clientes[i].getNombre() << ", " 
             << clientes[i].getApellido() << ", " 
             << clientes[i].getEmail() << ", " 
             << clientes[i].getCantidadVehiculosRentados() << ", " 
             << clientes[i].getDireccion() << ", " 
             << (clientes[i].isActivo() ? "Activo" : "Inactivo") << endl;
    }
}

// Funcion para buscar cliente por cedula
int Cliente::buscarCliente(Cliente* clientes, int cantidad, const string& cedula) {
    for (int i = 0; i < cantidad; ++i) {
        if (clientes[i].getCedula() == cedula) {
            return i;
        }
    }
    return -1;
}

// Funcion para editar datos de un cliente por cedula
void Cliente::editarCliente(Cliente* clientes, int cantidad, const string& cedula) {
    int index = Cliente::buscarCliente(clientes, cantidad, cedula);
    if (index == -1) {
        cout << "Cliente no encontrado." << endl;
        return;
    }

    string temp;
    int valInt;
    bool valBool;

    cout << "Editar datos del cliente (Escriba -1 para no modificar):" << endl;

    cout << "Cedula (" << clientes[index].getCedula() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") clientes[index].setCedula(temp);

    cout << "Nombre (" << clientes[index].getNombre() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") clientes[index].setNombre(temp);

    cout << "Apellido (" << clientes[index].getApellido() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") clientes[index].setApellido(temp);

    cout << "Email (" << clientes[index].getEmail() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") clientes[index].setEmail(temp);

    cout << "Direccion (" << clientes[index].getDireccion() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") clientes[index].setDireccion(temp);

    cout << "Cantidad de Vehiculos Rentados (" << clientes[index].getCantidadVehiculosRentados() << "): ";
    cin >> valInt;
    if (valInt != -1) clientes[index].setCantidadVehiculosRentados(valInt);

    cout << "Activo (1 para Si, 0 para No) (" << clientes[index].isActivo() << "): ";
    cin >> valBool;
    if (valBool != -1) clientes[index].setActivo(valBool);

    cout << "Datos del cliente actualizados exitosamente." << endl;
}

// Funcion para eliminar cliente por cedula
void Cliente::eliminarCliente(Cliente*& clientes, int& cantidad, const string& cedula) {
    int index = Cliente::buscarCliente(clientes, cantidad, cedula);
    if (index == -1) {
        cout << "Cliente no encontrado." << endl;
        return;
    }

    Cliente* nuevoArray = new Cliente[cantidad - 1];
    for (int i = 0, j = 0; i < cantidad; ++i) {
        if (i != index) {
            nuevoArray[j++] = clientes[i];
        }
    }

    delete[] clientes;
    clientes = nuevoArray;
    cantidad--;

    cout << "Cliente eliminado exitosamente." << endl;
}
