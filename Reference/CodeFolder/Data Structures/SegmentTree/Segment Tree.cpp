template <typename T>
struct SegmentTree
{
  // usa, v = 1, tl = 0, tr = n-1 para 0-indexed
  // usa  v = 1, tl = 1, tr = n para 1-indexed pero 
  // asegurate de acceder a nums[tl] correctamente 
  T neuter;
  vector<T> st;
  inline T merge(T a, T b) { return a + b; }
  // 6
  SegmentTree(vector<T> &nums)
  {
    neuter = 0;
    st.assign(4 * nums.size(), neuter);
    build(1, 0, nums.size() - 1, nums);
  }
  // 12
  void build(int v, int tl, int tr, vector<T> &nums)
  {
    if (tl == tr)
    {
      st[v] = nums[tl];
      return;
    }
    int tm = tl + (tr - tl) / 2;
    build(v * 2, tl, tm, nums);
    build(v * 2 + 1, tm + 1, tr, nums);
    st[v] = merge(st[2 * v], st[2 * v + 1]);
  }
  // 12
  void update(int v, int tl, int tr, int pos, T val)
  {
    if (tl == tr)
    {
      st[v] = val;
      return;
    }
    int tm = tl + (tr - tl) / 2;
    if (pos <= tm) update(v * 2, tl, tm, pos, val);
    else update(v * 2 + 1, tm + 1, tr, pos, val);
    st[v] = merge(st[v * 2], st[v * 2 + 1]);
  }
  // 8
  T query(int v, int tl, int tr, int l, int r)
  {
    if (tl >= l && tr <= r) return st[v];
    if (tl > r || tr < l) return neuter;
    int tm = tl + (tr - tl) / 2;
    return merge(query(v * 2, tl, tm, l, r), 
    query(v * 2 + 1, tm + 1, tr, l, r));
  }
};
