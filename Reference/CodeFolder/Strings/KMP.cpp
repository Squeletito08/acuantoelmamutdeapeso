vector<int> KMP(const string &text, const string &pat)
{
  int n = text.size();
  vector<int> pi = prefix_function(pat);
  int j = pi[0];
  vector<int> pi_text(n, 0);
  for (int i = 0; i < n; i++)
  {
    while (j > 0 && text[i] != pat[j]) j = pi[j - 1];
    if (text[i] == pat[j]) j++;
    pi_text[i] = j;
    if (j == pat.size()) j = pi[j - 1];
  }
  // Las ocurrencias de pat.size() en pi_text
  // son las apariciones de pat en text
  return pi_text;
}