int main() {
    deque<int> dq;

    // Insertar elementos al final de la deque (push_back)
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    dq.push_back(40);

    // Insertar elementos al frente de la deque (push_front)
    dq.push_front(5);
    dq.push_front(2);

    // Mostrar los elementos de la deque
    cout << "Elementos en la deque:" << endl;
    for (int el : dq) {
        cout << el << " ";
    }
    cout << endl;

    // Eliminar el elemento al frente (pop_front)
    dq.pop_front();

    // Eliminar el elemento al final (pop_back)
    dq.pop_back();

    cout << "Elementos después de eliminar el frente y el final:" << endl;
    for (int el : dq) {
        cout << el << " ";
    }
    cout << endl;

    // Verificar si la deque está vacía
    if (dq.empty()) {
        cout << "La deque está vacía." << endl;
    } else {
        cout << "La deque no está vacía." << endl;
    }

    // Mostrar el primer y último elemento
    cout << "El primer elemento es: " << dq.front() << endl;
    cout << "El último elemento es: " << dq.back() << endl;
    return 0;
}
