#include "repuesto.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Repuesto::Repuesto()
    : id(0), modelo(""), marca(""), nombre(""),
      modelo_carro(""), ano_carro(0), precio(0.0), existencias(0) {}

// Implementaciones de gets y sets
int Repuesto::getId() const {
    return id;
}

void Repuesto::setId(int id) {
    this->id = id;
}

string Repuesto::getModelo() const {
    return modelo;
}

void Repuesto::setModelo(const string& modelo) {
    this->modelo = modelo;
}

string Repuesto::getMarca() const {
    return marca;
}

void Repuesto::setMarca(const string& marca) {
    this->marca = marca;
}

string Repuesto::getNombre() const {
    return nombre;
}

void Repuesto::setNombre(const string& nombre) {
    this->nombre = nombre;
}

string Repuesto::getModeloCarro() const {
    return modelo_carro;
}

void Repuesto::setModeloCarro(const string& modelo_carro) {
    this->modelo_carro = modelo_carro;
}

int Repuesto::getAnoCarro() const {
    return ano_carro;
}

void Repuesto::setAnoCarro(int ano_carro) {
    this->ano_carro = ano_carro;
}

double Repuesto::getPrecio() const {
    return precio;
}

void Repuesto::setPrecio(double precio) {
    this->precio = precio;
}

int Repuesto::getExistencias() const {
    return existencias;
}

void Repuesto::setExistencias(int existencias) {
    this->existencias = existencias;
}

// Funcion para leer repuestos desde CSV
int Repuesto::leerRepuestos(const string& archivo, Repuesto*& repuestos, int& cantidad) {
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

    // Contar lineas restantes para determinar la cantidad de repuestos
    // cantidad = 0;
    streampos inicioDatos = file.tellg(); // Guardar posicion actual (despues del encabezado)
    while (getline(file, linea)) {
        if (!linea.empty()) {
            cantidad++;
        }
    }

    repuestos = new Repuesto[cantidad];

    file.clear(); // Limpiar flag eof
    file.seekg(inicioDatos);

    int i = 0;
    while (getline(file, linea)) {
        if (!linea.empty()) {
            stringstream ss(linea);
            string temp;

            int valInt;
            double valDouble;

            ss >> valInt;
            repuestos[i].setId(valInt);
            ss.ignore(1); // Omitir coma

            getline(ss, temp, ',');
            repuestos[i].setModelo(temp);

            getline(ss, temp, ',');
            repuestos[i].setMarca(temp);

            getline(ss, temp, ',');
            repuestos[i].setNombre(temp);

            getline(ss, temp, ',');
            repuestos[i].setModeloCarro(temp);

            if (getline(ss, temp, ',')) repuestos[i].setAnoCarro(stoi(temp));

            if (getline(ss, temp, ',')) repuestos[i].setPrecio(stod(temp));

            if (getline(ss, temp, ',')) repuestos[i].setExistencias(stoi(temp));

            i++;
        }
    }

    file.close();
    return cantidad;
}

// Funcion para escribir repuestos en CSV
void Repuesto::escribirRepuestos(const string& archivo, Repuesto* repuestos, int cantidad) {
    ofstream file(archivo, ios::trunc); // Abrir en modo truncado para limpiar el archivo existente
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para escribir los repuestos." << endl;
        return;
    }

    // Escribir encabezado
    file << "id,modelo,marca,nombre,modelo_carro,ano_carro,precio,existencias\n";

    for (int i = 0; i < cantidad; ++i) {
        if (repuestos[i].getId() != 0) {
            file << repuestos[i].getId() << ","
                 << repuestos[i].getModelo() << ","
                 << repuestos[i].getMarca() << ","
                 << repuestos[i].getNombre() << ","
                 << repuestos[i].getModeloCarro() << ","
                 << repuestos[i].getAnoCarro() << ","
                 << repuestos[i].getPrecio() << ","
                 << repuestos[i].getExistencias() << "\n";
        }
    }

    file.close();
}

