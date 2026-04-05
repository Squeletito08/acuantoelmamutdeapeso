#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 100005;  // ajusta según el tamaño de tu grafo
vector<int> grafo[MAXN];
bool visitado[MAXN];
int tin[MAXN], low[MAXN];
int timer = 0;
set<int> puntos_articulacion;  // para evitar repetidos

void dfs(int u, int padre = -1) {
    visitado[u] = true;
    tin[u] = low[u] = timer++;
    int hijos = 0;

    for (int v : grafo[u]) {
        if (v == padre) continue;

        if (visitado[v]) {
            // v ya fue visitado: actualiza low
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= tin[u] && padre != -1) {
                puntos_articulacion.insert(u);
            }
            ++hijos;
        }
    }

    // Caso especial: si u es la raíz y tiene más de un hijo
    if (padre == -1 && hijos > 1) {
        puntos_articulacion.insert(u);
    }
}

int main() {
    int n, m;
    cin >> n >> m; // número de nodos y aristas
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        grafo[u].push_back(v);
        grafo[v].push_back(u);  
    }

    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) dfs(i);
    }

    cout << "Puntos de articulación:\n";
    for (int p : puntos_articulacion) {
        cout << p << "\n";
    }

    return 0;
}
