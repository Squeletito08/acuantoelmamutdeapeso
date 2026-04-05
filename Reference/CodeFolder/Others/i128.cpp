// si no esta disponible
// typedef __int128_t lll;

// algunas operaciones que simulan int de 128 bits
using u64 = unsigned long long;

struct u128 { u64 hi, lo; };

// multiplica dos unsigned long long sin desborde
u128 mul_u64(u64 a, u64 b) {
    constexpr u64 MASK32 = 0xFFFFFFFF;

    u64 a_lo = a & MASK32;
    u64 a_hi = a >> 32;
    u64 b_lo = b & MASK32;
    u64 b_hi = b >> 32;

    u64 lo_lo = a_lo * b_lo;
    u64 hi_lo = a_hi * b_lo;
    u64 lo_hi = a_lo * b_hi;
    u64 hi_hi = a_hi * b_hi;

    u64 cross = hi_lo + lo_hi;
    bool carry1 = cross < hi_lo;

    u64 cross_lo = cross << 32;
    u64 lo = lo_lo + cross_lo;
    bool carry2 = lo < lo_lo;

    u64 hi = hi_hi + (cross >> 32) + carry1 + carry2;

    return { hi, lo };
}

// int de 128 bits con signo
struct i128
{
    u64 hi, lo;
    bool neg;
    inline bool operator==(const i128& o) const
    {
        return hi == o.hi and lo == o.lo and (neg == o.neg or (hi == 0 and lo == 0));
    }
    bool operator<(const i128& o) const
    {
        if (*this == o) return false;
        if (hi == 0 and lo == 0) return !o.neg;
        if (o.hi == 0 and o.lo == 0) return neg;
        if (neg != o.neg) return neg;
        if (hi < o.hi) return !neg;
        if (hi > o.hi) return neg;
        if (lo < o.lo) return !neg;
        if (lo > o.lo) return neg;
        return false;
    }
};

// multiplica dos long long sin desborde
i128 mul_ll(ll a, ll b)
{
    bool neg = (a<0) ^ (b<0);
    u128 res = mul_u64(llabs(a), llabs(b));
    return { res.hi, res.lo, neg };
}
