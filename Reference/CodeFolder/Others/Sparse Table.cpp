#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  // Calcula la potencia de 2 más grande tal que 2^k <= i
  vector<int> log(n + 1);
  log[1] = 0;
  for (int i = 2; i <= n; i++) {
    log[i] = log[i / 2] + 1;
  }

  int k = log[n] + 1;
  vector<vector<int>> sparse_table(k, vector<int>(n, INT_MAX));
  sparse_table[0] = nums;

  for (int i = 1; i < k; i++) {
    for (int j = 0; j + (1 << i) - 1 < n; j++) {
      sparse_table[i][j] =
          min(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]);
    }
  }

  while (q--) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    int k = log[r - l + 1];
    cout << min(sparse_table[k][l], sparse_table[k][r - (1 << k) + 1]) << endl;
  }

  return 0;
}
