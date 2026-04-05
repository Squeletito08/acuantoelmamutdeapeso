const int M = 26;
struct node
{
  vector<int> child;
  int p = -1;
  char c = 0;
  int suffixLink = -1, endLink = -1;
  int id = -1;
  node(int p = -1, char c = 0) : p(p), c(c)
  {
    child.resize(M, -1);
  }
};

struct AhoCorasick
{
  vector<node> t;
  vector<int> lengths; // Longitud de las palabras en el trie
  vector<int> occ;     // Ocurrencias por patrón
  int wordCount = 0;
  AhoCorasick()
  {
    t.emplace_back();
  }

  // Regresa el ID que se le asigno a la palabra agregada (0-indexado)
  int add(const string &s)
  {
    int u = 0; // Raíz temporal
    for (char c : s)
    {
      if (t[u].child[c - 'a'] == -1)
      {
        t[u].child[c - 'a'] = t.size();
        t.emplace_back(u, c);
      }
      u = t[u].child[c - 'a'];
    }
    if (t[u].id == -1) // Por si se trata de agregra una palabra que ya estaba
      t[u].id = wordCount++;
    lengths.push_back(s.size());
    return t[u].id;
  }

  void link(int u)
  {
    if (u == 0) // Si eres la raíz
    {
      t[u].suffixLink = 0;
      t[u].endLink = 0;
      return;
    }
    if (t[u].p == 0) // Si tu padre es la raíz
    {
      t[u].suffixLink = 0;
      if (t[u].id != -1)
        t[u].endLink = u;
      else
        t[u].endLink = t[t[u].suffixLink].endLink;
      return;
    }

    int v = t[t[u].p].suffixLink;
    char c = t[u].c;
    while (true)
    {
      if (t[v].child[c - 'a'] != -1)
      {
        t[u].suffixLink = t[v].child[c - 'a'];
        break;
      }
      if (v == 0)
      {
        t[u].suffixLink = 0;
        break;
      }
      v = t[v].suffixLink;
    }
    if (t[u].id != -1) // Si eres una palabra
      t[u].endLink = u;
    else
      t[u].endLink = t[t[u].suffixLink].endLink;
  }

  // BFS para construir los suffix links y end lins. Llamar a esto
  // cuando ya hayas metido todas strings del diccionario al trie
  void build()
  {
    queue<int> Q;
    Q.push(0);
    while (!Q.empty())
    {
      int u = Q.front();
      Q.pop();
      link(u);
      for (int v = 0; v < M; ++v)
        if (t[u].child[v] != -1)
          Q.push(t[u].child[v]);
    }
    occ.assign(wordCount, 0);
  }

  int match(const string &text)
  {
    int u = 0;
    int ans = 0;
    for (int j = 0; j < text.size(); ++j)
    {
      int i = text[j] - 'a';
      while (true)
      {
        if (t[u].child[i] != -1)
        {
          u = t[u].child[i];
          break;
        }
        if (u == 0)
          break;
        u = t[u].suffixLink;
      }

      // Temporal de u para moverse por el endLink para el caso
      // en el que haya sufijos propios de lo que llevamos visitado
      // que su vez sean palabras
      int v = u;
      while (true)
      {
        v = t[v].endLink;
        if (v == 0)
          break;
        ++ans;
        // int idx = j + 1 - lengths[t[v].id];
        // cout << "Found word #" << t[v].id << " at position " << idx << "\n";
        occ[t[v].id]++;
        v = t[v].suffixLink; // Para eviar el caso en el que el nodo de v es el de una palabra
      }
    }
    return ans;
  }
};

int main()
{
  AhoCorasick ac;
  string text;
  cin >> text;
  int n;
  cin >> n;
  vector<int> ids(n); // Por si se agrega varias veces la misma palabra
  for (int i = 0; i < n; i++)
  {
    string word;
    cin >> word;
    ids[i] = ac.add(word);
  }
  ac.build();
  ac.match(text);
  for (int i = 0; i < n; i++)
    cout << ac.occ[ids[i]] << endl;
  return 0;
}
