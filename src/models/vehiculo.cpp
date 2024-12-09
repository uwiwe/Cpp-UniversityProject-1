#include "vehiculo.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Vehiculo::Vehiculo() 
    : modelo(""), marca(""), placa(""), color(""),
      ano(0), kilometraje(0), rentado(false),
      motor(""), precio_renta(0.0), ced_cliente(""), fecha_de_entrega("") {}

// Implementaciones de gets y sets
string Vehiculo::getModelo() const {
    return modelo;
}

void Vehiculo::setModelo(const string& m) {
    modelo = m;
}

string Vehiculo::getMarca() const {
    return marca;
}

void Vehiculo::setMarca(const string& m) {
    marca = m;
}

string Vehiculo::getPlaca() const {
    return placa;
}

void Vehiculo::setPlaca(const string& p) {
    placa = p;
}

string Vehiculo::getColor() const {
    return color;
}

void Vehiculo::setColor(const string& c) {
    color = c;
}

int Vehiculo::getAno() const {
    return ano;
}

void Vehiculo::setAno(int a) {
    ano = a;
}

int Vehiculo::getKilometraje() const {
    return kilometraje;
}

void Vehiculo::setKilometraje(int k) {
    kilometraje = k;
}

bool Vehiculo::isRentado() const {
    return rentado;
}

void Vehiculo::setRentado(bool r) {
    rentado = r;
}

string Vehiculo::getMotor() const {
    return motor;
}

void Vehiculo::setMotor(const string& m) {
    motor = m;
}

double Vehiculo::getPrecioRenta() const {
    return precio_renta;
}

void Vehiculo::setPrecioRenta(double p) {
    precio_renta = p;
}

string Vehiculo::getCedCliente() const {
    return ced_cliente;
}

void Vehiculo::setCedCliente(const string& c) {
    ced_cliente = c;
}

string Vehiculo::getFechaDeEntrega() const {
    return fecha_de_entrega;
}

void Vehiculo::setFechaDeEntrega(const string& f) {
    fecha_de_entrega = f;
}

// Funcion para leer vehiculos desde CSV
int Vehiculo::leerVehiculos(const string& archivo, Vehiculo*& vehiculos, int& cantidad) {

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

    // Contar lineas restantes para determinar la cantidad de vehiculos
    // cantidad = 0;
    streampos inicioDatos = file.tellg(); // Guardar posicion actual (despues del encabezado)
    while (getline(file, linea)) {
        cantidad++;
    }

    vehiculos = new Vehiculo[cantidad];

    file.clear(); // Limpiar flag eof
    file.seekg(inicioDatos);

    int i = 0;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string temp;

        getline(ss, temp, ',');
        vehiculos[i].setModelo(temp);
        getline(ss, temp, ',');
        vehiculos[i].setMarca(temp);
        getline(ss, temp, ',');
        vehiculos[i].setPlaca(temp);
        getline(ss, temp, ',');
        vehiculos[i].setColor(temp);
        if (getline(ss, temp, ',')) vehiculos[i].setAno(stoi(temp));
        if (getline(ss, temp, ',')) vehiculos[i].setKilometraje(stoi(temp));
        if (getline(ss, temp, ',')) vehiculos[i].setRentado(temp == "1");
        getline(ss, temp, ',');
        vehiculos[i].setMotor(temp);
        if (getline(ss, temp, ',')) vehiculos[i].setPrecioRenta(stod(temp));
        getline(ss, temp, ',');
        vehiculos[i].setCedCliente(temp);
        getline(ss, temp);
        vehiculos[i].setFechaDeEntrega(temp);

        i++;
    }

    file.close();
    return cantidad;
}

// Funcion para escribir vehiculos en CSV
void Vehiculo::escribirVehiculos(const string& archivo, Vehiculo* vehiculos, int cantidad) {
    ofstream file(archivo, ios::trunc); // Limpiar el archivo antes de escribir
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para escribir los vehiculos." << endl;
        return;
    }

    // Escribir encabezado
    file << "modelo,marca,placa,color,ano,kilometraje,rentado,motor,precio_renta,ced_cliente,fecha_de_entrega\n";

    // Escribir datos de cada vehiculo
    for (int i = 0; i < cantidad; ++i) {
        if (!vehiculos[i].getPlaca().empty()) { // Validar que la placa no este vacia
            file << vehiculos[i].getModelo() << ","
                 << vehiculos[i].getMarca() << ","
                 << vehiculos[i].getPlaca() << ","
                 << vehiculos[i].getColor() << ","
                 << vehiculos[i].getAno() << ","
                 << vehiculos[i].getKilometraje() << ","
                 << (vehiculos[i].isRentado() ? "1" : "0") << ","
                 << vehiculos[i].getMotor() << ","
                 << vehiculos[i].getPrecioRenta() << ","
                 << vehiculos[i].getCedCliente() << ","
                 << vehiculos[i].getFechaDeEntrega() << "\n";
        }
    }

    file.close();
}

// Funcion para mostrar todos los vehiculos
void Vehiculo::mostrarVehiculos(Vehiculo* vehiculos, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cout << "Vehiculo " << i + 1 << ": " 
             << vehiculos[i].getModelo() << ", " 
             << vehiculos[i].getMarca() << ", " 
             << vehiculos[i].getPlaca() << ", " 
             << vehiculos[i].getColor() << ", " 
             << vehiculos[i].getAno() << ", " 
             << vehiculos[i].getKilometraje() << ", " 
             << (vehiculos[i].isRentado() ? "Si" : "No") << ", "
             << vehiculos[i].getMotor() << ", " 
             << vehiculos[i].getPrecioRenta() << ", "
             << vehiculos[i].getCedCliente() << ", " 
             << vehiculos[i].getFechaDeEntrega() << endl;
    }
}

