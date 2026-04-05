// A partir de un árbol como gráfica, construye en O(nlogn) un árbol enraizado
// balanceado (de altura O(logn)) dividiéndolo recursivamente en centroides

using graf_t = vector<vector<int>>;

struct ctree_n
{
    int id, parent;
    vector<int> children;
    ctree_n(int id_, int parent_ = -1) : id(id_), parent(parent_), children({}) {}
};

struct ctree
{
    vector<int> size; // size of node[i] subtree
    vector<ctree_n> node;
    int root;

    ctree(const graf_t& graf)
        : size(graf.size(),0)
    {
        int n = graf.size();
        node.reserve(n);
        vector<bool> visited(n,false);
        for (int i = 0; i < n; i++) node.emplace_back(i);
        decompose(0, -1, visited, graf);
    }

private:
    void decompose(int u, int parent, vector<bool>& visited, const graf_t& graf)
    {
        vector<bool> viscp1(visited), viscp2(visited);
        int total = subtree_size(u, -1, viscp1, graf);
        int centroid = find_centroid(u, -1, total, viscp2, graf);
        visited[centroid] = true;
        node[centroid].parent = parent;
        if (parent == -1) node[centroid].parent = root = centroid;
        else node[parent].children.push_back(centroid);
        for (int v : graf[centroid])
            if (!visited[v]) decompose(v, centroid, visited, graf);
    }

    int subtree_size(int u, int p, vector<bool>& visited, const graf_t& graf)
    {
        size[u] = 1;
        for (int v : graf[u])
            if (v != p && !visited[v])
                size[u] += subtree_size(v, u, visited, graf);
        return size[u];
    }

    int find_centroid(int u, int p, int total, vector<bool>& visited, const graf_t& graf)
    {
        for (int v : graf[u])
            if (v != p and !visited[v] and size[v] > total/2)
                return find_centroid(v, u, total, visited, graf);
        return u;
    }
};
