#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int INF = INT_MAX;

struct Edge
{
  int w = INF, to = -1;
  bool operator<(Edge const &other) const
  {
    return make_pair(w, to) < make_pair(other.w, other.to);
  }
};

int n;
vector<vector<Edge>> adj;

// O(m log n), useful for sparse graphs (m < n*(n-1)/2)
void prim()
{
  ll total_weight = 0;
  vector<Edge> min_e(n); // At the end will contain the edges of the MST
  min_e[0].w = 0;
  set<Edge> q;
  q.insert({0, 0});
  vector<bool> selected(n, false);
  for (int i = 0; i < n; ++i)
  {
    if (q.empty())
    {
      cout << "IMPOSSIBLE" << endl;
      return;
    }

    int v = q.begin()->to;
    selected[v] = true;
    total_weight += q.begin()->w;
    q.erase(q.begin());

    // if (min_e[v].to != -1)
    //   cout << v << " " << min_e[v].to << endl;

    for (Edge e : adj[v])
    {
      if (!selected[e.to] && e.w < min_e[e.to].w)
      {
        q.erase({min_e[e.to].w, e.to});
        min_e[e.to] = {e.w, v};
        q.insert({e.w, e.to});
      }
    }
  }

  cout << total_weight << endl;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cin >> n;
  int m;
  cin >> m;
  adj.resize(n);
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    int w;
    cin >> w;
    u--;
    v--;
    adj[u].push_back({w, v});
    adj[v].push_back({w, u});
  }
  prim();
}