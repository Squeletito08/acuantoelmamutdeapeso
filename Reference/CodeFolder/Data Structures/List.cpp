#include <iostream>
#include <list>
#include <iterator> // Necesario para next() y prev()
using namespace std;

int main() {
    list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);
    lst.push_back(50);

    cout << "Elementos en la lista (usando iteradores):" << endl;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    auto it = lst.begin();
    cout << "El primer elemento es: " << *it << endl;
    it = next(it, 2); // Avanzar el iterador 2 posiciones
    cout << "El tercer elemento (después de avanzar 2 pasos) es: " << *it << endl;

    // Uso de `prev()` para retroceder el iterador
    it = prev(it, 1); // Retroceder 1 posición
    cout << "El segundo elemento (después de retroceder 1 paso) es: " << *it << endl;

    // Inserción de un elemento antes de un iterador específico
    it = next(lst.begin(), 2); // Moverse al tercer elemento
    lst.insert(it, 35); // Insertar 35 antes del tercer elemento

    // Mostrar los elementos después de la inserción
    cout << "\nElementos después de insertar 35 antes del tercer elemento:" << endl;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Eliminar un elemento usando un iterador
    it = next(lst.begin(), 3); // Moverse al cuarto elemento
    lst.erase(it); // Eliminar el cuarto elemento (40)

    // Acceder al primer y último elemento usando `front()` y `back()`
    cout << "\nEl primer elemento es: " << lst.front() << endl;
    cout << "El último elemento es: " << lst.back() << endl;
    return 0;
}
