#include <iostream>
#include "utilidades.cpp"
#include "laberinto.cpp"
#include "ia.cpp"

string obtenerMapaRandom();

int main() {

    srand(time(0));
    string archivo = obtenerMapaRandom();

    Laberinto lab;
    

    lab.cargarMapa(archivo);
    lab.mostrar();
    auto& tablero = lab.obtenerMapa();
    IA agente(tablero);

    cout<< "estado inicial" << endl;
    lab.mostrar();
    while (!lab.metaAlcanzada(tablero)) {
        agente.mover(tablero);
        lab.mostrar();
    }

    std::cout << "Llegó a la meta!" << std::endl;
    return 0;
}