void sieve_of_eratosthenes() {
  int n;
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i] && (long long)i * i <= n) {
      for (int j = i * i; j <= n; j += i)
        is_prime[j] = false;
    }
  }
}

// lpf[i] contiene el factor primo más pequeño que divide a i
void sieve_lower_prime_factor() {
  vector<int> lpf(n + 1, 1);
  for (int i = 2; i <= n; i++) {
    if (lpf[i] == 1 && (long long)i * i <= n) {
      lpf[i] = i;
      for (int j = i * i; j <= n; j += i) {
        lpf[j] = i;
      }
    }
  }

  // Factorizar a num en sus factores primos O(log n)
  while (num != 1) {
    cout << lpf[num] << " ";
    num /= lpf[num];
  }
}
