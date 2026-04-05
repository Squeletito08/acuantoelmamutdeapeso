/**
 *
 * Problema de cerradura/clausura máxima (o mínima):
 *
 * Una cerradura C de una digráfica D es un conjunto de V(D) tal que no hay
 * flecha que salga de C.
 *
 * El problema de clausura máxima (o análogamente mínima) se trata de encontrar
 * C de peso máximo (o análogamente mínimo), con pesos sobre los vértices.
 *
 * Para pasar de un problema de clausura mínima a clausura máxima, la clausura
 * mínima es equivalente a la clausura máxima de la digráfica conversa (i.e. con
 * las flechas al revés).
 *
 * Para resolver el problema y encontrar el peso de la cerradura máxima se construye
 * la red de flujo con las mismas flechas que D y peso infinito, con los vértices
 * nuevos S y T, que todo vértice v con peso positivo tiene una flecha de S a v
 * con el peso de v, y todo vértice v con peso negativo tiene una flecha de v a
 * T con el valor absoluto del peso de v.
 *
 * El peso de la cerradura máxima es la suma de todos los pesos positivos menos
 * el flujo máximo de la red. Esto corresponde con el corte mínimo necesario
 * del valor máximo, i.e. que es lo menos que podemos "sacrificar" del peso
 * máximo posible.
 *
 * Los vértices en la cerradura máxima son aquellos que están del lado de S en
 * el corte mínimo.
 *
 */
using dig_adj = vector<vector<ll>>;
constexpr ll inf = 1e17;

ll peso_cerradura_max(ll n, dig_adj g, vector<ll> costs)
{
    // Le asignamos a S y T los índices n y n+1
    ll s = n, t = n + 1;
    Dinic flujo(n + 2, s, t);
    // Agrega las aristas en la gráfica
    for (ll v = 0; v < n; v++)
    for (ll u : g[v])
    {
        flujo.add(v, u, inf);
    }
    // Agrega los costos
    for (ll v = 0; v < n; v++)
    {
        ll c = costs[v];
        if (c > 0)
        {
            flujo.add(s, v, c);
        }
        else if (c < 0)
        {
            flujo.add(v, t, -c);
        }
    }

    // Suma de costos
    ll suma = 0;
    for (ll c : costs) if (c > 0) suma += c;

    return suma - flujo.maxFlow();
}
