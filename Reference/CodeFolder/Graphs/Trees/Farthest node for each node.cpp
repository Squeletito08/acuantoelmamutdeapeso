// dist[0][i] = distancia del nodo 'a' hacia todos los nodos i
// dist[1][i] = distancia del nodo 'b'' hacai todos los nodos i
int dist[2][N];
vector<int> graph[N];

// f_n = nodo más lejano
int dfs(int u, int p, int d, int i)
{
  dist[i][u] = d;
  int f_n = -1;
  for (int v : graph[u])
  {
    if (v != p)
    {
      int x = dfs(v, u, d + 1, i);
      if (f_n == -1 || dist[i][x] > dist[i][f_n]) f_n = x;
    }
  }
  return f_n == -1 ? u : f_n;
}

void calculate_diameter()
{
  int n; cin >> n;
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    graph[a-1].push_back(b-1);
    graph[b-1].push_back(a-1);
  }
  // Encontramos el nodo 'a' haciendo un dfs desde un nodo arbitrario
  int a = dfs(0, 0, 0, 0);

  // Encontramos el nodo 'b' haciendo un dfs desde 'a', y su vez calculamos la distancia de 'a' hacia todos los demás nodos
  int b = dfs(a, a, 0, 0);

  // Finalmente calculamos la distncia del nodo 'b' hacia todos los demas
  dfs(b, b, 0, 1);

  // dist(a, b) = Longitud del diametro del árbol
  // max(dist[0][u], dist[1][u]) = distancia de u hacia su nodo más lejano
}
