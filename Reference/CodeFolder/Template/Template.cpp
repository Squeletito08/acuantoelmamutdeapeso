#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define pb push_back
#define fi first
#define se second
#define sz(a) int(a.size())
#define endl "\n"
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <class T>
using oset = tree<T, null_type, less<T>,
                  rb_tree_tag, tree_order_statistics_node_update>;

ll gcd(ll a, ll b) {return a == 0? b: gcd(b%a,a);}
ll lcm(ll a, ll b) {return a * (b / gcd(a,b));}

int tc;

#define error(...) dbgh(#__VA_ARGS__, __VA_ARGS__)

template <typename T>
void dbgh(const char *names, T value)
{
  cerr << names << " = " << value << endl;
}

template <typename T, typename... Args>
void dbgh(const char *names, T value, Args... args)
{
  const char *comma = strchr(names, ',');
  cerr.write(names, comma - names) << " = " << value << endl;
  dbgh(comma + 1, args...);
}

constexpr ll INF_LL = LONG_LONG_MAX;
constexpr int INF_INT = INT_MAX;

void solve() {}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  for (tc = 1; tc <= t; tc++)
    solve();
  return 0;
}
