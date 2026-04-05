template <typename T>
struct MergeSortTree
{
  vector<vector<T>> st;
  MergeSortTree(vector<T> &nums)
  {
    st.resize(nums.size() * 4);
    build(1, 0, nums.size() - 1, nums);
  }

  void build(int v, int tl, int tr, vector<T> &nums)
  {
    if (tl == tr)
    {
      st[v] = {nums[tl]};
      return;
    }

    int tm = tl + (tr - tl) / 2;
    build(v * 2, tl, tm, nums);
    build(v * 2 + 1, tm + 1, tr, nums);

    merge(all(st[v * 2]), all(st[v * 2 + 1]), back_inserter(st[v]));
  }

  // Número de elementos iguales a val   
  T query(int v, int tl, int tr, int l, int r, T val)
  {
    if (tl > r || tr < l)
    {
      return 0;
    }

    if (tl >= l && tr <= r)
    {
      auto it = lower_bound(all(st[v]), val);
      auto jt = upper_bound(all(st[v]), val);

      if (it == st[v].end())
      {
        return 0;
      }

      int j = jt - st[v].begin();
      int i = it - st[v].begin();
      return j - i;
    }

    int tm = tl + (tr - tl) / 2;

    return query(v * 2, tl, tm, l, r, val) + query(v * 2 + 1, tm + 1, tr, l, r, val);
  }
};