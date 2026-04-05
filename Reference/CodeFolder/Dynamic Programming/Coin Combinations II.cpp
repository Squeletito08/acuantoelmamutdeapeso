const int X = 1e6 + 1;
ll dp[X];
ll coin_combinations_II()
{
  int n, x; cin >> n >> x;
  if (n <= 0 || x < 0) return 0;

  vector<ll> coins(n);
  for (int i = 0; i < n; i++)
    cin >> coins[i];
  dp[0] = 1;

  for (int c : coins)
    for (int sum = 0; sum <= x; sum++)
      if (sum - c >= 0)
      {
        dp[sum] += dp[sum - c];
        dp[sum] %= MOD;
      }
  return dp[x];
}
