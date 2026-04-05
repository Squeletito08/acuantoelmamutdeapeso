// Resuelve numéricamente una ecuación diferencial con PVI de manera estable
#include <iostream>
#include <cmath>
using namespace std;

// Define the differential equation dy/dx = f(x, y)
double f(double x, double y) {
    return x + y; // Example: dy/dx = x + y
}

// RK4 method to solve from x0 to xn with step size h
double rk4(double x0, double y0, double xn, double h) {
    int n = (int)((xn - x0) / h);
    double x = x0, y = y0;

    for (int i = 0; i < n; ++i) {
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
        double k3 = h * f(x + h / 2.0, y + k2 / 2.0);
        double k4 = h * f(x + h, y + k3);

        y += (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        x += h;
    }

    return y;
}

int main() {
    double x0 = 0, y0 = 1;   // Initial condition y(0) = 1
    double xn = 2, h = 0.1;  // Solve up to x = 2 with step size 0.1

    double result = rk4(x0, y0, xn, h);
    cout << "Approximate solution at x = " << xn << " is y = " << result << endl;

    return 0;
}

