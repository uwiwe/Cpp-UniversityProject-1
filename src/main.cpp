#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Vehiculo {
    string modelo = "";
    string marca = "";
    string placa = "";
    string color = "";
    int ano = 0;
    int kilometraje = 0;
    bool rentado = false;
    string motor = "";
    double precio_renta = 0.0;
    string ced_cliente = "";
    string fecha_de_entrega = "";
};

struct Cliente {
    string cedula = "";
    string nombre = "";
    string apellido = "";
    string email = "";
    int cantidad_vehiculos_rentados = 0;
    string direccion = "";
    bool activo = true;
};

struct Repuesto {
    string modelo = "";
    string marca = "";
    string nombre = "";
    string modelo_carro = "";
    int ano_carro = 0;
    int id = 0;
    double precio = 0.0;
    int existencias = 0;
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

    // Omitir encabezado
    if (!getline(file, linea)) {
        cerr << "Error: Archivo vacio o falta encabezado: " << archivo << endl;
        file.close();
        return -1;
    }

    // Contar lineas restantes para determinar la cantidad de vehiculos
    int cantidad = 0;
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

        getline(ss, vehiculos[i].modelo, ',');
        getline(ss, vehiculos[i].marca, ',');
        getline(ss, vehiculos[i].placa, ',');
        getline(ss, vehiculos[i].color, ',');
        if (getline(ss, temp, ',')) vehiculos[i].ano = stoi(temp);
        if (getline(ss, temp, ',')) vehiculos[i].kilometraje = stoi(temp);
        if (getline(ss, temp, ',')) vehiculos[i].rentado = (temp == "1");
        getline(ss, vehiculos[i].motor, ',');
        if (getline(ss, temp, ',')) vehiculos[i].precio_renta = stod(temp);
        getline(ss, vehiculos[i].ced_cliente, ',');
        getline(ss, vehiculos[i].fecha_de_entrega);

        i++;
    }

    file.close();
    return cantidad;
}

// Funcion para escribir vehiculos en csv
void escribirVehiculos(const string& archivo, Vehiculo* vehiculos, int cantidad) {
    ofstream file(archivo, ios::trunc); // Limpiar el archivo antes de escribir
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para escribir los vehiculos." << endl;
        return;
    }

    // Escribir encabezado
    file << "modelo,marca,placa,color,ano,kilometraje,rentado,motor,precio_renta,ced_cliente,fecha_de_entrega\n";

    // Escribir datos de cada vehiculo
    for (int i = 0; i < cantidad; ++i) {
        if (!vehiculos[i].placa.empty()) { // Validar que la placa no este vacia
            file << vehiculos[i].modelo << ","
                 << vehiculos[i].marca << ","
                 << vehiculos[i].placa << ","
                 << vehiculos[i].color << ","
                 << vehiculos[i].ano << ","
                 << vehiculos[i].kilometraje << ","
                 << (vehiculos[i].rentado ? "1" : "0") << ","
                 << vehiculos[i].motor << ","
                 << vehiculos[i].precio_renta << ","
                 << vehiculos[i].ced_cliente << ","
                 << vehiculos[i].fecha_de_entrega << "\n";
        }
    }

    file.close();
}


