#include <iostream>

// TODO: predice antes de compilar. ¿que advertencia esperas que de
// el compilador sobre esta funcion? 
// El compilador adevertira que se esta devolviendo la direccion de una variable local, porque lectura deja de existir cuando la funcion termina, y el puntero que se devuelve quedara colgando.
int* obtenerLecturaInsegura(int valorSensor) {
    int lectura = valorSensor * 2;
    return &lectura;
}

int main() {
    int* resultado = obtenerLecturaInsegura(10);
    std::cout << "Lectura (puntero colgante): " << *resultado << std::endl;
    return 0;
}
