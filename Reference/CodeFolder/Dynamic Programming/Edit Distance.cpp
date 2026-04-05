
const int N = 5000+1; 
const int M = 5000+1; 
int dp[N][M]; 
int edit_distance()
{
  string s, t; cin >> s >> t;
  int n = s.size(); int m = t.size();

  for (int j = m; j >= 0; j--)
    dp[n][j] = t.size() - j;
  for (int i = n; i >= 0; i--)
    dp[i][m] = s.size() - i;
  
  for (int i = n - 1; i >= 0; i--)
    for (int j = m - 1; j >= 0; j--)
      if (s[i] == t[j])
        dp[i][j] = dp[i + 1][j + 1];
      else
        dp[i][j] = min({1 + dp[i + 1][j + 1], 
                        1 + dp[i + 1][j], 
                        1 + dp[i][j + 1]});
    
  return dp[0][0]; 
}
