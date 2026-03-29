#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Laberinto {
private:
    vector<vector<char>> mapa;
    int filas, columnas;

public:
    void cargarMapa(string ruta);
    void mostrar();

    bool es_valido(int x, int y);
    bool metaAlcanzada(vector<vector<char>>& tablero);

    vector<vector<char>>& obtenerMapa();
};

void Laberinto::cargarMapa(std::string ruta) {
    std::ifstream archivo(ruta);
    std::string linea;

    while (getline(archivo, linea)) {
        std::vector<char> fila(linea.begin(), linea.end());
        mapa.push_back(fila);
    }

    filas = mapa.size();
    columnas = mapa[0].size();
}

void Laberinto::mostrar() {
    for (auto& fila : mapa) {
        for (char c : fila) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

bool Laberinto::es_valido(int x, int y) {
    return x >= 0 && y >= 0 && x < filas && y < columnas && mapa[x][y] != '#';
}

bool Laberinto::metaAlcanzada(vector<vector<char>>& tablero) {
    
    if (encontrar_posicion(tablero,'A') == encontrar_posicion(tablero,'G'))
        return true;

    return false;
}

std::vector<std::vector<char>>& Laberinto::obtenerMapa() {
    return mapa;
}