const int N = 100 + 1;
const int MAX_V = N * 1e3 + 1;
ll dp[N][MAX_V], value[N], weight[N];
// Es como un coin change 
ll knpasack_01_2()
{
  int n, w; cin >> n >> w;
  for (int i = 0; i < n; i++)
  { cin >> weight[i]; cin >> value[i]; }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < MAX_V; j++)
      dp[i][j] = INT_MAX;  
  
  dp[0][0] = 0;
  ll res = 0;
  for (int i = 1; i <= n; i++){
    for (int j = 0; j < MAX_V; j++)
    {
      if (j - value[i - 1] < 0)
        dp[i][j] = dp[i - 1][j];
      else
        dp[i][j] = min(dp[i - 1][j], 
                       dp[i - 1][j - value[i - 1]] + weight[i - 1]);
      if (dp[i][j] <= w)
        res = j;
    }
  }
  return res;
}

