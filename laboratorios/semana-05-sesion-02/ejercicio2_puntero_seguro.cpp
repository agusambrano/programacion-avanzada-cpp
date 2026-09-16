#include <iostream>

int* obtenerLecturaSegura(int valorSensor) {
    int* lectura = new int(valorSensor * 2);
    return lectura;
}

int main() {
    int* resultado = obtenerLecturaSegura(10);
    std::cout << "Lectura: " << *resultado << std::endl;
    delete resultado;
    resultado = nullptr;

    return 0;
}
