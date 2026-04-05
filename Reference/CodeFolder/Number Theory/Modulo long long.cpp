#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll MODL = 998244353ll;
struct mll
{
    ll x;
    mll() : x(0) {}
    mll(ll x_) : x((x_ % MODL) + (x_<0?MODL:0)) {}
    inline mll operator+(mll y) const { return mll(x + y.x); }
    inline mll operator*(mll y) const { return mll(x * y.x); }
    inline mll& operator+=(mll y) { x = (x + y.x) % MODL; return *this; }
    inline mll& operator*=(mll y) { x = (x * y.x) % MODL; return *this; }
    inline mll operator/(mll y) const { return mll(x * (y^(MODL-2)).x); }
    inline mll operator^(ll y) const
    {
        mll r = 1;
        mll a = mll(x);
        while (y > 0)
        {
            if (y & 1) r = r * a;
            a *= a;
            y >>= 1;
        }
        return r;
    }
};
ostream& operator<<(ostream& os, mll x) { os << x.x; return os; }
istream& operator>>(istream& is, mll& x) { ll y; is >> y; x = y; return is; }