// Funcion para insertar un nuevo vehiculo
void Vehiculo::insertarVehiculo(Vehiculo*& vehiculos, int& cantidad) {
    Vehiculo nuevo;
    cout << "Ingrese los detalles del nuevo vehiculo:" << endl;

    string temp;
    cout << "Modelo: ";
    getline(cin >> ws, temp); // "ws" Se utiliza para eliminar espacios en blanco residuales
    nuevo.setModelo(temp);

    cout << "Marca: ";
    getline(cin >> ws, temp);
    nuevo.setMarca(temp);

    cout << "Placa: ";
    getline(cin >> ws, temp);
    nuevo.setPlaca(temp);

    cout << "Color: ";
    getline(cin >> ws, temp);
    nuevo.setColor(temp);

    int valInt;
    cout << "Ano: ";
    cin >> valInt;
    nuevo.setAno(valInt);

    cout << "Kilometraje: ";
    cin >> valInt;
    nuevo.setKilometraje(valInt);

    bool valBool;
    cout << "Rentado (1 para Si, 0 para No): ";
    cin >> valBool;
    nuevo.setRentado(valBool);

    cout << "Motor: ";
    getline(cin >> ws, temp);
    nuevo.setMotor(temp);

    double valDouble;
    cout << "Precio de Renta: ";
    cin >> valDouble;
    nuevo.setPrecioRenta(valDouble);

    cout << "Cedula Cliente: ";
    getline(cin >> ws, temp);
    nuevo.setCedCliente(temp);

    cout << "Fecha de Entrega: ";
    getline(cin >> ws, temp);
    nuevo.setFechaDeEntrega(temp);

    Vehiculo* nuevoArray = new Vehiculo[cantidad + 1]; // 'new' indica que estoy reservando memoria para un arreglo de vehiculo con 'count + 1' elementos
    for (int i = 0; i < cantidad; ++i) {
        nuevoArray[i] = vehiculos[i];
    }
    nuevoArray[cantidad] = nuevo;
    delete[] vehiculos; // Liberar el espacio asignado con new
    vehiculos = nuevoArray;
    cantidad++;

    cout << "Vehiculo registrado exitosamente." << endl;
}

// Funcion para buscar vehiculo por placa
int Vehiculo::buscarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa) {
    for (int i = 0; i < cantidad; ++i) {
        if (vehiculos[i].getPlaca() == placa) {
            return i; // Retorna el indice si encuentra el vehiculo
        }
    }
    return -1; // Retorna -1 si no se encuentra el vehiculo
}


// Funcion para editar vehiculo por placa
void Vehiculo::editarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa) {
    int index = buscarVehiculo(vehiculos, cantidad, placa);
    if (index == -1) {
        cout << "Vehiculo no encontrado." << endl;
        return;
    }

    cout << "Editar datos del vehiculo (Escriba -1 para no modificar):" << endl;

    string temp;
    int valInt;
    double valDouble;
    bool valBool;

    cout << "Modelo (" << vehiculos[index].getModelo() << "): ";
    getline(cin >> ws, temp); 
    if (temp != "-1") vehiculos[index].setModelo(temp);

    cout << "Marca (" << vehiculos[index].getMarca() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") vehiculos[index].setMarca(temp);

    cout << "Placa (" << vehiculos[index].getPlaca() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") vehiculos[index].setPlaca(temp);

    cout << "Color (" << vehiculos[index].getColor() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") vehiculos[index].setColor(temp);

    cout << "Ano (" << vehiculos[index].getAno() << "): ";
    cin >> valInt;
    if (valInt != -1) vehiculos[index].setAno(valInt);
    cin.ignore();

    cout << "Kilometraje (" << vehiculos[index].getKilometraje() << "): ";
    cin >> valInt;
    if (valInt != -1) vehiculos[index].setKilometraje(valInt);
    cin.ignore();

    cout << "Rentado (1 para Si, 0 para No) (" << (vehiculos[index].isRentado() ? "Si" : "No") << "): ";
    cin >> valBool;
    if (valBool != -1) vehiculos[index].setRentado(valBool);
    cin.ignore();

    cout << "Motor (" << vehiculos[index].getMotor() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") vehiculos[index].setMotor(temp);

    cout << "Precio de Renta (" << vehiculos[index].getPrecioRenta() << "): ";
    cin >> valDouble;
    if (valDouble != -1) vehiculos[index].setPrecioRenta(valDouble);
    cin.ignore();

    cout << "Cedula Cliente (" << vehiculos[index].getCedCliente() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") vehiculos[index].setCedCliente(temp);

    cout << "Fecha de Entrega (" << vehiculos[index].getFechaDeEntrega() << "): ";
    getline(cin >> ws, temp);
    if (temp != "-1") vehiculos[index].setFechaDeEntrega(temp);

    cout << "Datos del vehiculo actualizados exitosamente." << endl;
}


// Funcion para eliminar vehiculo por placa
void Vehiculo::eliminarVehiculo(Vehiculo*& vehiculos, int& cantidad, const string& placa) {
    int index = buscarVehiculo(vehiculos, cantidad, placa);
    if (index == -1) {
        cout << "Vehiculo no encontrado." << endl;
        return;
    }

    Vehiculo* nuevoArray = new Vehiculo[cantidad - 1];
    for (int i = 0, j = 0; i < cantidad; ++i) {
        if (i != index) {
            nuevoArray[j++] = vehiculos[i];
        }
    }

    delete[] vehiculos;
    vehiculos = nuevoArray;
    cantidad--;

    cout << "Vehiculo eliminado exitosamente." << endl;
}
