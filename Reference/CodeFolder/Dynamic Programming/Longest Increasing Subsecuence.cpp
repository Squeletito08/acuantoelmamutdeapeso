int LIS(vector<int> &nums)
{
  int n = nums.size();
  vector<int> lis_aux;
  for (int i = 0; i < n; i++)
  {
    int x = nums[i];
    int pos = lower_bound(lis_aux.begin(), lis_aux.end(), x) - lis_aux.begin();
    if (pos == lis_aux.size())
      lis_aux.push_back(x);
    else
      lis_aux[pos] = x;
  }
  return lis_aux.size(); 
}