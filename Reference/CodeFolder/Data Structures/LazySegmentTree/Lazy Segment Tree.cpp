/* Lazy segment tree para sumar un valor en un rango [l, r] y
sacar la suma, minimo, máximo, etc, en un rango [l, r]

Si quieres que en vez de sumar en un rango sea asignar en un rango,
es decir, poner todos los elementos en el rango [l, r] a un mismo número
solo tienes que sustituir el '+=' por '=' */
struct LazySegmentTree
{
  ll neuter = 0; // remplazar por el nuetro de min, max, etc.
  vector<ll> st, lazy;
  vector<bool> is_lazy; // Para saber si a un nodo le hace falta propagar o no

  LazySegmentTree(vector<ll> &nums)
  {
    int n = nums.size();
    st.assign(4 * n, neuter);
    lazy.assign(4 * n, 0); // Se inicia con 0
    is_lazy.assign(4 * n, false);
    build(1, 0, n - 1, nums);
  }

  // remplazar por min, max, etc.
  inline ll merge(ll a, ll b) { return a + b; }

  void apply(int v, int tl, int tr, ll val)
  {
    lazy[v] += val;
    st[v] += (tr - tl + 1) * val; // si es min/max entonces solo st[v] += val
    is_lazy[v] = true;
  }

  void push(int v, int tl, int tr)
  {
    if (!is_lazy[v])
      return;

    int tm = tl + (tr - tl) / 2;
    apply(v * 2, tl, tm, lazy[v]);
    apply(v * 2 + 1, tm + 1, tr, lazy[v]);

    // Reiniciar lazy
    lazy[v] = 0;
    is_lazy[v] = false;
  }

  void build(int v, int tl, int tr, vector<ll> &nums)
  {
    if (tl == tr)
    {
      st[v] = nums[tl];
      return;
    }

    int tm = tl + (tr - tl) / 2;
    build(v * 2, tl, tm, nums);
    build(v * 2 + 1, tm + 1, tr, nums);
    st[v] = merge(st[v * 2], st[v * 2 + 1]);
  }

  void update(int v, int tl, int tr, int l, int r, ll val)
  {
    if (tl > r || tr < l)
    {
      return;
    }

    if (tl >= l && tr <= r)
    {
      apply(v, tl, tr, val);
      return;
    }

    push(v, tl, tr);
    int tm = tl + (tr - tl) / 2;
    update(v * 2, tl, tm, l, r, val);
    update(v * 2 + 1, tm + 1, tr, l, r, val);
    st[v] = merge(st[v * 2], st[v * 2 + 1]);
  }

  ll query(int v, int tl, int tr, int l, int r)
  {
    if (tl > r || tr < l)
    {
      return neuter;
    }

    if (tl >= l && tr <= r)
    {
      return st[v];
    }

    push(v, tl, tr);
    int tm = tl + (tr - tl) / 2;
    return merge(query(v * 2, tl, tm, l, r),
                 query(v * 2 + 1, tm + 1, tr, l, r));
  }
};