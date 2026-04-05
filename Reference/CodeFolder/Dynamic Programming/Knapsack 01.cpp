const ll W = 1e5 + 1;
const ll N = 100 + 1;
ll value[N], weight[N], dp[N][W];
ll knapsack_01()
{
  int n, w; cin >> n >> w;
  for (int i = 0; i < n; i++)
  { cin >> weight[i]; cin >> value[i]; }

  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= w; j++)
      if (j - weight[i - 1] < 0) 
        dp[i][j] = dp[i - 1][j];
      else 
        dp[i][j] = max(dp[i - 1][j], 
        dp[i - 1][j - weight[i - 1]] + value[i - 1]);
    
  return dp[n][w];
}
