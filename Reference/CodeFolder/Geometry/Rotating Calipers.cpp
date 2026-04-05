// Con el método de rotating calipers se puede encontrar rápidamente (en O(n)):
// - parejas antipodales (más lejanas) de un polígono convexo
// - diámetro de un polígono convexo
// - cierre convexo de puntos (divide y vencerás O(nlogn))
// - caja acotadora orientada de menor área y de menor perímetro
// - anchura mínima de un polígono convexo
// - cierre convexo de polígonos convexos
// - máxima y mínima distancia entre dos polígonos convexos
// - tira vacía más ancha que separa dos polígonos convexos
// - algunos tipos de triangulaciones y iluminación de galería de arte
// - unión/intersección de polígonos convexos
// - tangentes comunes de polígonos convexos
// - suma de minkowski de polígonos convexos

#include <bits/stdc++.h>
using namespace std;
using tt = float; // el tipo de coordenadas, puede ser int, double, etc, pero
                  // debe entrar el cuadrado de cualquier coordenada.
constexpr tt EPS = 1e-9; // si es int/ll debería ser cero

struct pt{ tt x, y; };
inline pt operator+(const pt& a, const pt& b) {
    return {a.x+b.x, a.y+b.y};
}
inline pt operator-(const pt& a, const pt& b) {
    return {a.x-b.x, a.y-b.y};
}
inline pt operator*(const pt& a, tt b) {
    return {a.x*b, a.y*b};
}
inline bool operator<(const pt& a, const pt& b) {
    return (a.x < b.x) || (abs(a.x-b.x)<=EPS && a.y < b.y);
}

// índice cíclico a un arreglo
inline int Z(int n, const vector<pt>& ps) { return (n+ps.size()) % ps.size(); }

inline tt turn(pt a, pt b, pt c) {
    pt u = {b.x-a.x, b.y-a.y};
    pt v = {c.x-b.x, c.y-b.y};
    return u.x*v.y - u.y*v.x;
}

inline tt turn(const vector<pt>& ps, int a, int b, int c) {
    return turn(ps[Z(a,ps)], ps[Z(b,ps)], ps[Z(c,ps)]);
}

inline tt dot(const pt& a, const pt& b) {
    return a.x*b.x + a.y*b.y;
}

inline tt cmp_turns(const vector<pt>& ps, int i, int j) {
    return turn(ps, i, i+1, j+1) - turn(ps, i, i+1, j);
}

// encuentra todas las parejas antipodales si ps es un polígono convexo en el
// sentido de turn positivo y sin puntos colineales (elimínalos tú primero)
//
// O(n)
vector<pair<int,int>> antipodal(const vector<pt>& ps)
{
    vector<pair<int,int>> ans;
    int n = ps.size();
    if (n < 2) return ans;
    int i = n-1;
    int j = i+1;
    while (cmp_turns(ps,i,j) > EPS) j++;
    int j0 = j;
    do {
        i++;
        ans.push_back({Z(i,ps),Z(j,ps)});
        while (cmp_turns(ps,i,j) > EPS) {
            j++;
            if (i != j0 || j != 1)
                ans.push_back({Z(i,ps), Z(j,ps)});
        }
        if (abs(cmp_turns(ps,i,j)) <= EPS && (i!=j0 || j!=n-1))
            ans.push_back({Z(i,ps), Z(j+1,ps)});
    } while (i != j0);
    return ans;
}

// diámetro cuadrado de polígono convexo
// ps polígono convexo, positivo en turn, sin puntos colineales
//
// O(n)
tt diam_sqr(const vector<pt>& ps) {
    tt m = 0;
    for (auto [i, j] : antipodal(ps)) {
        tt dx = ps[i].x-ps[j].x;
        tt dy = ps[i].y-ps[j].y;
        m = max(m, dx*dx + dy*dy);
    }
    return m;
}

