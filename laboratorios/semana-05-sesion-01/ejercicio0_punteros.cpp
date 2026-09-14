#include <iostream>
using namespace std;

int main() {
    int numero = 10;
    int* ptr_numero = &numero;

    std::cout << "Dirección de memoria de numero: " << ptr_numero << std::endl;
    std::cout << "Valor de memoria desde el puntero: " << *ptr_numero << std::endl;
    std::cout << "valor memoria desde la variable: " << &ptr_numero << std::endl;

    int notas [5] = {80,90,60,50,71};
    int* ptr_notas = notas;

    ptr_notas += 1;

    std::cout << "El valor en la memoria desde el arreglo: " << *ptr_notas << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << "valor de memoria desde puntero " << *(ptr_notas + i) << std::endl;
    }

    return 0;
}