// Funcion para insertar nuevo vehiculo
void insertarVehiculo(Vehiculo*& vehiculos, int& cantidad) {
    Vehiculo nuevo;
    cout << "Ingrese los detalles del nuevo vehiculo:" << endl;

    cout << "Modelo: ";
    getline(cin >> ws, nuevo.modelo); // "ws" Se utiliza para eliminar espacios en blanco residuales

    cout << "Marca: ";
    getline(cin >> ws, nuevo.marca);

    cout << "Placa: ";
    getline(cin >> ws, nuevo.placa);

    cout << "Color: ";
    getline(cin >> ws, nuevo.color);

    cout << "Ano: ";
    cin >> nuevo.ano;

    cout << "Kilometraje: ";
    cin >> nuevo.kilometraje;

    cout << "Rentado (1 para Si, 0 para No): ";
    cin >> nuevo.rentado;

    cout << "Motor: ";
    getline(cin >> ws, nuevo.motor);

    cout << "Precio de Renta: ";
    cin >> nuevo.precio_renta;

    cout << "Cedula Cliente: ";
    getline(cin >> ws, nuevo.ced_cliente);

    cout << "Fecha de Entrega: ";
    getline(cin >> ws, nuevo.fecha_de_entrega);

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

// Funcion para mostrar todos los vehiculos
void mostrarVehiculos(Vehiculo* vehiculos, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cout << "Vehiculo " << i + 1 << ": " << vehiculos[i].modelo << ", " << vehiculos[i].marca
             << ", " << vehiculos[i].placa << ", " << vehiculos[i].color << ", " << vehiculos[i].ano
             << ", " << vehiculos[i].kilometraje << ", " << (vehiculos[i].rentado ? "Si" : "No") << ", "
             << vehiculos[i].motor << ", " << vehiculos[i].precio_renta << ", "
             << vehiculos[i].ced_cliente << ", " << vehiculos[i].fecha_de_entrega << endl;
    }
}

// Funcion para buscar vehiculo por placa
int buscarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa) {
    for (int i = 0; i < cantidad; ++i) {
        if (vehiculos[i].placa == placa) {
            return i;
        }
    }
    return -1;
}

// Funcion para editar vehiculo por placa
void editarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa) {
    int index = buscarVehiculo(vehiculos, cantidad, placa);
    if (index == -1) {
        cout << "Vehiculo no encontrado." << endl;
        return;
    }

    cout << "Editar datos del vehiculo (Escriba -1 para no modificar):" << endl;

    cout << "Modelo (" << vehiculos[index].modelo << "): ";
    string modelo;
    getline(cin >> ws, modelo); 
    if (modelo != "-1") vehiculos[index].modelo = modelo;

    cout << "Marca (" << vehiculos[index].marca << "): ";
    string marca;
    getline(cin >> ws, marca);
    if (marca != "-1") vehiculos[index].marca = marca;

    cout << "Placa (" << vehiculos[index].placa << "): ";
    string nuevaPlaca;
    getline(cin >> ws, nuevaPlaca);
    if (nuevaPlaca != "-1") vehiculos[index].placa = nuevaPlaca;

    cout << "Color (" << vehiculos[index].color << "): ";
    string color;
    getline(cin >> ws, color);
    if (color != "-1") vehiculos[index].color = color;

    cout << "Ano (" << vehiculos[index].ano << "): ";
    int ano;
    cin >> ano;
    if (ano != -1) vehiculos[index].ano = ano;

    cout << "Kilometraje (" << vehiculos[index].kilometraje << "): ";
    int kilometraje;
    cin >> kilometraje;
    if (kilometraje != -1) vehiculos[index].kilometraje = kilometraje;

    cout << "Rentado (1 para Si, 0 para No) (" << vehiculos[index].rentado << "): ";
    int rentado;
    cin >> rentado;
    if (rentado != -1) vehiculos[index].rentado = rentado;

    cout << "Motor (" << vehiculos[index].motor << "): ";
    string motor;
    getline(cin >> ws, motor);
    if (motor != "-1") vehiculos[index].motor = motor;

    cout << "Precio de Renta (" << vehiculos[index].precio_renta << "): ";
    double precioRenta;
    cin >> precioRenta;
    if (precioRenta != -1) vehiculos[index].precio_renta = precioRenta;

    cout << "Cedula Cliente (" << vehiculos[index].ced_cliente << "): ";
    string cedCliente;
    getline(cin >> ws, cedCliente);
    if (cedCliente != "-1") vehiculos[index].ced_cliente = cedCliente;

    cout << "Fecha de Entrega (" << vehiculos[index].fecha_de_entrega << "): ";
    string fechaEntrega;
    getline(cin >> ws, fechaEntrega);
    if (fechaEntrega != "-1") vehiculos[index].fecha_de_entrega = fechaEntrega;

    cout << "Datos del vehiculo actualizados exitosamente." << endl;
}

