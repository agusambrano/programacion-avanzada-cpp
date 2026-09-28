#include <iostream>
#include <memory>
#include <utility>

// ---------- Bateria: ya la conoces (encapsulacion, invariante con setter que devuelve bool) ----------
class Bateria {
private:
    double capacidadMax;
    double cargaActual;

public:
    Bateria() {
        capacidadMax = 100.0;
        cargaActual = 100.0;
    }

    bool setCapacidad(double nuevaCapacidad) {
        if (nuevaCapacidad <= 0) {
            return false;
        }
        capacidadMax = nuevaCapacidad;
        cargaActual = nuevaCapacidad;
        return true;
    }

    bool descargar(double cantidad) {
        if (cantidad > cargaActual) {
            return false;
        }
        cargaActual = cargaActual - cantidad;
        return true;
    }

    void recargar() {
        cargaActual = capacidadMax;
    }

    double getCargaActual() {
        return cargaActual;
    }
};

class RegistroVuelo {
    double* alturas;
    int capacidad;
    int siguiente;

public:
    RegistroVuelo() {
        capacidad = 10;
        alturas = new double[capacidad];
        siguiente = 0;
        std::cout << "Registro de vuelo creado, capacidad " << capacidad << std::endl;
    }

    void agregar(double altura) {
        if (siguiente < capacidad) {
            alturas[siguiente++] = altura;
        } else {
            std::cout << "Registro lleno, no se puede agregar mas alturas" << std::endl;
        }
    }

    double getAltura(int indice) {
        if (alturas == nullptr) {
            std::cout << "Registro vacio (fue movido)" << std::endl;
            return 0.0;
        } else if (indice < 0 || indice >= siguiente) {
            std::cout << "Indice fuera de rango" << std::endl;
            return 0.0;
        } else {
            return alturas[indice];
        }
    }
    RegistroVuelo(RegistroVuelo&& otro) {
        alturas = otro.alturas;
        capacidad = otro.capacidad;
        siguiente = otro.siguiente;
        otro.alturas = nullptr;
        otro.capacidad = 0;
        otro.siguiente = 0;
    }

    RegistroVuelo& operator=(RegistroVuelo&& otro) {
        if (this != &otro) {
            delete[] alturas;
            alturas = otro.alturas;
            capacidad = otro.capacidad;
            siguiente = otro.siguiente;
            otro.alturas = nullptr;
            otro.capacidad = 0;
            otro.siguiente = 0;
        }
        return *this;
    }

    ~RegistroVuelo() {
        delete[] alturas;
        std::cout << "Destruyendo registro de vuelo (capacidad " << capacidad << ")" << std::endl;
    }
};


// ---------- Aeronave: ya la conoces (base de una jerarquia con herencia publica) ----------
class Aeronave {
private:
    int id;
    double altitud;

public:
    Aeronave() {
        id = 0;
        altitud = 0.0;
    }

    void setId(int nuevoId) {
        id = nuevoId;
    }

    int getId() {
        return id;
    }

    bool despegar(double altitudCrucero) {
        if (altitudCrucero <= 0) {
            return false;
        }
        altitud = altitudCrucero;
        std::cout << "Aeronave " << id << " despega a " << altitud << " metros" << std::endl;
        return true;
    }

    void aterrizar() {
        altitud = 0.0;
        std::cout << "Aeronave " << id << " aterriza" << std::endl;
    }

    double getAltitud() {
        return altitud;
    }
};

class Dron : public Aeronave {
    Bateria bateria;
    RegistroVuelo registro;
    public:
    Dron(int id, double capacidadBateria) {
        setId(id);
        bateria.setCapacidad(capacidadBateria);
        bateria.recargar();
    }
    
    bool puedeDespegar(double consumoEstimado) {
        return bateria.getCargaActual() >= consumoEstimado;
    }

    bool realizarVuelo(double altitudCrucero, double consumoBateria) {
        if (!puedeDespegar(consumoBateria)) {
            std::cout << "Dron " << "Dron " << getId() << " no tiene carga suficiente" << std::endl;
            return false;
        }
        despegar(altitudCrucero);
        registro.agregar(altitudCrucero);
        bateria.descargar(consumoBateria);
        aterrizar();
        return true;
    }

