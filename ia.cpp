using namespace std;
#include <vector>

class IA {
private:
    int x, y;

public:
    IA(vector<vector<char>>& tablero);
    void mover(vector<vector<char>>& tablero,bool tiene_movimientos);
};

vector<pair<int,int>> movimientos ={
    {1,0}, //abajo
    {-1,0}, //arriba
    {0,1}, //derecha
    {0,-1}, //izquierda
};

IA::IA(vector<vector<char>>& tablero) {
    auto pos = encontrar_posicion(tablero,'A');
    x = pos.first;
    y = pos.second;
}
Laberinto lab ;

void IA::mover(vector<vector<char>>& tablero,bool tiene_movimientos) {
    // movimiento dummy (después metés BFS, A*, etc)
    for(auto[dx,dy] : movimientos){
        int nx = x + dx;
        int ny = y + dy;
            if(lab.es_valido(nx,ny)){
                tiene_movimientos = true;
                tablero[x][y] = ' ';
                x = nx;
                y = ny;
                tablero[x][y] = 'A';
            break;
            }
    }
}