// Funcion para eliminar vehiculo por placa
void eliminarVehiculo(Vehiculo*& vehiculos, int& cantidad, const string& placa) {
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

// FUNCIONES DE CLIENTES ----------------------------------------------------------------------------------

// Funcion para leer clientes desde csv
int leerClientes(const string& archivo, Cliente*& clientes) {
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
    int cantidad = 0;
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

        getline(ss, clientes[i].cedula, ',');
        getline(ss, clientes[i].nombre, ',');
        getline(ss, clientes[i].apellido, ',');
        getline(ss, clientes[i].email, ',');
        if (getline(ss, temp, ',')) clientes[i].cantidad_vehiculos_rentados = stoi(temp);
        getline(ss, clientes[i].direccion, ',');
        if (getline(ss, temp, ',')) clientes[i].activo = (temp == "1");

        i++;
    }

    file.close();
    return cantidad;
}

// Funcion para escribir clientes en csv
void escribirClientes(const string& archivo, Cliente* clientes, int cantidad) {
    ofstream file(archivo, ios::trunc); // Limpiar el archivo antes de escribir
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para escribir los clientes." << endl;
        return;
    }

    // Escribir encabezado
    file << "cedula,nombre,apellido,email,cantidad_vehiculos_rentados,direccion,activo\n";

    // Escribir datos de cada cliente
    for (int i = 0; i < cantidad; ++i) {
        if (!clientes[i].cedula.empty()) { // Validar que la cedula no este vacia
            file << clientes[i].cedula << ","
                 << clientes[i].nombre << ","
                 << clientes[i].apellido << ","
                 << clientes[i].email << ","
                 << clientes[i].cantidad_vehiculos_rentados << ","
                 << clientes[i].direccion << ","
                 << (clientes[i].activo ? "1" : "0") << "\n";
        }
    }

    file.close();
}

// Funcion para insertar nuevo cliente
void insertarCliente(Cliente*& clientes, int& cantidad) {
    Cliente nuevo;
    cout << "Ingrese los detalles del nuevo cliente:" << endl;

    cout << "Cedula: ";
    getline(cin >> ws, nuevo.cedula);

    cout << "Nombre: ";
    getline(cin >> ws, nuevo.nombre);

    cout << "Apellido: ";
    getline(cin >> ws, nuevo.apellido);

    cout << "Email: ";
    getline(cin >> ws, nuevo.email);

    cout << "Cantidad de Vehiculos Rentados: ";
    cin >> nuevo.cantidad_vehiculos_rentados;

    cout << "Direccion: ";
    getline(cin >> ws, nuevo.direccion);

    cout << "Activo (1 para Si, 0 para No): ";
    cin >> nuevo.activo;

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
void mostrarClientes(Cliente* clientes, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cout << "Cliente " << i + 1 << ": " << clientes[i].cedula << ", " << clientes[i].nombre << ", "
             << clientes[i].apellido << ", " << clientes[i].email << ", "
             << clientes[i].cantidad_vehiculos_rentados << ", " << clientes[i].direccion << ", "
             << (clientes[i].activo ? "Activo" : "Inactivo") << endl;
    }
}

// Funcion para buscar cliente por cedula
int buscarCliente(Cliente* clientes, int cantidad, const string& cedula) {
    for (int i = 0; i < cantidad; ++i) {
        if (clientes[i].cedula == cedula) {
            return i;
        }
    }
    return -1;
}

