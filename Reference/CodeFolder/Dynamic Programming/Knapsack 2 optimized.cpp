const int N = 100 + 1;
const int MAX_V = N * 1e3 + 1;
ll dp[MAX_V], value[N], weight[N];
ll knpasack_01_2_op()
{
  int n, w; cin >> n >> w;

  for (int i = 0; i < n; i++)
  { cin >> weight[i]; cin >> value[i]; }

  for (int i = 0; i < MAX_V; i++)
    dp[i] = INT_MAX;
  
  dp[0] = 0;
  ll res = 0;
  for (int i = 1; i <= n; i++)
  {
    for (int j = MAX_V - 1; j >= 0; j--)
    {
      if (j - value[i - 1] >= 0)
        dp[j] = min(dp[j], dp[j - value[i - 1]] + weight[i - 1]);
      if (dp[j] <= w)
        res = max((ll)j, res);
    }
  }
  return res;
}
