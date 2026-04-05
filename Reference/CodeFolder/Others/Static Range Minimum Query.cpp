// O(n) construccion, O(1) query
template<typename T> struct rmq
{
    vector<T> v;
    ll n; static const int b = 62; // cambia a 30 si usamos int en lugar de ll
    vector<ll> mask, t;

    // la operación se puede cambiar si el resultado es elemento del cjto
    ll op(ll x, ll y) { return v[x] < v[y] ? x : y; }
    ll msb(ll x) { return __builtin_clz(1)-__builtin_clz(x); }
    ll small (ll r, ll sz = b) { return r-msb(mask[r]&((1<<sz)-1)); }
    rmq(const vector<T>& v_) : v(v_), n(v.size()), mask(n), t(n)
    {
        for (ll i = 0, at = 0; i < n; mask[i++] = at |= 1)
        {
            at = (at<<1)&((1ll<<b)-1);
            while (at and op(i, i-msb(at&-at)) == i)
                at ^= at&-at;
        }
        for (ll i = 0; i < n/b; i++)
            t[i] = small(b*i+b-1);
        for (ll j = 1; (1ll<<j) <= n/b; j++)
        for (ll i = 0; i+(1ll<<j) <= n/b; i++)
                t[n/b*j+1] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1ll<<(j-1))]);
    }
    T query(ll l, ll r)
    {
        if (r-l+1 <= b) return v[small(r,r-l+1)];
        ll ans = op(small(l+b-1), small(r));
        ll x = l/b+1, y = r/b-1;
        if (x <= y)
        {
            ll j = msb(y-x+1);
            ans = op(ans, op(t[n/b*j+x], t[n/b*j+y-(1ll<<j)+1]));
        }
        return v[ans];
    }
};
