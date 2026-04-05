// encuentra la pareja de puntos más cercana en O(nlogn)

#include <bits/stdc++.h>
using namespace std;
#define ALL(x) x.begin(), x.end()

// se pueden cambiar para que funcione con double o float
using fl = long double;
#define HYPOT hypotl
#define ABS fabsl

struct pt;
using vpt = vector<pt>;
using ppt = pair<pt,pt>;
constexpr fl INF = numeric_limits<fl>::infinity();

struct pt { fl x, y; }; // aquí se podría poner más info extra a según
bool cmpx(const pt& a, const pt& b) { return a.x < b.x; }
bool cmpy(const pt& a, const pt& b) { return a.y < b.y; }
fl dist(const pt& a, const pt& b) { return HYPOT(a.x-b.x, a.y-b.y); }

// se usa para escoger pares
inline const pair<ppt,fl>& best_pair(const pair<ppt,fl>& a, const pair<ppt,fl>& b)
{
    return b.second < a.second ? b : a;
}

// para crear pares de puntos con su distancia
inline pair<ppt, fl> mk_p(const pt& a, const pt& b)
{
    return {{a, b}, dist(a,b)};
}

// se usa para el caso base, es O(1) en ese contexto
inline pair<ppt,fl> closest_brute(const vpt& P, int start, int end)
{
    pair<ppt,fl> p = {{P[start],P[start]}, INF};
    for (int i = start; i < end; ++i)
    for (int j = i+1; j < end; ++j)
        p = best_pair(p, mk_p(P[i], P[j]));
    return p;
}

// suena O(n^2), pero por matemagia divertida esto es realmente O(1) en el
// contexto de la función completa, y está por ahí de 7 y 12 la cota superior
inline pair<ppt,fl> strip_closest(const vpt& strip, pair<ppt,fl> closest)
{
    for (int i = 0; i < strip.size(); ++i)
    for (int j = i+1; j < strip.size() and (strip[j].y - strip[i].y) < closest.second; ++j)
        closest = best_pair(closest, mk_p(strip[i], strip[j]));
    return closest;
}

pair<ppt,fl> aux_closest_pair(const vpt& Px, const vpt& Py, int start, int end)
{
    // caso base O(1)
    if (end-start <= 3) return closest_brute(Px, start, end);

    int mid = start + ((end-start)>>1);
    pt midpt = Px[mid];

    // Dividimos en izq y der el ordenamiento vertical O(n)
    vpt Pyl, Pyr;
    Pyl.reserve(mid-start); Pyr.reserve(end-mid+1);
    for (const pt& p : Py)
        if (p.x <= midpt.x) Pyl.push_back(p);
        else Pyr.push_back(p);

    // divide
    auto closest = best_pair(aux_closest_pair(Px, Pyl, start, mid),
            aux_closest_pair(Px, Pyr, mid, end));

    // vencerás: la pareja es una de las mitades, o cruza la franja media
    vpt strip;
    for (const pt& p : Py) // O(n)
        if (ABS(p.x - midpt.x) < closest.second)
            strip.push_back(p);
    return strip_closest(strip, closest);
}

inline pair<ppt,fl> closest_pair(vpt& P) // O(nlogn) divide y vencerás
{
    vpt Px(P), Py(P);
    sort(ALL(Px), cmpx); sort(ALL(Py), cmpy);
    return aux_closest_pair(Px, Py, 0, P.size());
}
