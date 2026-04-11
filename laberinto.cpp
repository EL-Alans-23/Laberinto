/*
 * SISTEMA DE LABERINTOS EN C++
 * ─────────────────────────────
 * Generacion : DFS con backtracking (pila)
 * Resolucion : BFS (cola)
 *
 * Compilar: g++ -std=c++17 -o laberinto laberinto.cpp
 * Ejecutar: ./laberinto
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>   // shuffle
#include <random>      // mt19937
#include <utility>     // pair

using namespace std;

// ─────────────────────────────────────────────
//  CONFIGURACION GLOBAL
// ─────────────────────────────────────────────
const int N = 8;   // filas  logicas  → grid real: 2*N+1 = 17 filas
const int M = 14;  // columnas logicas → grid real: 2*M+1 = 29 cols

// La grid real tiene paredes en indices pares
// y celdas transitables en indices impares.
// Ejemplo con N=2, M=3  (grid 5x7):
//   # # # # # # #
//   #   #   #   #
//   # # # # # # #
//   #   #   #   #
//   # # # # # # #

const int FILAS = 2 * N + 1;
const int COLS  = 2 * M + 1;

// Caracteres usados en la grid
const char PARED    = '#';
const char CAMINO   = ' ';
const char INICIO   = 'S';
const char FIN      = 'E';
const char SOLUCION = '*';

// Direcciones: arriba, abajo, izquierda, derecha
const int DX[] = { 0,  0, -1,  1 };
const int DY[] = {-1,  1,  0,  0 };

// Tipo alias para comodidad
using Grid  = vector<vector<char>>;
using Punto = pair<int,int>;

// ─────────────────────────────────────────────
//  1. CREAR GRID INICIAL (todo paredes)
// ─────────────────────────────────────────────
Grid crearGrid() {
    return Grid(FILAS, vector<char>(COLS, PARED));
}

// ─────────────────────────────────────────────
//  2. VERIFICAR LIMITES
// ─────────────────────────────────────────────
bool dentroDelTablero(int r, int c) {
    return r > 0 && r < FILAS - 1
        && c > 0 && c < COLS  - 1;
}

// ─────────────────────────────────────────────
//  3. GENERACION DEL LABERINTO  (DFS + backtracking)
//
//  Idea: empezamos en la celda logica (1,1).
//  Nos movemos de 2 en 2 hacia un vecino no visitado,
//  derribando la pared del medio.
//  Usamos una pila para hacer backtracking.
// ─────────────────────────────────────────────
void generarLaberinto(Grid& grid) {
    // Generador aleatorio con semilla de tiempo
    mt19937 rng(random_device{}());

    stack<Punto> pila;
    Punto inicio = {1, 1};

    grid[1][1] = CAMINO;
    pila.push(inicio);

    while (!pila.empty()) {
        auto [r, c] = pila.top();

        // Barajar las 4 direcciones al azar
        vector<int> dirs = {0, 1, 2, 3};
        shuffle(dirs.begin(), dirs.end(), rng);

        bool movio = false;
        for (int d : dirs) {
            int nr = r + DY[d] * 2;   // vecino a 2 pasos
            int nc = c + DX[d] * 2;

            if (dentroDelTablero(nr, nc) && grid[nr][nc] == PARED) {
                // Derribar la pared intermedia
                grid[r + DY[d]][c + DX[d]] = CAMINO;
                // Marcar celda vecina como camino
                grid[nr][nc] = CAMINO;

                pila.push({nr, nc});
                movio = true;
                break;
            }
        }

        // Sin vecinos disponibles → backtrack
        if (!movio) pila.pop();
    }

    // Marcar entrada y salida
    grid[1][1]             = INICIO;
    grid[FILAS-2][COLS-2]  = FIN;
}

// ─────────────────────────────────────────────
//  4. VALIDAR MOVIMIENTO para BFS
//
//  Un movimiento es valido si:
//   - No sale del tablero
//   - La celda no es pared
// ─────────────────────────────────────────────
bool movimientoValido(const Grid& grid, int r, int c) {
    return r >= 0 && r < FILAS
        && c >= 0 && c < COLS
        && grid[r][c] != PARED;
}

// ─────────────────────────────────────────────
//  5. RESOLUCION  (BFS — camino mas corto)
//
//  Usamos una cola para explorar celdas
//  por niveles de distancia desde S.
//  Guardamos el "padre" de cada celda para
//  reconstruir el camino al llegar a E.
//
//  Devuelve true si encontro solucion.
// ─────────────────────────────────────────────
bool resolverBFS(Grid& grid) {
    Punto inicio = {1, 1};
    Punto fin    = {FILAS-2, COLS-2};

    // padre[r][c] = celda desde donde llegamos a (r,c)
    vector<vector<Punto>> padre(FILAS, vector<Punto>(COLS, {-1,-1}));
    vector<vector<bool>>  visitado(FILAS, vector<bool>(COLS, false));

    queue<Punto> cola;
    cola.push(inicio);
    visitado[inicio.first][inicio.second] = true;

    bool encontrado = false;

    while (!cola.empty() && !encontrado) {
        auto [r, c] = cola.front();
        cola.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + DY[d];
            int nc = c + DX[d];

            if (movimientoValido(grid, nr, nc) && !visitado[nr][nc]) {
                visitado[nr][nc] = true;
                padre[nr][nc]    = {r, c};
                cola.push({nr, nc});

                if (nr == fin.first && nc == fin.second) {
                    encontrado = true;
                    break;
                }
            }
        }
    }

    if (!encontrado) return false;

    // Reconstruir el camino desde FIN hasta INICIO
    Punto actual = fin;
    while (padre[actual.first][actual.second] != make_pair(-1,-1)) {
        Punto prev = padre[actual.first][actual.second];
        // No sobreescribir S ni E
        if (grid[actual.first][actual.second] != FIN &&
            grid[actual.first][actual.second] != INICIO) {
            grid[actual.first][actual.second] = SOLUCION;
        }
        actual = prev;
    }

    return true;
}

// ─────────────────────────────────────────────
//  6. IMPRIMIR EL LABERINTO
// ─────────────────────────────────────────────
void imprimirLaberinto(const Grid& grid, const string& titulo) {
    cout << "\n=== " << titulo << " ===\n\n";
    for (int r = 0; r < FILAS; r++) {
        for (int c = 0; c < COLS; c++) {
            cout << grid[r][c];
        }
        cout << "\n";
    }
    cout << "\n";
}

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────
int main() {
    cout << "Tamano logico: " << N << " x " << M << "\n";
    cout << "Grid real    : " << FILAS << " x " << COLS << "\n";
    cout << "S = Entrada  E = Salida  * = Solucion\n";

    // 1. Crear grid vacia (todo paredes)
    Grid grid = crearGrid();

    // 2. Generar laberinto con DFS
    generarLaberinto(grid);
    imprimirLaberinto(grid, "LABERINTO GENERADO");

    // 3. Resolver con BFS
    bool resuelto = resolverBFS(grid);

    if (resuelto) {
        imprimirLaberinto(grid, "LABERINTO RESUELTO");
        cout << "Solucion encontrada!\n";
    } else {
        cout << "No existe solucion.\n";
    }

    return 0;
}