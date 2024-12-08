#ifndef VEHICULO_H // Evitar que sea procesado varias veces
#define VEHICULO_H

#include <string>
#include <iostream>

using namespace std;

class Vehiculo {
private:
    string modelo;
    string marca;
    string placa;
    string color;
    int ano;
    int kilometraje;
    bool rentado;
    string motor;
    double precio_renta;
    string ced_cliente;
    string fecha_de_entrega;

public:
    Vehiculo();

    // Gets y sets
    string getModelo() const;
    void setModelo(const string& m);

    string getMarca() const;
    void setMarca(const string& m);

    string getPlaca() const;
    void setPlaca(const string& p);

    string getColor() const;
    void setColor(const string& c);

    int getAno() const;
    void setAno(int a);

    int getKilometraje() const;
    void setKilometraje(int k);

    bool isRentado() const;
    void setRentado(bool r);

    string getMotor() const;
    void setMotor(const string& m);

    double getPrecioRenta() const;
    void setPrecioRenta(double p);

    string getCedCliente() const;
    void setCedCliente(const string& c);

    string getFechaDeEntrega() const;
    void setFechaDeEntrega(const string& f);

    // Funciones Vehiculos
    static int leerVehiculos(const string& archivo, Vehiculo*& vehiculos, int& cantidad);
    static void escribirVehiculos(const string& archivo, Vehiculo* vehiculos, int cantidad);
    static void mostrarVehiculos(Vehiculo* vehiculos, int cantidad);
    static void insertarVehiculo(Vehiculo*& vehiculos, int& cantidad);
    static int buscarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa);
    static void editarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa);
    static void eliminarVehiculo(Vehiculo*& vehiculos, int& cantidad, const string& placa);
};

#endif // Final de ifndef
