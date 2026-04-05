// Test de primalidad de Fermat (probabilistico)
bool isPrime(ll n, int iter = 5)
{
  if (n < 4) return n == 2 || n == 3;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 0; i < iter; i++)
  {
    ll a = 2 + rand() % (n - 3);
    if (modpow(a, n - 1, n) != 1) return false;
  }
  return true;
}