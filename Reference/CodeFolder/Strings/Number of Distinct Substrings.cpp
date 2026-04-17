ll Distinct_Substrings() {
  string s;
  cin >> s;

  SuffixArray sa_obj(s);

  int n = s.size();
  ll total_substrings = (1LL * n * (n + 1)) / 2;

  ll lcp_sum = 0;
  for (int i = 0; i < sa_obj.lcp.size(); i++) {
    lcp_sum += sa_obj.lcp[i];
  }

  return total_substrings - lcp_sum;
}
