// Ejercicio 14: Teatro (at(), propagacion y orden de los catch)
//
// Completa los metodos marcados con TODO y el cuerpo de procesar. No
// cambies las firmas ni el main().
//
// Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio14 ejercicio14_teatro_at.cpp
// Ejecutar: ./ejercicio14
//
// Salida esperada:
// Compra aceptada: 3 asientos en la fila 1, total 45
// Rechazada (no existe): vector::_M_range_check: __n (which is 7) >= this->size() (which is 4)
// Rechazada (no existe): map::at
// Rechazada (dato invalido): cantidad no positiva
// Rechazada (no alcanza): asientos insuficientes
// Libres en la fila 1: 2
// Solicitudes procesadas: 5

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class Teatro {
private:
    std::vector<int> libresPorFila;
    std::map<int, double> precioPorZona;
public:
    Teatro() {
        libresPorFila = {10, 5, 8, 2};
        precioPorZona[1] = 15.0;
        precioPorZona[2] = 9.5;
    }
    int libresEn(int fila) {
        return libresPorFila.at(fila);
    }
    double precioDe(int zona) {
        return precioPorZona.at(zona);
    }
    double comprar(int fila, int zona, int cantidad) {
        int libres = libresEn(fila);
        double precio = precioDe(zona);

        if (cantidad <= 0) {
            throw std::invalid_argument("cantidad no positiva");
        }
        if (cantidad > libres) {
            throw std::runtime_error("asientos insuficientes");
        }

        libresPorFila.at(fila) -= cantidad;
        return cantidad * precio;
    }
};

void procesar(Teatro* teatro, int fila, int zona, int cantidad) {
    try {
        double total = teatro->comprar(fila, zona, cantidad);
        std::cout << "Compra aceptada: " << cantidad
                  << " asientos en la fila " << fila
                  << ", total " << total << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Rechazada (no existe): " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Rechazada (dato invalido): " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Rechazada (no alcanza): " << e.what() << std::endl;
    }
}

int main() {
    Teatro teatro;
    int solicitudes[5][3] = {{1, 1, 3}, {7, 1, 2}, {0, 4, 2}, {2, 2, 0}, {3, 2, 5}};
    for (int i = 0; i < 5; i++) {
        procesar(&teatro, solicitudes[i][0], solicitudes[i][1], solicitudes[i][2]);
    }
    std::cout << "Libres en la fila 1: " << teatro.libresEn(1) << std::endl;
    std::cout << "Solicitudes procesadas: 5" << std::endl;
    return 0;
}