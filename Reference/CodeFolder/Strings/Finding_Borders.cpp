/*
A border of a string is a prefix that is also a suffix of the string but not the whole string. For example, the borders of abcababcab are ab and abcab.
Your task is to find all border lengths of a given string: 
*/
void Finding_Borders(string& s){
  vector<int> pi = prefix_function(s);
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