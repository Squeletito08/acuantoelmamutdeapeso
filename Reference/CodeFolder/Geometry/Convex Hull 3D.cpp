#include <bits/stdc++.h>
using namespace std;
using ftype = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;
template <typename T> inline int sz(const T& x) { return (int) (x).size(); }
template <typename T> using minpq = priority_queue<T, vector<T>, greater<T>>;

// para double usualmente 1e-9 está bien, para long double 1e-12 o 1e-18 es mejor
constexpr ftype EPS = 1e-9; // modificable :)

struct p3
{
    ftype x,y,z;
    p3(ftype x = 0, ftype y = 0, ftype z = 0) : x(x), y(y), z(z) {}
    inline p3 operator-() const { return p3(-x,-y,-z); }
    inline p3 operator+(const p3& o) const { return p3(x+o.x, y+o.y, z+o.z); }
    inline p3 operator-(const p3& o) const { return (*this) + (-o); }
    inline ftype operator*(const p3& o) const { return x*o.x+y*o.y+z*o.z; }
    ftype mag() const { return hypot(x,y,z); } // hypot 3D aparece en C++17
    inline p3 operator^(const p3& o) const {
        return p3(y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x);
    }
};

struct edge;
constexpr int VIVA = 1e9;
// Necesitamos info de caras adyacentes para no forzosamente llegar al O(n^2)
// e1=(a,b), e2=(b,c), e3=(c,a)
// points es los futuros puntos que pueden ver la cara
// dead es el índice del vértice que la borrará o 1e9 si sigue viva
struct face
{
    int a,b,c;
    p3 q;
    edge *e1, *e2, *e3;
    vi points;
    int dead = VIVA;

    face(int a, int b, int c, p3 q) : a(a), b(b), c(c), q(q) {
        e1 = e2 = e3 = 0;
    }
};
// Usaremos algo similar a una DCEL con cara a la que entra y arista gemela
struct edge
{
    edge *twin;
    face *f;
};

// Pegamos dos caras, produciendo ambas aristas gemelas de su unión
void pega(face *f1, face *f2, edge *&e1, edge *&e2)
{
    e1 = new edge;
    e2 = new edge;
    e1->twin = e2;
    e2->twin = e1;
    e1->f = f2;
    e2->f = f1;
}

// Esta estructura se encuentra en la sección Numeric
pcg32 rng; // O bien, en su lugar:
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// hace el shuffle de los puntos para tener nlogn esperado, asegurándose que los
// primeros 4 puntos formen un simplex no degenerado
void ch_setup(vector<p3>& ps)
{
    int n = sz(ps);
    shuffle(ps.begin(), ps.end(), rng);
    vi ve; // el simplex inicial como una lista de índices de puntos
    ve.push_back(0);
    // vamos agregando puntos uno a uno al simplex mientras no quede degenerado
    for (int i = 0; i < n && sz(ve) < 4; i++)
        if (sz(ve) == 1)
            if ((ps[ve[0]] - ps[i]).mag() > EPS)
                ve.push_back(i);
        else if (sz(ve) == 2)
            if (((ps[ve[1]] - ps[ve[0]]) ^ (ps[i] - ps[ve[0]])).mag() > EPS)
                ve.push_back(i);
        else if (abs(
                   (ps[i] - ps[ve[0]]) * 
                   ( (ps[ve[1]] - ps[ve[0]]) ^ (ps[ve[2]] - ps[ve[0]]) )
                 ) > EPS)
            ve.push_back(i);
    assert(sz(ve) == 4); // si todo simplex es degenerado, error
    vector<p3> ve2; // el simplex inicial como una lista de puntos
    for (int i : ve) ve2.push_back(ps[i]);
    reverse(ve.begin(), ve.end());
    // mueve los 4 puntos del simplex al inicio
    for (int i : ve) ps.erase(ps.begin() + i);
    ps.insert(ps.begin(), ve2.begin(), ve2.end());
}

