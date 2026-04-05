// Si tenemos un polígono con coordenadas enteras y conocemos el número de
// puntos (con coordenadas enteras) internos y en la frontera, podemos obtener
// su área en O(1):
int pick_area(int internos, int en_frontera)
{
    return internos + en_frontera/2 - 1;
}

// Podemos obtener los puntos con coordenadas enteras en la frontera en O(n):
int boundary_points(const vector<pair<int, int>>& P) {
    int n = P.size();
    int B = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        int dx = abs(P[i].first - P[j].first);
        int dy = abs(P[i].second - P[j].second);
        B += __gcd(dx, dy); // tecnicamente O(log(min(dx,dy)))
    }
    return B;
}

// Si conocemos el área y los puntos en la frontera, podemos obtener internos.
// Tomamos 2 veces el área porque podemos obtenerla sin floats con shoelace
int pick_internos(int area2x, int en_frontera)
{
    return (area2x - en_frontera + 2)/2;
}

// asi...
ll shoelace_area2x(const vector<pair<int,int>>& P)
{
    int n = P.size();
    ll area2x = 0;
    for (int i = 0; i < n; ++i)
    {
        int j = (i+1)%n;
        area2x += 1LL * P[i].first * P[j].second;
        area2x -= 1LL * P[j].first * P[i].second;
    }
    return abs(area2x);
}
