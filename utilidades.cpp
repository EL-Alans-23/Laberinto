#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

void limpiarPantalla();
void pausa();

void limpiarPantalla() {
    system("clear"); // o "cls" en Windows
}

pair <int,int> encontrar_posicion( vector<vector<char>>& tablero, char caracter){
    for (int i = 0; i < (int)tablero.size(); i++){
        for (int j = 0; j < (int)tablero[0].size(); j++){
            if (tablero[i][j] == caracter){
                return {i,j};
            }
        }
    }
    return {-1,-1};
}


string obtenerMapaRandom() {

    vector<string> archivos = {
        "data/mapa1.txt",
        "data/mapa2.txt",
        "data/mapa3.txt",
        "data/mapa4.txt",
        "data/mapa5.txt",
        "data/mapa6.txt",
        "data/mapa7.txt",
        "data/mapa8.txt",
        "data/mapa9.txt",
        "data/mapa10.txt"
    };

    int indice = rand() % archivos.size();
    return archivos[indice];
}