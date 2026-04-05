#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 19;
const int DIG = 10;
const int CEROS = 2;
const int LIBRE = 2;

ll dp[N][DIG][CEROS][LIBRE];

ll counting(string &numero, int n, int ant, bool ceros, bool libre)
{
  if (n == 0)
    return 1;

  int dig = numero[numero.size() - n] - '0';

  if (ant != -1 && dp[n][ant][ceros][libre] != -1)
    return dp[n][ant][ceros][libre];

  ll res = 0;
  int tope = (libre) ? 9 : dig;

  for (int j = 0; j <= tope; j++)
  {

    if (j == ant && !ceros)
      continue;

    res += counting(numero, n - 1, j, ceros && j == 0, libre || j < dig);
  }

  if (ant != -1)
    dp[n][ant][ceros][libre] = res;
  return res;
}

// Your task is to count the number of integers between a and b where no two adjacent digits are the same.
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(nullptr);

  ll a, b;
  cin >> a >> b;
  a--;
  memset(dp, -1, sizeof(dp));
  string b_s = to_string(b);
  ll res = counting(b_s, b_s.size(), -1, 1, 0);

  if (a >= 0)
  {
    memset(dp, -1, sizeof(dp));
    string a_s = to_string(a);
    res -= counting(a_s, a_s.size(), -1, 1, 0);
  }

  cout << res << endl;
  return 0;
}