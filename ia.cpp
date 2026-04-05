using namespace std;
#include <vector>
#include <queue>
#include <map>

class IA {
private:
    int x, y;

public:
    IA(vector<vector<char>>& tablero);
    void mover(vector<vector<char>>& tablero);
    struct Nodo{
    int x,y;};
    pair<int,int> BFS(vector<vector<char>>& tablero,int x,int y);
};
Laberinto lab;

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

void IA::mover(vector<vector<char>>& tablero) {

        auto [nx,ny] = BFS (tablero, x, y);
        tablero [x][y] = ' ';
        x = nx;
        y = ny;
        tablero [x][y] = 'A';
}

pair<int,int> IA::BFS(vector<vector<char>>& tablero, int x, int y){

    vector<vector<bool>> visitados(
    tablero.size(),
    vector<bool>(tablero[0].size(), false)
    );
    queue<Nodo> cola;

    // para guardar de dónde venimos
    map<pair<int,int>, pair<int,int>> padre;

    cola.push({x,y});
    visitados[x][y] = true;

    while(!cola.empty()){
        Nodo actual = cola.front();
        cola.pop();

        int cx = actual.x;
        int cy = actual.y;

        // si encontramos la meta
        if(tablero[cx][cy] == 'S'){
            // reconstruir camino (volver atrás)
            pair<int,int> pos = {cx, cy};

            while(padre[pos] != make_pair(x,y)){
                pos = padre[pos];
            }

            return pos; // siguiente paso
        }

        for(auto [dx,dy] : movimientos){
            int nx = cx + dx;
            int ny = cy + dy;

            if(lab.es_valido(nx,ny) && !visitados[nx][ny]){
                cola.push({nx,ny});
                visitados[nx][ny] = true;
                padre[{nx,ny}] = {cx,cy};
            }
        }
    }

    return {x,y}; // si no encuentra nada
}


