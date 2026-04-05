#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// Se puede usar como un set, tiene todas sus funcionalidades pero agrega dos funciones extra
template <class T>
using oset = tree<T, null_type, less<T>,
                  rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order, order_of_key
// También en vez de less<T> se puede poner greater<T> mayor estricto (>)

int main()
{
  oset<int> A; // declaración

  // Insertar elementos
  A.insert(1);
  A.insert(10);
  A.insert(2);
  A.insert(7);
  A.insert(2); // Solo contiene valores unicos

  // A contains = 1 2 7 10
  cout << "A = ";
  for (auto i : A)
    cout << i << " ";
  cout << endl;

  // Encontrar el kth elemento
  cout << "0th element: " << *A.find_by_order(0) << endl; //  1
  cout << "1st element: " << *A.find_by_order(1) << endl; //  2
  cout << "2nd element: " << *A.find_by_order(2) << endl; //  7
  cout << "3rd element: " << *A.find_by_order(3) << endl; //  10
  auto invalido = A.find_by_order(10);
  if (invalido == A.end())
    cout << "No existe ese elemento" << endl;
  cout << endl;

  // Encontrar el número de elementos menores que x
  cout << "No. of elems smaller than 6: " << A.order_of_key(6) << endl;   //  2
  cout << "No. of elems smaller than 11: " << A.order_of_key(11) << endl; //  4
  cout << "No. of elems smaller than 1: " << A.order_of_key(1) << endl;   //  0
  cout << endl;

  // lower bound -> Primer elemento >= que x
  cout << "Lower Bound of 6: " << *A.lower_bound(6) << endl;
  cout << "Lower Bound of 2: " << *A.lower_bound(2) << endl;
  cout << endl;

  // Upper bound -> Primer elemento > que x
  cout << "Upper Bound of 6: " << *A.upper_bound(6) << endl;
  cout << "Upper Bound of 1: " << *A.upper_bound(1) << endl;
  cout << endl;

  // Eliminar elementos
  A.erase(1);
  A.erase(11); // Eliminar un elemento que no está no hace nada

  // A contains = 2 7 10
  cout << "A = ";
  for (auto i : A)
    cout << i << " ";
  cout << endl;
}
