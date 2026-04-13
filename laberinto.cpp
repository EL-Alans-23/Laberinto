#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;
using Tablero = vector<vector<char>>;
using Punto = pair<int,int>;

int N,M;
int FILAS;
int COLS;
const char PARED = '#';
const char CAMINO = ' ';
const char ENTRADA = 'E';
const char SALIDA = 'S';
const char SOLUCION = '*';
//direciones arriba, abajo, izquierda, derecha
const int DX[] = {0,0,-1,1};
const int DY[] = {-1,1,0,0};

// crear tablero inicial
Tablero crearLaberinto(){
    return Tablero(FILAS,vector<char>(COLS,PARED));  
}

//verificar los limites del tablero
bool validar_limites(int x, int y){
    return 0 < x && x < FILAS - 1 && 0 < y && y < COLS - 1;
}

// GENERACION DEL LABERINTO  (DFS + backtracking)
//  Idea: empezamos en la celda logica (1,1).
//  Nos movemos de 2 en 2 hacia un vecino no visitado,
//  derribando la pared del medio.
//  Usamos una pila para hacer backtracking.
void crear_laberinto(Tablero& tablero){
    // generador aleatorio con semilla de tiempo
    stack<Punto> pila;
    Punto inicio = {1,1};

    tablero[1][1] = CAMINO;
    pila.push(inicio);

    while (!pila.empty()){
        auto [x,y] = pila.top();
        vector<int> direc = {0,1,2,3};
        for (int i = 0; i < 4; i++){
            int j = rand()%4;
            swap(direc[i],direc[j]);
        }
            bool movio = false;

        for (int d:direc){
            int nx = x +DY[d]*2;
            int ny = y + DX[d]*2;

            if(validar_limites(nx,ny) && tablero[nx][ny] == PARED){
                tablero[x+DY[d]][y+DX[d]] = CAMINO;
                tablero[nx][ny] = CAMINO;
                pila.push({nx,ny});
                movio = true;
                break;
            }
        }
        // sin vecinos disponibles -> Backtrack
        if (!movio){
            pila.pop();
        }
    }
    tablero[1][1] = ENTRADA;
    tablero[FILAS - 2][COLS - 2] = SALIDA;
}

//Validar Movimiento para BFS
bool mov_valido(const Tablero& tablero, int x, int y){
    return 0 <= x && x < FILAS && 0 <= y && y < COLS && tablero[x][y] != PARED;
}

// Resolucion BFS
bool BFS(Tablero& tablero){
    Punto inicio = {1,1};
    Punto fin = {FILAS - 2, COLS - 2};

    //padre[x][y] = celda desde donde llegamos a {x,y}
    vector<vector<Punto>> padre(FILAS,vector<Punto>(COLS,{-1,-1}));
    vector<vector<bool>> visitado(FILAS, vector<bool>(COLS,false));

    queue<Punto> cola;
    cola.push(inicio);
    visitado[inicio.first][inicio.second] = true;

    bool encontrado = false;

    while(!cola.empty() && !encontrado){
        auto [x,y] = cola.front();
        cola.pop();
        for (int d = 0;d < 4; d++){
            int nx = x + DY[d];
            int ny = y + DX[d];

                if(mov_valido(tablero,nx,ny) && !visitado[nx][ny]){
                    visitado[nx][ny] = true;
                    padre[nx][ny] = {x,y};
                    cola.push({nx,ny});

                    if(nx == fin.first && ny == fin.second){
                        encontrado = true;
                        break;
                    }
                }
        }
    }
    if (!encontrado) return false;

    //reconstruir el camino desde FIN hasta INICIO
    Punto actual = fin;
    while (padre[actual.first][actual.second] != make_pair(-1,-1)){
        Punto prev = padre[actual.first][actual.second];

        //No sobreescribir S ni E
        if(tablero[actual.first][actual.second] != SALIDA && tablero[actual.first][actual.second] != ENTRADA){
            tablero[actual.first][actual.second] = SOLUCION;
        }
        actual = prev;
    }
    return true;
}

// Imprimir el tablero
void imprimir_laberinto(const Tablero& tablero, const string& titulo){
    cout<< "\n=== "<< titulo << "===\n\n";
    for (int x = 0; x < FILAS; x++){
        for (int y = 0; y < COLS; y++){
            cout<< tablero[x][y];
        }
        cout<< "\n";
    }
    cout<<"\n";
}

//Main
int main(){
    srand(time(0));
    cout<<"ingrese filas: ";
    cin>>N;
    cout<<"ingrese columnas: ";
    cin>>M;
    FILAS = 2 * N + 1;
    COLS = 2 * M + 1;
    cout << "Tamano logico: " << N << " x " << M << "\n";
    cout << "tamano real    : " << FILAS << " x " << COLS << "\n";
    cout << "S = SALIDA  E = ENTRADA  * = Solucion\n";
    //crear laberinto vacio (todas las paredes)
    Tablero laberinto = crearLaberinto();

    //generar laberinto con DFS
    crear_laberinto(laberinto);
    imprimir_laberinto(laberinto,"Laberinto generado");

    // Resolver con BFS
    bool resuelto = BFS(laberinto);

    if (resuelto){
        imprimir_laberinto(laberinto, "Laberinto Resuelto");
        cout<< "solucion encontrada\n";
    }
    else{
        cout<< "No tiene solucion\n";
    }
    return 0;
}
