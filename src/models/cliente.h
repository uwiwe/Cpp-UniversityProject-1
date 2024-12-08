#ifndef CLIENTE_H // Evitar que sea procesado varias veces
#define CLIENTE_H

#include <string>
using namespace std;

class Cliente {
private:
    string cedula;
    string nombre;
    string apellido;
    string email;
    int cantidad_vehiculos_rentados;
    string direccion;
    bool activo;

public:
    Cliente();

    // Gets y sets
    string getCedula() const;
    void setCedula(const string& cedula);

    string getNombre() const;
    void setNombre(const string& nombre);

    string getApellido() const;
    void setApellido(const string& apellido);

    string getEmail() const;
    void setEmail(const string& email);

    int getCantidadVehiculosRentados() const;
    void setCantidadVehiculosRentados(int cantidad);

    string getDireccion() const;
    void setDireccion(const string& direccion);

    bool isActivo() const;
    void setActivo(bool activo);

    // Funciones clientes
    static int leerClientes(const string& archivo, Cliente*& clientes, int& cantidad);
    static void escribirClientes(const string& archivo, Cliente* clientes, int cantidad);
    static void insertarCliente(Cliente*& clientes, int& cantidad);
    static void mostrarClientes(Cliente* clientes, int cantidad);
    static int buscarCliente(Cliente* clientes, int cantidad, const string& cedula);
    static void editarCliente(Cliente* clientes, int cantidad, const string& cedula);
    static void eliminarCliente(Cliente*& clientes, int& cantidad, const string& cedula);
};

#endif // Final de ifndef