// Encuentra dados dos polígonos convexos el "puente" superior/inferior que los
// une en su cierre convexo. Nótese que la figura convexa izquierda y derecha
// deben tener una vertical que los separe perfectamente y no deben haber puntos
// encimados.
//
// si dir=1 es el puente de arriba y si dir=-1 es el puente de abajo
//
// O(n)
pair<int,int> hull_caliper(const vector<pt>& l, const vector<pt>& r, int dir) {
    // comenzamos con el más derecho de la izq y el más izquierdo de la der
    int li = 0; for (int i = 1; i < l.size(); i++) if (l[li] < l[i]) li = i;
    int ri = 0; for (int i = 1; i < r.size(); i++) if (r[i] < r[ri]) ri = i;
    bool ch = false; // changed?
    do {
        ch = false;
        int nr, nl;
        while (turn(l[li],r[ri],r[nr = Z(ri-dir,r)]) > dir*EPS) {
            ch = true;
            ri = nr;
        }
        while (turn(r[ri],l[li],l[nl = Z(li+dir,l)]) < -dir*EPS) {
            ch = true;
            li = nl;
        }
    } while (ch);
    return {li, ri};
}

// Encuentra el cierre convexo de dos polígonos convexos en O(n) si existe una
// vertical que los separa en izquierdo y derecho que no cruzan, y si no tienen
// puntos encimados.
vector<pt> hull_merge(const vector<pt>& l, const vector<pt>& r) {
    vector<pt> hull;
    auto [hil, hir] = hull_caliper(l, r, 1);
    auto [lol, lor] = hull_caliper(l, r, -1);
    for (int i = hil; i != lol; i = Z(i+1,l))
        hull.push_back(l[i]);
    hull.push_back(l[lol]);
    for (int i = lor; i != hir; i = Z((i+1),r))
        hull.push_back(r[i]);
    hull.push_back(r[hir]);
    return hull;
}

// ps es un polígono CONVEXO, si tu polígono no es convexo, toma el CH
// NOTE: para esto necesitaremos que tt sea de punto flotante, pues la caja puede
//       tener una orientación rotada cualquier ángulo aunque los puntos tengan
//       coordenadas enteras, lo cual complica el garantizar cerradura entera.
// NOTE: la caja de mínimo perímetro es idéntico el proceso pero minimizamos el
//       perímetro en lugar del área {{2(w+h) en lugar de w*h}}
vector<pt> min_obbox(const vector<pt>& ps) {
    // https://geidav.wordpress.com/tag/rotating-calipers/
    // NOTE: manejar casos triviales n < 3
    int n = ps.size();
    int j=0,k=0,l=0,m=0; // segmento, opuesto, top, bottom (las 4 calipers)
    tt A = numeric_limits<tt>::max(); // área inicial
    vector<pt> ans(4); // el AABB tras rotar
    // tratamos de girar las cuatro líneas
    for (int i = 0; i < n; i++) {
        // i es min en x
        pt dir = Z(i+1,ps)-Z(i,ps); // normalizar?
        pt perp = {-dir.y,dir.x};
        while (turn(ps,i,i+1,k+1) > turn(ps,i,i+1,k)) k++;
        while (dot(perp, Z(l+1,ps)-Z(i,ps)) > dot(perp, Z(l,ps) - Z(i,ps))) l++;
        while (dot(perp, Z(m+1,ps)-Z(i,ps)) > dot(perp, Z(m,ps) - Z(i,ps))) m++;
        tt minx = dot(ps[i], dir);
        tt maxx = dot(Z(k,ps),dir);
        tt miny = dot(Z(m,ps),perp);
        tt maxy = dot(Z(l,ps),perp);
        tt w = maxx - minx;
        tt h = maxy - miny;
        long double inv = 1.0l/dot(dir,dir);
        tt A2 = w*h*inv;
        if (A2 < A) {
            A = A2;
            j = i;
            ans[0] = dir*minx*inv + perp*miny*inv;
            ans[1] = dir*maxx*inv + perp*miny*inv;
            ans[2] = dir*minx*inv + perp*maxy*inv;
            ans[3] = dir*maxx*inv + perp*maxy*inv;
        }
    }
    return ans;
}

// TODO: https://www.cs.jhu.edu/~misha/Spring16/ORourke82.pdf
