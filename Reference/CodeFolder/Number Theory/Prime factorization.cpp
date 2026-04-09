map<long long, int> primeFactorize(long long n) {
  map<long long, int> factors;
  while (n % 2 == 0) {
    factors[2]++;
    n /= 2;
  }
  for (long long i = 3; i * i <= n; i += 2) {
    while (n % i == 0) {
      factors[i]++;
      n /= i;
    }
  }
  // Si sigue siendo más grande que 1, es primo
  if (n > 1) {
    factors[n]++;
  }
  return factors;
}
