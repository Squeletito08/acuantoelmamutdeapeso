// En un árbol enraizado, marcamos a una única arista hacia un hijo como pesada
// si cuenta con la mayor cantidad de vértices en su subárbol. Esto nos forma
// trayectorias pesadas, sobre las cuales podemos agregar segment-trees de
// prefijos para hacer updates/queries de trayectorias, pues se puede mostrar
// que cualquier trayectoria cuenta con a lo más O(logn) de trayectorias
// pesadas. Las aristas no-pesadas les llamamos ligeras.
// La descomposición toma O(n).

// En varios casos se puede usar un segment tree sobre el euler tour en lugar
// de hacer esto.

// parent[v] es el padre de v, depth[v] es la profundidad en v, heavy[v] indica
// al hijo con el cual <v,heavy[v]> es arista pesada, head[v] es donde termina
// el heavy path de v, pos[v] es la posición en el segment-tree de dicho heavy
// path completo. En decompose se llena head y pos.
vector<int> parent, depth, heavy, head, pos;
int cur_pos;

// esto se llama desde init, no directamente
int dfs(int v, vector<vector<int>> const& adj) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c, adj);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    return size;
}

// esto se llama desde init, no directamente
void decompose(int v, int h, vector<vector<int>> const& adj) {
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1)
        decompose(heavy[v], h, adj);
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c, adj);
    }
}

// se asume v=0 raíz
void init(vector<vector<int>> const& adj) {
    int n = adj.size();
    parent = vector<int>(n);
    depth = vector<int>(n);
    heavy = vector<int>(n, -1);
    head = vector<int>(n);
    pos = vector<int>(n);
    cur_pos = 0;

    dfs(0, adj);
    decompose(0, 0, adj);
}

// max-query en este ejemplo
// Encontramos lca(a, b)=L, hacemos la query del segment tree a->L y L->b
// Como hay un segment tree por heavy path y hay logn heavy paths, O(log^2 n)
// |- (pero si precalculas los prefijos es logn)
// TODO: implementar segment_tree_query(-, -). En lugar de implementar logn
//       segment-trees, se puede implementar uno solo con segmentos disjuntos
//       por cada heavy path
int query(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]);
        res = max(res, cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    int last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
    res = max(res, last_heavy_path_max);
    return res;
}
