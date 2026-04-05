// O(logi) cada inserción, O(logi) consulta, O(nlogn) construcción total
struct pt
{
    ll x, y;
    pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}
    bool operator<(const pt p) const // ord lexicográfico
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    inline bool operator==(const pt p) const { return x == p.x and y == p.y; }
    inline pt operator+(const pt p) const { return pt(x+p.x, y+p.y); }
    inline pt operator-(const pt p) const { return pt(x-p.x, y-p.y); }
    inline pt operator*(const ll c) const { return pt(c*x, c*y); }
    inline ll operator*(const pt p) const { return x*p.x + y*p.y; } // producto interior
    inline int operator^(const pt p) const // signo del producto exterior
    {
        // NOTE: esto debe modificarse a según. estos productos fácilmente
        //       podrían ser muy grandes, por lo que se podría quizás adaptar
        //       como...
        //   --> long double l = x*(long double)p.y; // y análogamente para r
        //   --> long long l = x*p.y; // y análogamente para r
        //   --> dejarlo así y definir i128
        // x*p.y - y*p.x
        i128 l = mul_ll(x, p.y);
        i128 r = mul_ll(y, p.x);
        if (l == r) return 0;
        if (l < r) return -1;
        return 1;
    }
    friend istream& operator>>(istream& in, pt& p)
    {
        return in >> p.x >> p.y;
    }
};

bool ccw(pt p, pt q, pt r)
{
    return ((q-p)^(r-q)) > 0;
}

struct upper
{
    set<pt> se;
    set<pt>::iterator it;

    int is_under(pt p) // 1 -> in ; 2 -> border
    {
        it = se.lower_bound(p);
        if (it == se.end()) return 0;
        if (it == se.begin()) return p == *it ? 2 : 0;
        if (ccw(p, *it, *prev(it))) return 1;
        return ccw(p, *prev(it), *it) ? 0 : 2;
    }
    void insert(pt p)
    {
        if (is_under(p)) return;
        if (it != se.end()) while (next(it) != se.end() and !ccw(*next(it), *it, p))
            it = se.erase(it);
        if (it != se.begin()) while (--it != se.begin() and !ccw(p, *it, *prev(it)))
            it = se.erase(it);
        se.insert(p);
    }
};

struct dyn_hull
{
    upper U,L;

    int is_inside(pt p) // 1 -> in ; 2 -> border
    {
        int u = U.is_under(p), l = L.is_under({-p.x, -p.y});
        if (!u or !l) return 0;
        return max(u,l);
    }
    void insert(pt p)
    {
        U.insert(p);
        L.insert({-p.x, -p.y});
    }
    int size()
    {
        int ans = U.se.size() + L.se.size();
        return ans <= 2 ? ans/2 : ans-2;
    }
};

