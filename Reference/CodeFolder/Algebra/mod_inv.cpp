#include <iostream>
using namespace std;

int euclides_extendido(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = euclides_extendido(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

// Devuelve el inverso modular de a módulo m, o -1 si no existe
int inverso_modular(int a, int m) {
    int x, y;
    int g = euclides_extendido(a, m, x, y);
    if (g != 1) return -1; // No existe inverso si a y m no son coprimos
    x = (x % m + m) % m;   // Asegura que x sea positivo
    return x;
}

