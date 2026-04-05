// Resuelve en O(n) una matriz tridiagonal, y es estable si la matriz es
// diagonal-dominante (i.e. en cada renglón la entrada de la diagonal es
// mayor a la suma del resto de entradas del renglón).

#include <iostream>
#include <vector>
using namespace std;

// Solves Ax = d where A is a tridiagonal matrix with vectors a (sub), b (main), c (super)
vector<double> thomas_algorithm(const vector<double>& a, const vector<double>& b,
                                const vector<double>& c, const vector<double>& d) {
    int n = b.size();
    vector<double> c_prime(n, 0.0), d_prime(n, 0.0), x(n, 0.0);

    // Forward sweep
    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];
    for (int i = 1; i < n; ++i) {
        double m = b[i] - a[i] * c_prime[i - 1];
        c_prime[i] = i < n - 1 ? c[i] / m : 0.0;
        d_prime[i] = (d[i] - a[i] * d_prime[i - 1]) / m;
    }

    // Back substitution
    x[n - 1] = d_prime[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        x[i] = d_prime[i] - c_prime[i] * x[i + 1];
    }

    return x;
}

// Example usage
int main() {
    // Tridiagonal system Ax = d
    // a: sub-diagonal (a[0] unused), b: main diagonal, c: super-diagonal
    vector<double> a = {0, 1, 1};     // a[0] is unused
    vector<double> b = {4, 4, 4};
    vector<double> c = {1, 1, 0};     // c[n-1] is unused
    vector<double> d = {5, 5, 5};

    vector<double> solution = thomas_algorithm(a, b, c, d);

    cout << "Solution:\n";
    for (double val : solution)
        cout << val << " ";
    cout << endl;

    return 0;
}