vector<face*> hull3(vector<p3> &ps)
{
    int n = sz(ps);
    ch_setup(ps);
    vector<face*> f, new_face(n,0);

    // conf[i] es la lista de conflictos del punto i (las caras que puede ver)
    // conf[i] puede tener caras eliminadas, que debemos ignorar
    vector<vector<face*>> conf(n);
    auto add_face = [&](int a, int b, int c) {
        face *F = new face(a,b,c, (ps[b] - ps[a]) ^ (ps[c] - ps[a]));
        f.push_back(F);
        return F;
    };

    // comenzamos con un triangulo con una cara por ambos lados (orient. op.).
    // imagina que es una rebanadita de sandwich en triangulito sin grosor
    face *F1 = add_face(0,1,2);
    face *F2 = add_face(0,2,1);
    pega(F1, F2, F1->e1, F2->e3);
    pega(F1, F2, F1->e2, F2->e2);
    pega(F1, F2, F1->e3, F2->e1);

    // a cada punto le agregamos la cara que ve a su lista de conflictos
    for (int i = 3; i < n; ++i)
    for (face *F : {F1, F2})
    {
        // si ^ es el producto de Grassman, i es el punto actual, (a,b,c)
        // son los puntos que forman la cara, entonces
        //      Q = (i - a)^(b - a)^(c - a)
        // i.e. es el volumen orientado del paralelepípedo del simplex
        ftype Q = (ps[i] - ps[F->a]) * F->q;
        // si la orientación del simplex es positiva, entonces el punto puede
        // ver la cara, ya que no la cruza por atrás
        if (Q > EPS) conf[i].push_back(F);
        // si la orientación del simplex es positiva o aprox 0, entonces
        // diremos el punto puede ver la cara desde la perspectiva de la
        // cara. esto tiene que ser así porque comenzamos con el trig
        // degenerado y hay un plano en el que técnicamente no ve a nadie,
        // pero sí queremos darle a ambas caras sus puntos
        if (Q >= -EPS) F->points.push_back(i);
    }

    // las iteraciones incrementales
    for (int i = 3; i < n; ++i)
    {
        // marca las caras visibles para i como muertas x.x
        for (face *F : conf[i]) F->dead = min(F->dead, i);

        // las aristas que incidan en una cara viva y una muerta son las que
        // van a ser conectadas con el nuevo punto
        int v = -1; // último pt sobre el cual agregamos una cara
        for (face *F : conf[i])
        {
            if (F->dead != i) continue; // murió antes
            int parr[3] = {F->a, F->b, F->c}; // puntos de la cara indexables
            edge* earr[3] = {F->e1, F->e2, F->e3}; // aristas de la cara " "

            for (int j = 0; j < 3; ++j)
            {
                int j2 = (j + 1) % 3;
                // como F está muerta, si otra cara en que incide alguna de sus
                // aristas está viva, entonces esa arista hay que conectarla con
                // una nueva cara a i
                if (i < earr[j]->f->dead)
                {
                    // la nueva cara
                    face *Fn = new_face[parr[j]] = add_face(parr[j], parr[j2], i);
                    // agregamos a la cara nueva los puntos que pueden ver a su
                    // incidencia o a la que tapó
                    set_union(
                        (F->points).begin(), (F->points).end(),
                        (earr[j]->f->points).begin(), (earr[j]->f->points).end(),
                        back_inserter(Fn->points)
                    );
                    // eliminamos los puntos que sobraron y no ven realmente a
                    // la cara nueva
                    Fn->points.erase(stable_partition(
                        (Fn->points).begin(), (Fn->points).end(), [&](int k) {
                            return k > i && (ps[k] - ps[Fn->a]) * Fn->q > EPS;
                        }
                    ), (Fn->points).end());
                    // agregamos la nueva cara a la lista de conflictos de los
                    // puntos que la ven
                    for (int k : Fn->points)
                        conf[k].push_back(Fn);
                    // asignamos la cara nueva como la incidencia de la gemela
                    earr[j]->twin->f = Fn;
                    // asignamos la arista a la cara nueva
                    Fn->e1 = earr[j];
                    // recordamos el último punto sobre el cual agregamos cara
                    v = parr[j];
                }
            }
        }

        if (v == -1) continue; // el punto está al interior del CH

        // pegamos todas las nuevas caras (new_face)
        while (!new_face[v]->e2)
        {
            int u = new_face[v]->b;
            pega(new_face[v], new_face[u], new_face[v]->e2, new_face[u]->e3);
            v = u;
        }
    }

    // eliminamos las caras muertas x.x
    f.erase(remove_if(f.begin(), f.end(), [&](face *F) {
        return F->dead < n;
    }), f.end());
    return f;
}
