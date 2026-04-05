// O(n^3) por cada sistema Ax=b
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Solves Ax = b using Gaussian elimination (with partial pivoting)
vector<double> gaussian_elimination(vector<vector<double>> A, vector<double> b, int n) {
    // Forward elimination
    for (int i = 0; i < n; i++) {
        // Partial pivoting (find max element in column i)
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
                maxRow = k;
        }

        // Swap rows in A and b
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        // Eliminate entries below pivot
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // Back substitution
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
    return x;
}

int main() {
    int n = 3;
    vector<vector<double>> A = {
        {2, -1, -2},
        {-4, 6, 3},
        {-4, -2, 8}
    };
    vector<double> b = {-2, 9, -5};

    vector<double> x = gaussian_elimination(A, b, n);

    cout << "Solution x:" << endl;
    for (double xi : x)
        cout << xi << " ";
    cout << endl;

    return 0;
}
