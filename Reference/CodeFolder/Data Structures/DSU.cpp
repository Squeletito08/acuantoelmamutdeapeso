typedef vector<int> vi;
/**
 * Estructura DSU (Disjoint Set Union) o Union-Find.
 * Permite mantener conjuntos disjuntos con operaciones eficientes.
 */
struct DSU
{
  vi parent;   // parent[i]: padre del nodo i
  vi rank;     // rank[i]: estimación de la profundidad del árbol del conjunto que contiene a i
  vi setSize;  // setSize[i]: tamaño del conjunto cuya raíz es i
  int numSets; // Número actual de conjuntos disjuntos

  // Constructor: Inicializa DSU con N elementos (1 a N)
  DSU(int N)
  {
    N++; // Para trabajar con índices desde 1
    parent.resize(N);
    rank.assign(N, 0);
    setSize.assign(N, 1);
    for (int i = 1; i < N; ++i)
      parent[i] = i;
    numSets = N - 1;
  }

  // Devuelve la raíz del conjunto que contiene a 'i' (con compresión de caminos)
  int find(int i)
  {
    if (parent[i] != i)
      parent[i] = find(parent[i]);
    return parent[i];
  }

  // Retorna true si 'i' y 'j' están en el mismo conjunto
  bool isSameSet(int i, int j)
  {
    return find(i) == find(j);
  }

  // Retorna el número de conjuntos disjuntos actuales
  int countSets()
  { return numSets; }

  // Retorna el tamaño del conjunto que contiene al elemento 'i'
  int size(int i)
  { return setSize[find(i)]; }

  // Une los conjuntos que contienen a 'i' y 'j'
  void unify(int i, int j)
  {
    if (isSameSet(i, j))
      return;
    int x = find(i), y = find(j);

    // Unión por rango para mantener árboles bajos
    if (rank[x] > rank[y])
      swap(x, y);

    parent[x] = y;
    if (rank[x] == rank[y])
      rank[y]++;

    setSize[y] += setSize[x];
    --numSets;
  }
};

int main()
{
  // Ejemplo de uso
  DSU dsu(5); // Elementos del 1 al 5

  dsu.unify(1, 2);
  dsu.unify(3, 4);

  cout << dsu.isSameSet(1, 2) << endl; //  1 (true)
  cout << dsu.isSameSet(1, 3) << endl; //  0 (false)
  cout << dsu.size(1) << endl;         //  2
  cout << dsu.countSets() << endl;     //  3

  dsu.unify(2, 3);
  cout << dsu.countSets() << endl; //  2

  // Ejemplo componentes conexas
  int n = 6; // nodos del 1 al 6
  vector<pair<int, int>> edges = {
      {1, 2}, {2, 3}, {4, 5}};

  DSU dsu(n);

  // Unir nodos conectados
  for (auto &[u, v] : edges)
    dsu.unify(u, v);

  // Mostrar cuántas componentes conexas hay
  cout << "Componentes conexas: " << dsu.countSets() << endl; // Debería imprimir 3

  // Mostrar tamaño de la componente de cada nodo
  for (int i = 1; i <= n; ++i)
  {
    cout << "Nodo " << i << " pertenece a componente de tamaño: " << dsu.size(i) << endl;
  }
}