// Funcion para editar datos de un cliente por cedula
void editarCliente(Cliente* clientes, int cantidad, const string& cedula) {
    int index = buscarCliente(clientes, cantidad, cedula);
    if (index == -1) {
        cout << "Cliente no encontrado." << endl;
        return;
    }

    cout << "Editar datos del cliente (Escriba -1 para no modificar):" << endl;
    cout << "Cedula (" << clientes[index].cedula << "): ";
    string nuevaCedula;
    getline(cin >> ws, nuevaCedula);
    if (nuevaCedula != "-1") clientes[index].cedula = nuevaCedula;

    cout << "Nombre (" << clientes[index].nombre << "): ";
    string nombre;
    getline(cin >> ws, nombre);
    if (nombre != "-1") clientes[index].nombre = nombre;

    cout << "Apellido (" << clientes[index].apellido << "): ";
    string apellido;
    getline(cin >> ws, apellido);
    if (apellido != "-1") clientes[index].apellido = apellido;

    cout << "Email (" << clientes[index].email << "): ";
    string email;
    getline(cin >> ws, email);
    if (email != "-1") clientes[index].email = email;

    cout << "Direccion (" << clientes[index].direccion << "): ";
    string direccion;
    getline(cin >> ws, direccion);
    if (direccion != "-1") clientes[index].direccion = direccion;

    cout << "Cantidad de Vehiculos Rentados (" << clientes[index].cantidad_vehiculos_rentados << "): ";
    int cantidad_rentados;
    cin >> cantidad_rentados;
    if (cantidad_rentados != -1) clientes[index].cantidad_vehiculos_rentados = cantidad_rentados;

    cout << "Activo (1 para Si, 0 para No) (" << clientes[index].activo << "): ";
    int activo;
    cin >> activo;
    if (activo != -1) clientes[index].activo = activo;

    cout << "Datos del cliente actualizados exitosamente." << endl;
}

// Funcion para eliminar cliente por cedula
void eliminarCliente(Cliente*& clientes, int& cantidad, const string& cedula) {
    int index = buscarCliente(clientes, cantidad, cedula);
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

// FUNCIONES DE REPUESTOS ----------------------------------------------------------------------------------

// Funcion para leer repuestos desde csv
int leerRepuestos(const string& archivo, Repuesto*& repuestos) {
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
    int cantidad = 0;
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

            ss >> repuestos[i].id;
            ss.ignore(1); // Omitir coma
            getline(ss, repuestos[i].modelo, ',');
            getline(ss, repuestos[i].marca, ',');
            getline(ss, repuestos[i].nombre, ',');
            getline(ss, repuestos[i].modelo_carro, ',');
            if (getline(ss, temp, ',')) repuestos[i].ano_carro = stoi(temp);
            if (getline(ss, temp, ',')) repuestos[i].precio = stod(temp);
            if (getline(ss, temp, ',')) repuestos[i].existencias = stoi(temp);

            i++;
        }
    }

    file.close();
    return cantidad;
}

// Funcion para escribir repuestos en csv
void escribirRepuestos(const string& archivo, Repuesto* repuestos, int cantidad) {
    ofstream file(archivo, ios::trunc); // Abrir en modo truncado para limpiar el archivo existente
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para escribir los repuestos." << endl;
        return;
    }

    // Escribir encabezado
    file << "id,modelo,marca,nombre,modelo_carro,ano_carro,precio,existencias\n";

    for (int i = 0; i < cantidad; ++i) {
        if (repuestos[i].id != 0) {
            file << repuestos[i].id << ","
                 << repuestos[i].modelo << ","
                 << repuestos[i].marca << ","
                 << repuestos[i].nombre << ","
                 << repuestos[i].modelo_carro << ","
                 << repuestos[i].ano_carro << ","
                 << repuestos[i].precio << ","
                 << repuestos[i].existencias << "\n";
        }
    }

    file.close();
}

