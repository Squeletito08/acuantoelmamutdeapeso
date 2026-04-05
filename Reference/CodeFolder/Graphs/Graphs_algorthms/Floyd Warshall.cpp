const int INF = 1e9;
int n; 

vector<vector<int>> d(n, vector<int>(n, INF));
// Inicializamos la matriz de distancias:
// - d[i][j] = INF si no hay un camino directo conocido de i a j
// - d[i][i] = 0 para todo i (la distancia de un nodo a sí mismo es 0)
// - d[i][j] = peso de la arista de i a j, si existe una arista directa

// Floyd-Warshall: encuentra distancias mínimas entre todos los pares (i, j)
for (int k = 0; k < n; ++k) {
    // Usamos el nodo k como intermediario
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Solo procesamos si los caminos i -> k y k -> j existen
            if (d[i][k] < INF && d[k][j] < INF)
                // Verificamos si ir de i a j pasando por k es más barato
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }
}
