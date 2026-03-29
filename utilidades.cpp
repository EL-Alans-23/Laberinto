#include <iostream>
#include <cstdlib>
#include <vector>

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