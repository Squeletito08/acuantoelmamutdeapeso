using ll = long long;
using dig_adj = vector<vector<ll>>;
using vll = vector<ll>;

void dfsa_aux(dig_adj &d, vll &pred, vll &tvisit, vll &texpl, vll &verts, ll &time, ll &i, ll v);
/**
 * Algoritmo de Knuth para ordenamiento acíclico. O(n+m). Variación de DFS.
 *
 * Sea D una digráfica y sea x_1, x_2, ..., x_n un ordenamiento de sus vértices.
 * Decimos que el ordenamiento es acíclico si para cada flecha x_ix_j en D, i<j.
 * Existe si y sólo si la digráfica no tiene un ciclo dirigido.
 *
 * Como toda digráfica acíclica tiene fuente y sumidero, la idea del algoritmo
 * es escoger fuentes, "quitarlas" y repetir.
 *
 * Como este algoritmo es correcto si la digráfica es acíclica, se puede
 * verificar si la digráfica es acíclica al ejecutarlo y revisar si el
 * ordenamiento es acíclico.
 *
 * Este algoritmo es auxiliar al algoritmo de componentes fuertemente conexas.
 */
vll dfsa(ll n, dig_adj &d)
{
    // pred - predecesor || tvisit - tiempo de visita || texpl - tiempo de exploración
    vll pred(n,-1), tvisit(n,0), texpl(n,0), verts(n,-1);
    ll time = 0, i = n;

    for (ll v = 0; v < n; v++)
    {
        if (tvisit[v]) continue;
        dfsa_aux(d, pred, tvisit, texpl, verts, time, i, v);
    }

    /**
     * Hasta aquí tenemos:
     *   lista de predecesores - pred
     *   tiempos de visita de cada vértice - tvisit
     *   tiempo en el que se explora (tras sus hijos) el vértice - texpl
     *   el ordenamiento acíclico - verts
     */
    return verts;
}
// Auxiliar que realiza la búsqueda por profundidad recursivamente
void dfsa_aux(dig_adj &d, vll &pred, vll &tvisit, vll &texpl, vll &verts, ll &time, ll &i, ll v)
{
    tvisit[v] = ++time;
    for (ll u : d[v])
    {
        if (tvisit[u]) continue;
        pred[u] = v;
        dfsa_aux(d, pred, tvisit, texpl, verts, time, i, u);
    }
    texpl[v] = ++time;
    verts[--i] = v;       
}
