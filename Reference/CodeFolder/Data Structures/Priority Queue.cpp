struct Comparador
{
  bool operator()(const pair<int, string> &a, const pair<int, string> &b)
  {
    return a.first > b.first; // Ordenar por el primer valor del par (min-heap por valor de entero)
  }
};

int main()
{
  // Crear una priority_queue con el comportamiento por defecto (max-heap)
  priority_queue<int> pqMax;

  // Insertar elementos en el max-heap
  pqMax.push(5);
  pqMax.push(2);
  pqMax.push(8);
  pqMax.push(1);
  pqMax.push(3);

  cout << "Elementos en el max-heap (prioridad alta a baja):" << endl;

  // Extraer elementos (se extrae el de mayor valor primero)
  // 8 5 3 2 1
  while (!pqMax.empty())
  {
    cout << pqMax.top() << " "; // Muestra el elemento de mayor prioridad (en max-heap, el más grande)
    pqMax.pop();                // Elimina el elemento de mayor prioridad
  }
  cout << endl;

  // Crear una priority_queue con el comportamiento de min-heap
  priority_queue<int, vector<int>, greater<int>> pqMin;

  // Insertar elementos en la min-heap
  pqMin.push(5);
  pqMin.push(2);
  pqMin.push(8);
  pqMin.push(1);
  pqMin.push(3);

  cout << "Elementos en el min-heap (prioridad baja a alta):" << endl;

  // Extraer elementos (se extrae el de menor valor primero)
  // 1 2 3 5 8
  while (!pqMin.empty())
  {
    cout << pqMin.top() << " "; // Muestra el elemento de mayor prioridad (en max-heap, el más grande)
    pqMin.pop();                // Elimina el elemento de mayor prioridad
  }
  cout << endl;

  // Priority Queue con comparador persoanlizado
  priority_queue<pair<int, string>, vector<pair<int, string>>, Comparador> pq;

  pq.push({5, "cinco"});
  pq.push({2, "dos"});
  pq.push({8, "ocho"});
  pq.push({1, "uno"});
  pq.push({3, "tres"});

  while (!pq.empty())
  {
    cout << pq.top().first << " - " << pq.top().second << endl;
    pq.pop();
  }
  // 1 - uno
  // 2 - dos ...
  return 0;
}
