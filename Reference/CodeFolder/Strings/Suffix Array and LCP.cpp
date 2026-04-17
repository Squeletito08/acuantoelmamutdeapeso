#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

/*
Suffix Array (SA):
Sea s una cadena de longitud n. El i-ésimo sufijo de s es la subcadena
s[i...n-1]. El Suffix Array contiene los índices de inicio de todos los
sufijos de la cadena, ordenados lexicográficamente.

LCP (Longest Common Prefix) Array:
El valor lcp[i] indica la longitud del prefijo común más largo entre el
sufijo en la posición i y el sufijo en la posición i-1 del Suffix Array
(SA).

txt[0..n-1] = "b a n a n a $"
               0 1 2 3 4 5 6

SA[]  = {6,    5,   3,     1,       0,        4,    2}
      = {"$", "a", "ana", "anana", "banana", "na", "nana"}
        ---------------------------------------------------
índice: 0     1    2      3        4          5      6

LCP[] = {0,    0,   1,     3,       0,        0,    2}
lcp[0] = 0 (no hay sufijo anterior)
lcp[1] = LCP de "$" y "a"          = 0
lcp[2] = LCP de "a" y "ana"        = 1
lcp[3] = LCP de "ana" y "anana"    = 3
lcp[4] = LCP de "anana" y "banana" = 0
lcp[5] = LCP de "banana" y "na"    = 0
lcp[6] = LCP de "na" y "nana"      = 2
*/

struct SuffixArray {
  vi sa, lcp, rank;
  vi log;
  vector<vi> sp;
  int n;

  const int ALPHABET = 256;

  void construct_sparse(int n) {
    log.resize(n + 1);

    log[1] = 0;
    for (int i = 2; i <= n; i++) {
      log[i] = log[i / 2] + 1;
    }

    sp.resize(log[n] + 1, vector<int>(n + 1, 0));

    sp[0] = lcp;

    int k = log[n];
    for (int i = 1; i <= k; i++) {
      for (int j = 0; j + (1 << i) - 1 < n; j++) {
        sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  int query_lcp(int i, int j) {
    if (i == j) {
      return n - sa[i] - 1;
    }
    int l = min(i, j) + 1;
    int r = max(i, j);
    int k = log[r - l + 1];
    return min(sp[k][l], sp[k][r - (1 << k) + 1]);
  }

  SuffixArray(string s) {
    s += '$'; // Debe ser el menor caracter lexicográficamente
    n = s.size();
    sa.resize(n);
    rank.resize(n);
    vi cnt(max(ALPHABET, n), 0);

    // --- Fase Inicial (k = 0): Ordenar por el primer carácter ---
    for (int i = 0; i < n; i++)
      cnt[s[i]]++;
    for (int i = 1; i < ALPHABET; i++)
      cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++)
      sa[--cnt[s[i]]] = i;

    int cls = 1; // Número de clases de equivalencia (grupos de sufijos iguales)
    rank[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      if (s[sa[i]] != s[sa[i - 1]])
        cls++;
      rank[sa[i]] = cls - 1;
    }

    // --- Prefix Doubling: Ordenar por prefijos de longitud 2^h ---
    vi next_sa(n), next_rank(n);
    for (int h = 0; (1 << h) < n; h++) {
      int k = (1 << h);

      // Ordenar por la segunda mitad (shift a la izquierda por k)
      // Esto ya nos da un ordenamiento parcial basado en s[i+k...i+2k-1]
      for (int i = 0; i < n; i++)
        next_sa[i] = (sa[i] - k + n) % n;

      // Counting Sort: Ordenar por la primera mitad usando los ranks actuales
      fill(cnt.begin(), cnt.begin() + cls, 0);
      for (int i = 0; i < n; i++)
        cnt[rank[next_sa[i]]]++;
      for (int i = 1; i < cls; i++)
        cnt[i] += cnt[i - 1];
      for (int i = n - 1; i >= 0; i--)
        sa[--cnt[rank[next_sa[i]]]] = next_sa[i];

      // Generar nuevos ranks comparando pares (rank_izq, rank_der)
      next_rank[sa[0]] = 0;
      cls = 1;
      for (int i = 1; i < n; i++) {
        pair<int, int> cur = {rank[sa[i]], rank[(sa[i] + k) % n]};
        pair<int, int> prev = {rank[sa[i - 1]], rank[(sa[i - 1] + k) % n]};
        if (cur != prev)
          cls++;
        next_rank[sa[i]] = cls - 1;
      }
      rank = next_rank;
      if (cls == n)
        break; // Todos los sufijos ya tienen una posición única
    }
    buildLCP(s);
    construct_sparse(n);
  }

  // Kasai: Calcula LCP aprovechando que LCP(i, j) >= LCP(i-1, j') - 1
  void buildLCP(const string &s) {
    int n = s.size();
    lcp.assign(n, 0);
    int k = 0;
    for (int i = 0; i < n; i++) {
      // El sufijo en la posición rank[i] se compara con el anterior en el SA
      if (rank[i] == 0) {
        k = 0;
        continue;
      }
      int j = sa[rank[i] - 1];
      // Expandir mientras los caracteres coincidan
      while (i + k < n && j + k < n && s[i + k] == s[j + k])
        k++;
      lcp[rank[i]] = k;

      // En la siguiente iteración (sufijo i+1), el LCP será al menos k-1
      k = max(k - 1, 0);
    }
  }
};
