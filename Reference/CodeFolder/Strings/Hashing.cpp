struct Hash
{
  ll P = 1777771; // Primo para sacar el hash
  ll MOD[2], PI[2];
  vector<ll> h[2]; // Contiene los prefix sum de los hahses  
  vector<ll> pi[2]; // pi[k][i] contiene PI[k] elevado a la i 
  Hash(string &s)
  {
    MOD[0] = 999727999;
    MOD[1] = 1070777777;
    PI[0] = 325255434; // Inverso multiplicativo de P modulo MOD[0]
    PI[1] = 10018302; // Inverso multiplicativo de P modulo MOD[1]
    for (int k = 0; k < 2; k++)
      h[k].resize(s.size() + 1), pi[k].resize(s.size() + 1);
    for (int k = 0; k < 2; k++)
    {
      h[k][0] = 0;
      pi[k][0] = 1;
      ll p = 1;
      for (int i = 1; i < s.size() + 1; i++)
      {
        h[k][i] = (h[k][i - 1] + p * s[i - 1]) % MOD[k];
        pi[k][i] = (1LL * pi[k][i - 1] * PI[k]) % MOD[k];
        p = (p * P) % MOD[k];
      }
    }
  }
  // Returns the hash of substring [s,e)
  ll get(int s, int e)
  {
    ll h0 = (h[0][e] - h[0][s] + MOD[0]) % MOD[0];
    h0 = (1LL * h0 * pi[0][s]) % MOD[0];
    ll h1 = (h[1][e] - h[1][s] + MOD[1]) % MOD[1];
    h1 = (1LL * h1 * pi[1][s]) % MOD[1];
    return (h0 << 32) | h1;
  }
};

// O(n²)
int Distinct_Substrings(string& s){
  int n = s.size();
  Hash s_hash(s);
  unordered_set<ll> aux;
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
      aux.insert(s_hash.get(i, j + 1));

 return aux.size(); 
}

// Nos dice si la substring s[l2...r2] es menor que la string s[l1...r1] en
// tiempo log_2(n)
bool less_str(string &s, Hash &hash, int l1, int r1, int l2, int r2)
{
  int l = 0;
  int r = s.size() - 1;

  // Busqueda binaria en la longitud máxima del prefijo que es igual en ambas strings
  int last = 0;
  while (l <= r)
  {
    int m = l + (r - l) / 2;
    int h1 = hash.get(l1, l1 + m);
    int h2 = hash.get(l2, l2 + m);

    if (h1 == h2)
    {
      last = m;
      l = m + 1;
    }
    else
    {
      r = m - 1;
    }
  }

  // s[l1...l1+last) == s[l2...l2+last)
  // Si last < s.size() && s[l2+last] < s[l1+last] entonces
  // s[l2...r2] es menor que la string s[l1...r1]
  return last < s.size() && s[l2 + last] < s[l1 + last];
}