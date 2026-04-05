/*
pi[i] = Longitud del prefijo propio más grande
en la substring s[0...i] que también es sufijo de 
esa misma substring. Por definición pi[0] = 0. 

s =  b a b a b a c b b a 
pi = 0 0 1 2 3 4 0 1 1 2 
    ----------------------
     0 1 2 3 4 5 6 7 8 9 
*/
vector<int> prefix_function(const string &s)
{
  int n = s.size();
  vector<int> pi(n, 0);
  int j = 0;
  for (int i = 1; i < n; i++)
  {
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}

/*
A border of a string is a prefix that is also a suffix of the string but not the whole string. For example, the borders of abcababcab are ab and abcab.
Your task is to find all border lengths of a given string: 
*/
void Finding_Borders(string& s){
  vector<int> pi = prefix_fun(s);
  // Empezamos con el borde más grande
  int j = pi[s.size() - 1];
  vector<int> res;
  while (j > 0)
  {
    res.push_back(j);
    // El siguiente borde más grande 
    j = pi[j - 1];
  }
  for (int i = res.size() - 1; i >= 0; i--)
    cout << res[i] << " ";
}