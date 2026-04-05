#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// o_multiset usando un par de {valor, id_unico}
template <class T>
using o_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>,
                        rb_tree_tag, tree_order_statistics_node_update>;

const int INF = INT_MAX; 

int main() {
  o_multiset<int> A;
  int timer = 0; // Variable para asignar IDs únicos

  // --- INSERTAR ---
  A.insert({10, timer++});
  A.insert({2, timer++});
  A.insert({7, timer++});
  A.insert({2, timer++}); 
  A.insert({2, timer++});

  // A: {2, 1}, {2, 3}, {2, 4}, {7, 2}, {10, 0}

  // --- BUSCAR EL K-ÉSIMO ELEMENTO ---
  cout << "0th element: " << A.find_by_order(0)->first << endl; // 2 
  cout << "3rd element: " << A.find_by_order(3)->first << endl; // 7 
  cout << endl;

  // --- ORDER_OF_KEY  ---
  // ¿Cuántos elementos son estrictamente menores que 2?
  // Usamos un ID muy pequeño para obtener el primer par
  cout << "Menores que 2: " << A.order_of_key({2, -1}) << endl; // 0

  // ¿Cuántos elementos son menores o iguales que 2?
  // Usamos un ID muy grande para que incluya todos los {2, id}
  cout << "Menores o iguales que 2: " << A.order_of_key({2, INF})
       << endl; // 3
  cout << endl;

  // --- LOWER Y UPPER BOUND ---
  // Lower Bound de X: primer par >= {X, min_id}
  auto lb = A.lower_bound({2, -1});
  cout << "Lower Bound de 2: {" << lb->first << ", " << lb->second << "}"
       << endl;

  // Upper Bound de X: primer par > {X, max_id}
  auto ub = A.upper_bound({2, INF});
  if (ub != A.end())
    cout << "Upper Bound de 2: {" << ub->first << ", " << ub->second << "}"
         << endl;
  cout << endl;

  // --- ELIMINAR ---
  // Para borrar una sola instancia de '2':
  auto it = A.lower_bound({2, -1});
  if (it != A.end() && it->first == 2) {
    A.erase(it); // Borra el primer '2' que encuentre
  }

  return 0;
}
