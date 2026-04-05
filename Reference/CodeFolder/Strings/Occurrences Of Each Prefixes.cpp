vector<int> occurrences_of_each_prefixes(const string& s){
  int n = s.size();
  vector<int> pref = prefix_function(s);
  vector<int> occ(n + 1);
  for (int i = 0; i < n; i++)
    occ[pref[i]]++;
  for (int i = n - 1; i > 0; i--)
    occ[pref[i - 1]] += occ[i];
  for (int i = 0; i <= n; i++)
    occ[i]++;
  return occ; 
}