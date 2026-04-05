// O(3^n)
int dp[1 << 16];
int cost[1 << 16];
int main()
{
  int N = 16;
  for (int mask = 0; mask < N; mask++)
  {
    for (int submask = mask; submask; submask = (submask - 1) & mask)
    {
      dp[mask] = max(dp[mask], cost[submask] + dp[mask ^ submask]);
    }
  }
  return 0;
}