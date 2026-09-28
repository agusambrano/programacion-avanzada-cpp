// Ejercicio 3: Volador, Nadador y VehiculoAnfibio (herencia multiple)
//
// Completa los metodos marcados con TODO. No cambies las firmas ni el main().
//
// Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio3 ejercicio3_volador_nadador_anfibio.cpp
// Ejecutar: ./ejercicio3
//
// Salida esperada:
// Altitud maxima: 3000
// Profundidad maxima: 50
// Tripulantes: 6

#include <iostream>

class Volador {
private:
    double altitudMaxima;
public:
    bool setAltitudMaxima(double a) {
        if (a > 0 and a <= 15000) {
            altitudMaxima = a;
            return true;
        }
        return false;
    }
    double getAltitudMaxima() {
        return altitudMaxima;
    }
};

class Nadador {
private:
    double profundidadMaxima;
public:
    bool setProfundidadMaxima(double p) {
        if (p > 0 and p <= 300) {
            profundidadMaxima = p;
            return true;
        }
        return false;
    }
    double getProfundidadMaxima() {
        return profundidadMaxima;
    }
};

class VehiculoAnfibio : public Volador, public Nadador {
private:
    int numeroTripulantes;
public:
    bool setNumeroTripulantes(int n) {
        if (n > 0 and n <= 20) {
            numeroTripulantes = n;
            return true;
        }
        return false;
    }
    int getNumeroTripulantes() {
        return numeroTripulantes;
    }
};

int main() {
    VehiculoAnfibio v1;
    v1.setAltitudMaxima(3000);
    v1.setProfundidadMaxima(50);
    v1.setNumeroTripulantes(6);
    std::cout << "Altitud maxima: " << v1.getAltitudMaxima() << std::endl;
    std::cout << "Profundidad maxima: " << v1.getProfundidadMaxima() << std::endl;
    std::cout << "Tripulantes: " << v1.getNumeroTripulantes() << std::endl;
    return 0;
}
