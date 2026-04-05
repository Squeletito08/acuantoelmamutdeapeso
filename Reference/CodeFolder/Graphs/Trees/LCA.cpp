// Puede ser útil recordar que dist(a,b) = depth(a) + depth(b) - 2*depth(lca(a,b))
int n, l;                // n = número de nodos, l = log2(n)
vector<vector<int>> adj; // Lista de adyacencia del árbol

int timer;              // Temporizador para asignar tin y tout
vector<int> tin, tout;  // Tiempo de entrada y salida en DFS
vector<vector<int>> up; // up[v][i] = 2^i-ésimo ancestro de v

// DFS para preprocesar ancestros y tiempos
void dfs(int v, int p)
{
  tin[v] = ++timer; // Al entrar al nodo v
  up[v][0] = p;     // 2^0-ésimo ancestro es el padre directo

  // Computar los 2^i-ésimos ancestros
  for (int i = 1; i <= l; ++i)
    up[v][i] = up[up[v][i - 1]][i - 1];

  // Continuar DFS con los hijos
  for (int u : adj[v])
  {
    if (u != p)
      dfs(u, v);
  }

  tout[v] = ++timer; // Al salir del nodo v
}

// Verifica si u es ancestro de v usando tin y tout
bool is_ancestor(int u, int v)
{
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

// Devuelve el Lowest Common Ancestor de u y v
int lca(int u, int v)
{
  // Si uno es ancestro del otro, es el LCA
  if (is_ancestor(u, v))
    return u;
  if (is_ancestor(v, u))
    return v;

  // Subimos a u hasta que su ancestro está justo por debajo del LCA
  for (int i = l; i >= 0; --i)
  {
    if (!is_ancestor(up[u][i], v))
      u = up[u][i];
  }

  return up[u][0]; // El padre de u en este punto es el LCA
}

// Preprocesamiento inicial para Binary Lifting
void preprocess(int root)
{
  tin.resize(n);
  tout.resize(n);
  timer = 0;
  l = ceil(log2(n)); // Límite de profundidad de los ancestros
  up.assign(n, vector<int>(l + 1));
  dfs(root, root); // Empezamos el DFS desde la raíz
}

int main()
{
  n = 7;
  adj.resize(n);
  adj[0] = {1, 2};
  adj[1] = {0, 3, 4};
  adj[2] = {0, 5, 6};
  adj[3] = {1};
  adj[4] = {1};
  adj[5] = {2};
  adj[6] = {2};

  preprocess(0); // Raíz del árbol en 0

  cout << lca(3, 4) << endl; // Salida esperada: 1
  cout << lca(5, 6) << endl; // Salida esperada: 2
  cout << lca(3, 5) << endl; // Salida esperada: 0
}
