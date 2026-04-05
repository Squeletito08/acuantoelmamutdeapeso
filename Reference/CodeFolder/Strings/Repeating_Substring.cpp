/*
A repeating substring is a substring that occurs in two (or more) locations in the string. Your task is to find the longest repeating substring in a given string.
*/
string Repeating_Substring()
{
  string s;
  cin >> s;
  s += "$";
  pair<vi, vi> result = Suffix_Array_and_LCP(s);
  vi SA = result.first;
  vi LCP = result.second;

  int ans = 0;
  for (int i = 0; i < s.size(); i++)
    ans = max(ans, LCP[SA[i]]);

  if (ans == 0)
    return ""; 

  for (int i = 0; i < s.size(); i++)
    if (ans == LCP[SA[i]])
      return s.substr(SA[i], LCP[SA[i]]);
    
  return "";
}