    double getAltitudRegistrada(int indice) {
        return registro.getAltura(indice);
    }

    double getCargaActual() {
        return bateria.getCargaActual();
    }
};

// ---------- TorreControl: ya la conoces (recurso que varias Estacion van a compartir) ----------
class TorreControl {
private:
    int totalDespachos;

public:
    TorreControl() {
        totalDespachos = 0;
        std::cout << "Torre de control creada" << std::endl;
    }

    void registrarDespacho() {
        totalDespachos = totalDespachos + 1;
    }

    int getTotalDespachos() {
        return totalDespachos;
    }

    ~TorreControl() {
        std::cout << "Destruyendo torre de control (" << totalDespachos << " despachos)" << std::endl;
    }
};

class Estacion {
private:
    int idEstacion;
    std::unique_ptr<Dron> dronAsignado;
    std::shared_ptr<TorreControl> torre;

public:
    Estacion(int id, std::shared_ptr<TorreControl> torreCompartida) {
        idEstacion = id;
        torre = torreCompartida;
        std::cout << "Estacion " << id << " conectada a la torre, use_count = " << torre.use_count() << std::endl;
    }

    void asignarDron(std::unique_ptr<Dron> dron) {
        dronAsignado = std::move(dron);
        torre->registrarDespacho();
        std::cout << "Estacion " << idEstacion << " recibe el dron " << dronAsignado->getId() << std::endl;
    }

    std::unique_ptr<Dron> liberarDron() {
        std::cout << "Estacion " << idEstacion << " libera su dron" << std::endl;
        return std::move(dronAsignado);
    }

    bool tieneDron() {
        return dronAsignado != nullptr;
    }

    Dron* verDron() {
        return dronAsignado.get();
    }
};

int main() {
    // Demostracion directa de RAII + move semantics sobre RegistroVuelo,
    // independiente de cualquier smart pointer: mueve el objeto por valor.
    RegistroVuelo registroTemporal;
    registroTemporal.agregar(999.0);

    // Crear el registro final moviendo el registro temporal a registroFinal
    RegistroVuelo registroFinal(std::move(registroTemporal));
    std::cout << "registroFinal.getAltura(0): " << registroFinal.getAltura(0) << std::endl;
    std::cout << "registroTemporal tras moverlo: ";
    registroTemporal.getAltura(0);

    // Crear la primera torre de control como un puntero compartido
    auto torre = std::make_shared<TorreControl>();
    std::cout << "use_count inicial: " << "use_count inicial: " << torre.use_count() << std::endl;

    Estacion base1(1, torre);
    Estacion base2(2, torre);

    std::cout << "use_count tras conectar 2 estaciones: " << torre.use_count() << std::endl;

    // Crear dron1 como un puntero unico con los valores (101, 80.0)
    auto dron1 = std::make_unique<Dron>(101, 80.0);

    dron1->realizarVuelo(120.0, 15.0);
    base1.asignarDron(std::move(dron1));


    if (base1.tieneDron()) {
        base1.verDron()->realizarVuelo(150.0, 20.0);
        std::cout << "Altitud registrada [0]: " << base1.verDron()->getAltitudRegistrada(0) << std::endl;
        std::cout << "Altitud registrada [1]: " << base1.verDron()->getAltitudRegistrada(1) << std::endl;
    }

    auto dronTransferido = base1.liberarDron();
    std::cout << "base1 tiene dron tras liberar: " << base1.tieneDron() << std::endl;

    base2.asignarDron(std::move(dronTransferido));

    if (base2.tieneDron()) {
        base2.verDron()->realizarVuelo(100.0, 10.0);
        std::cout << "Carga restante en base2: " << base2.verDron()->getCargaActual() << std::endl;
        std::cout << "Altitud registrada [0] tras la transferencia: "
                   << base2.verDron()->getAltitudRegistrada(0) << std::endl;
    }

    std::cout << "Total despachos registrados por la torre: " << torre->getTotalDespachos() << std::endl;

    return 0;
}
