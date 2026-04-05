int lcs(string &a, string &b)
{
  int m = a.size(), n = b.size();
  vector<vector<int>> aux(m + 1, vector<int>(n + 1));
  for (int i = 1; i <= m; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      if (a[i - 1] == b[j - 1])
        aux[i][j] = 1 + aux[i - 1][j - 1];
      else
        aux[i][j] = max(aux[i - 1][j], aux[i][j - 1]);
    }
  }
  return aux[m][n];
}