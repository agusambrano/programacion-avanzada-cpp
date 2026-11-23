// Ejercicio 2: Empleado, Docente y Administrativo (un arreglo de punteros a la base)
//
// Completa los metodos marcados con TODO. No cambies las firmas ni el main().
//
// Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio2 ejercicio2_planilla_empleados.cpp
// Ejecutar: ./ejercicio2
//
// Salida esperada:
// Pago 0: 1500
// Pago 1: 1800
// Pago 2: 1200
// Total de la planilla: 4500

#include <iostream>

class Empleado {
private:
    double sueldoBase;
public:
    Empleado(double s) {
        sueldoBase = s;
    }
    Empleado() {
        sueldoBase = 0;
    }
    void setSueldoBase(double s) {
        sueldoBase = s;
    }
    virtual ~Empleado() {}
    double getSueldoBase() {
        return sueldoBase;
    }
    virtual double calcularPago() {
        return sueldoBase;
    }
};

class Docente : public Empleado {
private:
    int horasExtra;
public:
    Docente(double s, int h) {
        setSueldoBase(s);
        horasExtra = h;
    }
    double calcularPago() override {
        return getSueldoBase() + horasExtra * 25;
    }
};

class Administrativo : public Empleado {
private:
    double bono;
public:
    Administrativo(double s, double b) {
        setSueldoBase(s);
        bono = b;
    }
    double calcularPago() override {
        return getSueldoBase() + bono;
    }
};

double totalPlanilla(Empleado* planilla[], int cantidad) {
    double total = 0;
    for (int i = 0; i < cantidad; i++) {
        total += planilla[i]->calcularPago();
    }
    return total;
}

int main() {
    Empleado conserje(1500);
    Docente docente(1400, 16);
    Administrativo secretaria(1000, 200);

    Empleado* planilla[3] = {&conserje, &docente, &secretaria};
    for (int i = 0; i < 3; i++) {
        std::cout << "Pago " << i << ": " << planilla[i]->calcularPago() << std::endl;
    }
    std::cout << "Total de la planilla: " << totalPlanilla(planilla, 3) << std::endl;
    return 0;
}