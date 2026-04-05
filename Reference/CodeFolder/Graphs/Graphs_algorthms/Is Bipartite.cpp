int n; 
vector<vector<int>> adj; 

vector<int> side(n, -1); // side[i] = 0 o 1 si ya fue asignado, -1 si no ha sido visitado
bool is_bipartite = true; 

queue<int> q; 
// Recorremos todos los componentes del grafo
for (int st = 0; st < n; ++st) {
    if (side[st] == -1) {
        // Si el nodo aún no ha sido visitado, iniciamos BFS desde él
        q.push(st);
        side[st] = 0; // Le asignamos el color 0

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : adj[v]) {
                if (side[u] == -1) {
                    // Si el vecino no ha sido visitado, lo coloreamos con el color opuesto
                    side[u] = side[v] ^ 1; // Alternamos entre 0 y 1
                    q.push(u);
                } else {
                    // Si el vecino ya está coloreado y tiene el mismo color, no es bipartito
                    if (side[u] == side[v])
                        is_bipartite = false;
                }
            }
        }
    }
}
cout << (is_bipartite ? "YES" : "NO") << endl; 
