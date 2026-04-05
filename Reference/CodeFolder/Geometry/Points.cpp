// vector 2d

using ff = float;

struct v2 {
    ff x, y;
    v2(ff x, ff y): x(x), y(y) {}
    bool operator==(v2 const& t) const {
        return x == t.x && y == t.y;
    }
    v2& operator+=(const v2 &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    v2& operator-=(const v2 &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    v2& operator*=(ff t) {
        x *= t;
        y *= t;
        return *this;
    }
    v2& operator/=(ff t) {
        x /= t;
        y /= t;
        return *this;
    }
    v2 operator+(const v2 &t) const {
        return v2(*this) += t;
    }
    v2 operator-(const v2 &t) const {
        return v2(*this) -= t;
    }
    v2 operator*(ff t) const {
        return v2(*this) *= t;
    }
    v2 operator/(ff t) const {
        return v2(*this) /= t;
    }
    ff mag() const {
        return sqrt(x*x + y*y);
    }
    ff sqrmag() const {
        return x*x + y*y;
    }
};

v2 operator*(ff a, v2 b) {
    return b * a;
}

inline ff dot(v2 a, v2 b) {
    return a.x * b.x + a.y * b.y;
}

inline ff cross(v2 a, v2 b) {
    return a.x*b.y - a.y*b.x;
}
