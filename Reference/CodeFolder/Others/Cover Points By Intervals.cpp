// Número de puntos x en 0 <= l <= r <= 1e18 tal que el 
// número de intervalos que lo cubren es igual a k, con k en [1...n]
void cover_points()
{
  int n; cin >> n;
  vector<pll> pairs(n); vector<ll> val;
  for (int i = 0; i < n; i++)
  {
    ll l, r;
    cin >> l >> r;
    pairs[i] = make_pair(l, r + 1);
    val.push_back(l);
    val.push_back(r + 1);
  }

  sort(all(val));
  val.resize(unique(all(val)) - val.begin());
  vector<ll> prefix(2 * n + 1);

  for (auto p : pairs)
  {
    int l = lower_bound(all(val), p.first) - val.begin();
    int r = lower_bound(all(val), p.second) - val.begin();
    prefix[l] += 1;
    prefix[r] -= 1;
  }
  for (int i = 1; i <= 2 * n; i++)
    prefix[i] += prefix[i - 1];
  
  vector<ll> res(n + 1);
  for (int i = 1; i < val.size(); i++)
  {
    ll num_points = val[i] - val[i - 1];
    res[prefix[i - 1]] += num_points;
  }
  // res[i] = El número de puntos que son cubiertos por i intervalos
}