// Funcion para insertar repuesto
void Repuesto::insertarRepuesto(Repuesto*& repuestos, int& cantidad) {
    Repuesto nuevo;
    nuevo.setId((cantidad == 0) ? 1 : repuestos[cantidad - 1].getId() + 1);

    cout << "Ingrese los detalles del nuevo repuesto:" << endl;

    string temp;
    int valInt;
    double valDouble;

    cout << "Modelo: ";
    getline(cin >> ws, temp);
    nuevo.setModelo(temp);

    cout << "Marca: ";
    getline(cin >> ws, temp);
    nuevo.setMarca(temp);

    cout << "Nombre: ";
    getline(cin >> ws, temp);
    nuevo.setNombre(temp);

    cout << "Modelo del Carro: ";
    getline(cin >> ws, temp);
    nuevo.setModeloCarro(temp);

    cout << "Ano del Carro: ";
    cin >> valInt;
    nuevo.setAnoCarro(valInt);

    cout << "Precio: ";
    cin >> valDouble;
    nuevo.setPrecio(valDouble);

    cout << "Existencias: ";
    cin >> valInt;
    nuevo.setExistencias(valInt);

    Repuesto* nuevoArray = new Repuesto[cantidad + 1];
    for (int i = 0; i < cantidad; ++i) {
        nuevoArray[i] = repuestos[i];
    }
    nuevoArray[cantidad] = nuevo;

    delete[] repuestos;
    repuestos = nuevoArray;
    cantidad++;

    cout << "Repuesto agregado correctamente con ID: " << nuevo.getId() << endl;
}

// Funcion para mostrar todos los repuestos
void Repuesto::mostrarRepuestos(Repuesto* repuestos, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cout << "Repuesto ID: " << repuestos[i].getId() << ", "
             << repuestos[i].getModelo() << ", "
             << repuestos[i].getMarca() << ", "
             << repuestos[i].getNombre() << ", "
             << repuestos[i].getModeloCarro() << ", "
             << repuestos[i].getAnoCarro() << ", "
             << repuestos[i].getPrecio() << ", "
             << repuestos[i].getExistencias() << endl;
    }
}

// Funcion para buscar repuesto por ID
int Repuesto::buscarRepuesto(Repuesto* repuestos, int cantidad, int id) {
    for (int i = 0; i < cantidad; ++i) {
        if (repuestos[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

// Funcion para editar repuesto por ID
void Repuesto::editarRepuesto(Repuesto* repuestos, int cantidad, int id) {
    int index = buscarRepuesto(repuestos, cantidad, id);
    if (index == -1) {
        cout << "Repuesto no encontrado." << endl;
        return;
    }

    cout << "Editar datos del repuesto (deje en blanco para no modificar):" << endl;

    string temp;
    int valInt;
    double valDouble;

    cout << "Modelo (" << repuestos[index].getModelo() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") repuestos[index].setModelo(temp);

    cout << "Marca (" << repuestos[index].getMarca() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") repuestos[index].setMarca(temp);

    cout << "Nombre (" << repuestos[index].getNombre() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") repuestos[index].setNombre(temp);

    cout << "Modelo del Carro (" << repuestos[index].getModeloCarro() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") repuestos[index].setModeloCarro(temp);

    cout << "Ano del Carro (" << repuestos[index].getAnoCarro() << "): ";
    cin >> valInt;
    if (valInt != -1) repuestos[index].setAnoCarro(valInt);

    cout << "Precio (" << repuestos[index].getPrecio() << "): ";
    cin >> valDouble;
    if (valDouble != -1) repuestos[index].setPrecio(valDouble);

    cout << "Existencias (" << repuestos[index].getExistencias() << "): ";
    cin >> valInt;
    if (valInt != -1) repuestos[index].setExistencias(valInt);

    cout << "Datos del repuesto actualizados exitosamente." << endl;
}

// Funcion para eliminar repuesto por ID
void Repuesto::eliminarRepuesto(Repuesto*& repuestos, int& cantidad, int id) {
    int index = buscarRepuesto(repuestos, cantidad, id);
    if (index == -1) {
        cout << "Repuesto no encontrado." << endl;
        return;
    }

    Repuesto* nuevoArray = new Repuesto[cantidad - 1];
    for (int i = 0, j = 0; i < cantidad; ++i) {
        if (i != index) {
            nuevoArray[j++] = repuestos[i];
        }
    }

    delete[] repuestos;
    repuestos = nuevoArray;
    cantidad--;

    cout << "Repuesto eliminado exitosamente." << endl;
}
