
/*
Given a string s and q queries, each query is a string t
For each request you need to count how many times the string t
occurs as a substring in s.
O(t log(n)) where n = s.size() for each query 
*/

int lwb(vi &SA, string &s, string &t)
{
  int l = 0;
  int r = SA.size() - 1;

  int res = SA.size();
  while (l <= r)
  {
    int m = l + (r - l) / 2;
    if (s.substr(SA[m], t.size()) >= t)
    {
      res = m;
      r = m - 1;
    }
    else
    {
      l = m + 1;
    }
  }
  return res;
}

int upb(vi &SA, string &s, string &t)
{
  int l = 0;
  int r = SA.size() - 1;
  int res = SA.size();
  while (l <= r)
  {
    int m = l + (r - l) / 2;
    if (s.substr(SA[m], t.size()) > t)
    {
      res = m;
      r = m - 1;
    }
    else
    {
      l = m + 1;
    }
  }
  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(nullptr);

  string s;
  cin >> s;
  s += "$";

  vi SA = Suffix_Array(s);

  int q;
  cin >> q;

  while (q--)
  {
    string t;
    cin >> t;
    cout << upb(SA, s, t) - lwb(SA, s, t) << endl;
  }
  return 0;
}