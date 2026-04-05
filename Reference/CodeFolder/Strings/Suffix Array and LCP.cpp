/*
Suffix array (SA):
Let s be a string of length n.The i-th suffix of s is the substring
s[i...n - 1].
A suffix array will contain integers that represent the starting indexes of the all the suffixes of a given string, after the aforementioned suffixes are sorted.

Note:  The order of the sorted cyclic shifts is equivalent to the order of the sorted suffixes

LCP (Longest Common Prefix) array:
A value lcp[SA[i]] indicates length of the longest common prefix of the suffixes indexed in SA[i] and SA[i+1]. 

txt[0..n-1] = "b a n a n a $"
               0 1 2 3 4 5 6

suffix[]  = {6,    5,   3,     1,       0,        4,    2}
          = {"$", "a", "ana", "anana", "banana", "na", "nana"}
            ---------------------------------------------------
             0     1    2      3        4         5     6

for (int i = 1; i < n; i++)
    cout << LCP[SA[i]] << " "; 
lcp        = {0, 1, 3, 0, 0, 2, 0}
lcp[SA[0]] = LCP of "$" and "a"          = 0
lcp[SA[1]] = LCP of "a" and "ana"        = 1
lcp[SA[2]] = LCP of "ana" and "anana"    = 3
lcp[SA[3]] = LCP of "anana" and "banana" = 0
lcp[SA[4]] = LCP of "banana" and "na"    = 0
lcp[SA[5]] = LCP of "na" and "nana"      = 2
*/

void countingSort(vi &SA, vi &eq)
{
  vi count(sz(eq));

  for (int i = 0; i < sz(eq); i++)
    count[eq[i]]++;

  for (int i = 1; i < sz(eq); i++)
    count[i] += count[i - 1];

  vi out(sz(eq));

  for (int i = sz(eq) - 1; i >= 0; i--)
  {
    int val = eq[SA[i]];
    out[count[val] - 1] = SA[i];
    count[val]--;
  }
  SA = out;
}

pair<vi, vi> Suffix_Array_and_LCP(const string &s)
{
  int n = sz(s);
  vector<pair<char, int>> aux(n);

  for (int i = 0; i < n; i++)
    aux[i] = {s[i], i};

  sort(all(aux));

  vi SA(n);

  for (int i = 0; i < n; i++)
    SA[i] = aux[i].second;

  vi eq(n);

  eq[SA[0]] = 0;
  for (int i = 1; i < n; i++)
    eq[SA[i]] = (aux[i - 1].first != aux[i].first) ? eq[SA[i - 1]] + 1 : eq[SA[i - 1]];

  for (int h = 0; (1 << h) < n; h++)
  {
    int k = 1 << h;

    for (int i = 0; i < n; i++)
      SA[i] = (SA[i] - k + n) % n;

    countingSort(SA, eq);

    vi aux(n);
    aux[SA[0]] = 0;
    for (int i = 1; i < n; i++)
    {
      pair<int, int> ant = {eq[SA[i - 1]],
                            eq[(SA[i - 1] + k) % n]};
      pair<int, int> act = {eq[SA[i]], eq[(SA[i] + k) % n]};
      aux[SA[i]] = (ant != act) ? aux[SA[i - 1]] + 1 : aux[SA[i - 1]];
    }

    eq = aux;
  }

  vi LCP(n);

  int k = 0;
  for (int i = 0; i < n - 1; i++)
  {
    int j = SA[eq[i] - 1];

    while (s[i + k] == s[j + k])
      k++;

    LCP[i] = k;

    k = max(k - 1, 0);
  }

  return {SA, LCP};
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  string s;
  cin >> s;
  s += "$";
  pair<vi, vi> result = Suffix_Array_and_LCP(s);
  vi SA = result.first;
  vi LCP = result.second;
  return 0;
}