// Funcion para insertar repuestos en csv
void insertarRepuesto(Repuesto*& repuestos, int& cantidad) {
    Repuesto nuevo;
    nuevo.id = (cantidad == 0) ? 1 : repuestos[cantidad - 1].id + 1; // Generar id unico

    cout << "Ingrese los detalles del nuevo repuesto:" << endl;

    cout << "Modelo: ";
    getline(cin >> ws, nuevo.modelo);

    cout << "Marca: ";
    getline(cin >> ws, nuevo.marca);

    cout << "Nombre: ";
    getline(cin >> ws, nuevo.nombre);

    cout << "Modelo del Carro: ";
    getline(cin >> ws, nuevo.modelo_carro);

    cout << "Ano del Carro: ";
    cin >> nuevo.ano_carro;

    cout << "Precio: ";
    cin >> nuevo.precio;

    cout << "Existencias: ";
    cin >> nuevo.existencias;

    Repuesto* nuevoArray = new Repuesto[cantidad + 1];
    for (int i = 0; i < cantidad; ++i) {
        nuevoArray[i] = repuestos[i];
    }
    nuevoArray[cantidad] = nuevo;
    delete[] repuestos;
    repuestos = nuevoArray;
    cantidad++;

    cout << "Repuesto agregado correctamente con ID: " << nuevo.id << endl;
}


// Funcion para mostrar todos los repuestos
void mostrarRepuestos(Repuesto* repuestos, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cout << "Repuesto ID: " << repuestos[i].id << ", " << repuestos[i].modelo << ", " << repuestos[i].marca << ", "
             << repuestos[i].nombre << ", " << repuestos[i].modelo_carro << ", "
             << repuestos[i].ano_carro << ", " << repuestos[i].precio << ", "
             << repuestos[i].existencias << endl;
    }
}

// Funcion para buscar repuesto por id
int buscarRepuesto(Repuesto* repuestos, int cantidad, int id) {
    for (int i = 0; i < cantidad; ++i) {
        if (repuestos[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Funcion para editar repuesto por id
void editarRepuesto(Repuesto* repuestos, int cantidad, int id) {
    int index = buscarRepuesto(repuestos, cantidad, id);
    if (index == -1) {
        cout << "Repuesto no encontrado." << endl;
        return;
    }

    cout << "Editar datos del repuesto (deje en blanco para no modificar):" << endl;
    cout << "ID (" << repuestos[index].id << "): ";
    int nuevoId;
    cin >> nuevoId;
    if (nuevoId != -1) repuestos[index].id = nuevoId;

    cout << "Modelo (" << repuestos[index].modelo << "): ";
    string modelo;
    getline(cin >> ws, modelo);
    if (modelo != "-1") repuestos[index].modelo = modelo;

    cout << "Marca (" << repuestos[index].marca << "): ";
    string marca;
    getline(cin >> ws, marca);
    if (marca != "-1") repuestos[index].marca = marca;

    cout << "Nombre (" << repuestos[index].nombre << "): ";
    string nombre;
    getline(cin >> ws, nombre);
    if (nombre != "-1") repuestos[index].nombre = nombre;

    cout << "Modelo del Carro (" << repuestos[index].modelo_carro << "): ";
    string modelo_carro;
    getline(cin >> ws, modelo_carro);
    if (modelo_carro != "-1") repuestos[index].modelo_carro = modelo_carro;

    cout << "Ano del Carro (" << repuestos[index].ano_carro << "): ";
    int ano_carro;
    cin >> ano_carro;
    if (ano_carro != -1) repuestos[index].ano_carro = ano_carro;

    cout << "Precio (" << repuestos[index].precio << "): ";
    double precio;
    cin >> precio;
    if (precio != -1 && precio != -1.00) repuestos[index].precio = precio;

    cout << "Existencias (" << repuestos[index].existencias << "): ";
    int existencias;
    cin >> existencias;
    if (existencias != -1) repuestos[index].existencias = existencias;

    cout << "Datos del repuesto actualizados exitosamente." << endl;
}


// Funcion para eliminar repuesto por id
void eliminarRepuesto(Repuesto*& repuestos, int& cantidad, int id) {
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