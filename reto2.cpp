//reto2

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Vehiculo {
protected:
    string marca;
    string modelo;
    int anio;
    double precioBase;

public:
    Vehiculo(const string& marca, const string& modelo, int anio, double precioBase)
        : marca(marca), modelo(modelo), anio(anio), precioBase(precioBase) {}

    virtual ~Vehiculo() {}                           // destructor virtual
    virtual double calcularPrecioFinal() const {     // base: sin impuesto
        return precioBase;
    }

    string getMarca()  const { return marca; }
    string getModelo() const { return modelo; }
    int    getAnio()   const { return anio; }
};

class Auto : public Vehiculo {
    int numeroPuertas;

public:
    Auto(const string& marca, const string& modelo, int anio, double precioBase, int numeroPuertas)
        : Vehiculo(marca, modelo, anio, precioBase), numeroPuertas(numeroPuertas) {}

    double calcularPrecioFinal() const override {    // impuesto 15%
        return precioBase * 1.15;
    }
};

class Moto : public Vehiculo {
    int cilindrada;

public:
    Moto(const string& marca, const string& modelo, int anio, double precioBase, int cilindrada)
        : Vehiculo(marca, modelo, anio, precioBase), cilindrada(cilindrada) {}

    double calcularPrecioFinal() const override {    // impuesto 10%
        return precioBase * 1.10;
    }
};

int main() {
    vector<Vehiculo*> flota;
    flota.push_back(new Auto("Toyota", "Corolla", 2023, 25000.0, 4));
    flota.push_back(new Moto("Yamaha", "MT-07", 2022, 8000.0, 689));

    cout << fixed << setprecision(2);
    for (Vehiculo* v : flota) {
        cout << v->getMarca() << " " << v->getModelo()
             << " (" << v->getAnio() << ") -> $"
             << v->calcularPrecioFinal() << '\n';
    }

    for (Vehiculo* v : flota) delete v;
    return 0;
}
