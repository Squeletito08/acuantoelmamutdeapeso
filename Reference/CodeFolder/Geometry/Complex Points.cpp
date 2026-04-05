#include <complex>
// definimos un punto como un complejo
//typedef long long C; // no nos sirve para algunos trucos como abs y arg
typedef long double C;
typedef complex<C> P;
#define X real()
#define Y imag()
#define C_EPS 1e-12

// no importa si C es punto flotante
inline bool operator<(P a, P b) { return a.X < b.X || (a.X == b.X && a.Y < b.Y); }
inline C cross(P a, P b) { return (conj(a)*b).Y; }
inline C dir(P u, P v, P w) { return cross(v-u,w-v); }
inline bool ccw(P u, P v, P w) { return dir(u,v,w) > C_EPS; }
inline bool cw(P u, P v, P w) { return dir(u,v,w) < -C_EPS; }
inline bool colin(P u, P v, P w)
{ C d = dir(u,v,w); return -C_EPS <= d && d <= C_EPS; }
int seg_intersect(P a, P b, P c, P d)
{ // 0.ab no toca cd.
  // 1.se tocan solo en un extremo.
  // 2.son colineales y se tocan infinitas veces.
  // 3.se tocan al interior de alguno exactamente una vez.
    if (colin(a,b,c) && colin(a,b,d))
    {
        if (c > d) swap(c,d);
        if (a > b) swap(a,b);
        if (abs(b-c) <= C_EPS || abs(d-a) <= C_EPS) return 1;
        if (a < c && c < b) return 2;
        if (c < a && a < d) return 2;
        return 0;
    }
    if (abs(a-c)<=C_EPS || abs(a-d)<=C_EPS || abs(b-c)<=C_EPS || abs(b-d)<=C_EPS)
        return 1;
    if (dir(a,b,c)*dir(a,b,d) < 0 && dir(c,d,a)*dir(c,d,b) < 0)
        return 3;
    return 0;
}
// solo si C es punto flotante
inline C dist(P a, P b) { return abs(b-a); }
inline C dist_pt_line(P l1, P l2, P p) { return cross(l1-p,l2-p)/dist(l1,l2); }
inline C angle_xaxis(P p) { return arg(p); }
inline P polr(C mag, C angle) { return polar(mag,angle); }
inline P rotated(P v, C angle) { return v*polar(1,angle); }

int main()
{
    P p = {3,-4};
    cout << "p: " << p.X << ' ' << p.Y << endl; // mostramos parte X y Y
    return 0;
}
