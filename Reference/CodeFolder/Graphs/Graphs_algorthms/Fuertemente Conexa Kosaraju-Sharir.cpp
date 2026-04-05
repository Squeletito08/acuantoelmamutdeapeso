// NOTE: Hace uso de Acyclic Ordering (dfsa)

using ll = long long;
using dig_adj = vector<vector<ll>>;
using vll = vector<ll>;

void sca_aux(dig_adj &conv, vll &pred, vll &tvisit, vll &texpl, ll &time, vll &componente, ll comp_idx, ll v);
/**
 * Componentes fuertemente conexas (Kosaraju-Sharir). O(n+m). Variación de DFS.
 *
 * Además, construimos la gráfica de bloques fuertes pero se indica en un
 * comentario donde podemos deternernos si sólo queremos las componentes.
 * A veces a esto se le llama la condensación de la digráfica.
 *
 * Aquí estoy realizando una pequeña modificación para el problema: construyo
 * la digráfica de bloques fuertes con el costo acumulado de todos los vértices
 * en cada bloque (pues todo bloque únicamente puede ser elegido todo junto).
 *
 * Recuerde que la digráfica conversa es la que tiene las flechas invertidas
 */
dig_adj sca(ll n, dig_adj &d, dig_adj &d_converse)
{
    vll ord_aciclico = dfsa(n, d);

    // pred - predecesor || tvisit - tiempo de visita || texpl - tiempo de exploración
    vll pred(n,-1), tvisit(n,0), texpl(n,0);
    vll componente(n,-1); // a cuál componente pertenece cada vértice
    ll time = 0, componente_idx = 0;

    // La consulta de los vértices debe ser sobre el orden acíclico
    for (ll v : ord_aciclico)
    {
        if (tvisit[v]) continue;
        sca_aux(d_converse, pred, tvisit, texpl, time, componente, componente_idx++, v);
    }

    /**
     * Hasta aquí tenemos:
     *   lista de predecesores - pred
     *   tiempos de visita de cada vértice - tvisit
     *   tiempo en el que se explora (tras sus hijos) el vértice - texpl
     *   a qué componente pertenece cada vértice - componente
     *   cuántas componentes hay - componente_idx
     */

    dig_adj bloques(componente_idx);
    // Revisamos todas las aristas y agregamos las que unen componentes
    for (ll u = 0; u < n; u++)
    for (ll v : d[u])
    {
        ll cu = componente[u];
        ll cv = componente[v];
        if (cu == cv) continue;
        bloques.m++;
        bloques[cu].push_back(cv);
    }

    return bloques;
}
// Auxiliar que realiza la búsqueda por profundidad recursivamente
void sca_aux(dig_adj &conv, vll &pred, vll &tvisit, vll &texpl, ll &time, vll &componente, ll comp_idx, ll v)
{
    tvisit[v] = ++time;
    componente[v] = comp_idx;
    for (ll u : conv[v])
    {
        if (tvisit[u]) continue;
        pred[u] = v;
        sca_aux(conv, pred, tvisit, texpl, time, componente, comp_idx, u);
    }
    texpl[v] = ++time;
}
