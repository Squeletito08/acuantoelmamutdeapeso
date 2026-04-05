const ll W = 1e5 + 1;
const ll N = 100 + 1;
ll value[N], weight[N], dp[W];
ll knapsack_01_op()
{
  ll n, w; cin >> n >> w;
  for (int i = 0; i < n; i++)
  { cin >> weight[i]; cin >> value[i]; }

  for (int i = 0; i < n; i++)
    for (int j = w; j >= 0; j--)
      if (j - weight[i] >= 0)
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
      
  return dp[w];
}
