ll Distinct_Substrings()
{
  string s;
  cin >> s;
  s += "$";

  pair<vi, vi> result = Suffix_Array_and_LCP(s);
  vi SA = result.first;
  vi LCP = result.second;

  ll sum = 0;
  ll n = s.size() - 1; // Para no contar al '$' agregado

  for (int i = 0; i < n; i++)
    sum += LCP[i];

  ll number_of_substrings = (n * (n + 1)) / 2;
  return number_of_substrings - sum; 
}