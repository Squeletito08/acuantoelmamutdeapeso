#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
const double PI = 3.14159265358979323846;

double f(double x) {
    return -(x - 2) * (x - 2) + PI; 
}

double busqueda_ternaria_max(double l, double r, double epsilon = 1e-7) {
    while (r - l > epsilon) {
        double tercio1 = l + (r - l) / 3;
        double tercio2 = r - (r - l) / 3;
        if (f(tercio1) < f(tercio2))
            l = tercio1;  // El máximo está en [tercio1, r]
        else
            r = tercio2;  // El máximo está en [l, tercio2]
    }
    return (l + r) / 2; // Aproximación del máximo
}

int main() {
    double l = 0, r = 4;
    double max_x = busqueda_ternaria_max(l, r);
    cout << fixed << setprecision(7);
    cout << "Máximo en x ≈ " << max_x << ", f(x) ≈ " << f(max_x) << endl;
    return 0;
}
