// O(nlogC) con C el máximo |x_i|
// Para funciones que se intersectan a lo más una vez, nos da el min de
// todas ellas en tiempo logaritmico (por ejemplo para encontrar el CH de
// varias rectas)
typedef long long C; // esto se puede cambiar
typedef complex<C> P;
#define X real()
#define Y imag()

C dot(P a, P b) {
    return (conj(a) * b).X;
}

// rectas por ejemplo, pero puede ser otra fn
C f(P a,  C x) {
    return dot(a, {x, 1});
}

const int maxn = 2e5; // max número de funciones 

P line[4 * maxn]; // segment tree del arreglo de lineas

void add_line(P nw, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[v], l);
    bool mid = f(nw, m) < f(line[v], m);
    if(mid) {
        swap(line[v], nw);
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * v, l, m);
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}

C get(int x, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(line[v], x);
    } else if(x < m) {
        return min(f(line[v], x), get(x, 2 * v, l, m));
    } else {
        return min(f(line[v], x), get(x, 2 * v + 1, m, r));
    }
}

// para agregar líneas: add_line({m, b})
// para obtener el mínimo del arreglo de líneas en x: get_line(x)
