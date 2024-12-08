#ifndef REPUESTO_H // Evitar que sea procesado varias veces
#define REPUESTO_H

#include <string>
using namespace std;

class Repuesto {
private:
    int id;
    string modelo;
    string marca;
    string nombre;
    string modelo_carro;
    int ano_carro;
    double precio;
    int existencias;

public:
    Repuesto();

    // gets y sets
    int getId() const;
    void setId(int id);

    string getModelo() const;
    void setModelo(const string& modelo);

    string getMarca() const;
    void setMarca(const string& marca);

    string getNombre() const;
    void setNombre(const string& nombre);

    string getModeloCarro() const;
    void setModeloCarro(const string& modelo_carro);

    int getAnoCarro() const;
    void setAnoCarro(int ano_carro);

    double getPrecio() const;
    void setPrecio(double precio);

    int getExistencias() const;
    void setExistencias(int existencias);

    // Funciones repuestos
    static int leerRepuestos(const string& archivo, Repuesto*& repuestos, int& cantidad);
    static void escribirRepuestos(const string& archivo, Repuesto* repuestos, int cantidad);
    static void insertarRepuesto(Repuesto*& repuestos, int& cantidad);
    static void mostrarRepuestos(Repuesto* repuestos, int cantidad);
    static int buscarRepuesto(Repuesto* repuestos, int cantidad, int id);
    static void editarRepuesto(Repuesto* repuestos, int cantidad, int id);
    static void eliminarRepuesto(Repuesto*& repuestos, int& cantidad, int id);
};

#endif // Final de ifndef
