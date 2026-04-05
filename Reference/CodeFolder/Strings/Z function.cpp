/**
z[i] = longitud de la substring más grande que empieza en i 
y que también es un prefijo de la string s 

s = a a b x a a y a a b 
z = 0 1 0 0 2 1 0 3 1 0
  -----------------------
    0 1 2 3 4 5 6 7 8 9 
*/
vector<int> Z_function(const string &s)
{
  int n = s.size();
  vector<int> z(n, 0);
  int l = 0, r = 0; 
  z[0] = 0;
  for (int i = 1; i < n; i++)
  {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r)
    {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}

