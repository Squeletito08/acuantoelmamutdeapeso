#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005;
vector<int> grafo[MAXN];
bool visitado[MAXN];
int tin[MAXN], low[MAXN];
int timer = 0;
vector<pair<int, int>> puentes;

void dfs(int u, int padre = -1) {
    visitado[u] = true;
    tin[u] = low[u] = timer++;

    for (int v : grafo[u]) {
        if (v == padre) continue;

        if (visitado[v]) {
            // back edge
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > tin[u]) {
                // u-v es un puente
                puentes.push_back({u, v});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m; // número de nodos y aristas

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        grafo[u].push_back(v);
        grafo[v].push_back(u); // no dirigido
    }

    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) dfs(i);
    }

    cout << "Puentes encontrados:\n";
    for (auto [u, v] : puentes) {
        cout << u << " - " << v << "\n";
    }

    return 0;
}
