// Tamaño del bitset (usa hasta 32 si quieres convertir a int sin problemas)
const int N = 8;
int main() {
    // 🔹 Crear bitsets
    bitset<N> bs1(string("10101001"));   // Desde string binario
    int num = 42;
    bitset<N> bs2(num);                  // Desde entero (42 = 00101010)

    cout << "bs1: " << bs1 << endl;
    cout << "bs2: " << bs2 << endl;

    // 🔹 Iterar sobre bits
    cout << "Bits activos (1) en bs1: ";
    for (int i = 0; i < N; ++i) {
        if (bs1[i]) cout << i << " ";
    }
    cout << "\n";

    // 🔹 Operaciones lógicas entre bitsets
    cout << "bs1 & bs2: " << (bs1 & bs2) << endl;
    cout << "bs1 | bs2: " << (bs1 | bs2) << endl;
    cout << "bs1 ^ bs2: " << (bs1 ^ bs2) << endl;

    // 🔹 Métodos importantes
    cout << "bs1.any():  " << bs1.any() << "  // ¿Algún bit en 1?\n";
    cout << "bs1.none(): " << bs1.none() << " // ¿Todos los bits en 0?\n";
    cout << "bs1.all():  " << bs1.all() << "  // ¿Todos los bits en 1?\n";
    cout << "bs1.count(): " << bs1.count() << " // ¿Cuántos bits en 1?\n";

    // 🔹 Modificación de bits
    bs1.set(2);     // Pone a 1 el bit 2
    bs1.reset(0);   // Pone a 0 el bit 0
    bs1.flip(1);    // Invierte el bit 1

    cout << "bs1 modificado: " << bs1 << endl;

    bs1.set();      // Todos los bits a 1
    cout << "bs1.set(): " << bs1 << endl;

    bs1.reset();    // Todos los bits a 0
    cout << "bs1.reset(): " << bs1 << endl;

    bs1.flip();     // Invierte todos los bits
    cout << "bs1.flip(): " << bs1 << endl;

    // 🔹 Conversión a entero
    unsigned long val_ul = bs2.to_ulong();         // Hasta 32 bits
    unsigned long long val_ull = bs2.to_ullong();  // Hasta 64 bits
    int val_int = static_cast<int>(val_ul);        // Seguro si N <= 32

    cout << "bs2 como unsigned long: " << val_ul << endl;
    cout << "bs2 como int: " << val_int << endl;

    // 🔹 Convertir int a bitset nuevamente
    bitset<N> fromInt(val_int);
    cout << "Convertido desde int: " << fromInt << endl;

    return 0;
}
