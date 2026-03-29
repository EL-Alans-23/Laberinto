#include <iostream>
#include "utilidades.cpp"
#include "laberinto.cpp"
#include "ia.cpp"


int main() {
    Laberinto lab;

    lab.cargarMapa("data/mapa.txt");
    lab.mostrar();
    auto& tablero = lab.obtenerMapa();
    IA agente(tablero);

    // loop básico
    while (!lab.metaAlcanzada()) {
        agente.mover(tablero,false);
        lab.mostrar();
    }

    std::cout << "Llegó a la meta!" << std::endl;
    return 0;
}