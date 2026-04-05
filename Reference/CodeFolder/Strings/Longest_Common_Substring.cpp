
// Nos dice si i pertenece a la string a y j a la string b o viceversa
bool distintos(int n1, int n, int i, int j)
{
  return (i >= 0 && i < n1 && j >= n1 + 1 && j < n) || (j >= 0 && j < n1 && i >= n1 + 1 && i < n);
}

string LCS()
{
  string a;
  cin >> a;
  int n1 = a.size();

  string b;
  cin >> b;
  int n2 = b.size();

  string s = a + "$" + b + "#";

  pair<vi, vi> result = Suffix_Array_and_LCP(s);
  vi SA = result.first;
  vi LCP = result.second;

  int res = 0;
  int maximo = INT_MIN;
  for (int i = 1; i < s.size(); i++)
  {
    if (distintos(n1, s.size(), SA[i], SA[i - 1]))
    {
      if (LCP[SA[i]] > maximo)
      {
        maximo = LCP[SA[i]];
        res = SA[i];
      }
    }
  }
  return s.substr(res, LCP[res]); 
}