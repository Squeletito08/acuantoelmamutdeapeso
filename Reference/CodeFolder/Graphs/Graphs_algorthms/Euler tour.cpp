const int N = 2e5 + 1;
int timer = 0;
int start[N];
int endd[N];
ll arreglo_segtree[N];
ll values[N];
vector<int> graph[N];
void euler_tour(int u, int p)
{
  start[u] = timer++;
  for (int v : graph[u])
    if (v != p)
      euler_tour(v, u);
  endd[u] = timer;
}

int main()
{
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; i++)
    cin >> values[i];
  
  // Gŕafica con nodos 0-indexados
  for (int i = 0; i < n - 1; i++)
  {
    int u, v; cin >> u >> v;
    u--;
    v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  // Empezamos el euler tour con la raiz
  int root = 0;
  euler_tour(root, -1);
  // Para este punto start[i] y end[i] tienen el tiempo en el que se visito y se terminó de visitar el vertice i en el árbol 
  // end[i] - start[i] = Tamaaño del subarbol de i (incluyendolo)

  // Construimos un arreglo con los valores de los nodos, con el orden dado por start, que hará que los nodos estén contiguos y podamos hacer uso de un SegmentTree
  for (int i = 0; i < n; i++)
    arreglo_segtree[start[i]] = values[i];

  SegmentTree<ll> st(arreglo_segtree, n);
  // start[i] = indice desde donde comienza el subarbol de i (incluyendolo) en arreglo_segtree
  // endd[i] - 1 = incide donde termina el subarbol de i en arreglo_segtree (es importante restarle uno)

  while (q--)
  {
    int op; cin >> op;
    int node; cin >> node;
    node--;

    int l = start[node]; 
    int r = endd[node] - 1;

    if (op == 1)
    {
      ll val;
      cin >> val;
      // l es la posición donde está el nodo en arreglo_segtree
      st.update(1, 0, n - 1, l, val);
    }
    else
    {
      // En caso de que no se incluya a nodo en el subarbol
      // puede pasar que el subarbol sea vacío
      if (r < l)
      {
        cout << 0 << endl;
        continue;
      }
      cout << st.query(1, 0, n - 1, l, r) << endl;
    }
  }
  return 0;
}