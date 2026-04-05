// algoritmo de graham
using ff = float;

// -1 reloj (derecho), +1 contrarreloj (izquierdo), 0 colineal
int giro(v2 a, v2 b, v2 c) {
    ff v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1;
    if (v > 0) return +1;
    return 0;
}

// regresa lista con el cierre convexo (CH)
vector<v2> cvxhull(vector<v2>& pts) {
    // caso trivial
    if (pts.size() <= 2) return pts;

    // punto mas chico en Y
    v2 p0 = *min_element(pts.begin(), pts.end(), [](const v2& a, const v2& b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    // ord angular con respecto a p0
    sort(pts.begin(), pts.end(), [&p0](const v2& a, const v2& b){
        int g = giro(p0, a, b);
        if (g == 0) {
            // si son colineales, escoge primero el más cercano
            return (p0-a).sqrmag() < (p0-b).sqrmag();
        }
        return g > 0;
    });

    // ordenamos últimos colineales por distancia inversa para evitar que 'vaya y regrese'
    ll i = (ll)pts.size() - 1;
    while (i >= 0 && giro(p0, pts[i], pts.back()) == 0) i--;
    // invertimos los últimos puntos colineales para que aparezcan primero los lejanos
    reverse(pts.begin()+i+1, pts.end());

    vector<v2> cvx; // la pila con el CH
    for (ll j = 0; j < (ll)pts.size(); j++) {
        // eliminamos los que induzcan un giro inválido
        while (cvx.size() > 1 && giro(cvx[cvx.size()-2], cvx.back(), pts[j]) < 0)
            cvx.pop_back();
        cvx.push_back(pts[j]);
    }

    return cvx;
}
