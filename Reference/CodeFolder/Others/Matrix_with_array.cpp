#include <iostream>
#include <algorithm>
using namespace std;

const long long MOD = 1000000007;
// Multiplicación de matrices 2x2: C = A * B
void mult2x2(const long long A[2][2], const long long B[2][2], long long C[2][2]) {
    long long temp00 = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % MOD;
    long long temp01 = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % MOD;
    long long temp10 = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % MOD;
    long long temp11 = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % MOD;
    C[0][0] = temp00;
    C[0][1] = temp01;
    C[1][0] = temp10;
    C[1][1] = temp11;
}
// Exponenciación binaria de la matriz 2x2 M a la potencia exp. El resultado se almacena en 'result'.
void matPow2x2(const long long M[2][2], long long exp, long long result[2][2]) {
    // Inicializamos 'result' como la identidad.
    result[0][0] = 1; result[0][1] = 0;
    result[1][0] = 0; result[1][1] = 1;
    
    long long base[2][2] = { {M[0][0], M[0][1]}, {M[1][0], M[1][1]} };
    
    while(exp > 0) {
        if(exp & 1) {
            long long temp[2][2];
            mult2x2(result, base, temp);
            result[0][0] = temp[0][0]; result[0][1] = temp[0][1];
            result[1][0] = temp[1][0]; result[1][1] = temp[1][1];
        }
        long long temp[2][2];
        mult2x2(base, base, temp);
        base[0][0] = temp[0][0]; base[0][1] = temp[0][1];
        base[1][0] = temp[1][0]; base[1][1] = temp[1][1];
        exp >>= 1;
    }
}

// s_0 y s_1 son los casos base y n es el número de pasos a avanzar a partir de s1.
long long fib(long long n, long long s_0, long long s_1) {
    // Si n es 0, la matriz identidad deja la columna [s_1, s_0] y se devuelve s_1.
    if(n == 0) return s_1 % MOD;
    long long M[2][2] = { {1, 1}, {1, 0} };
    long long power[2][2];
    matPow2x2(M, n, power);
    // Multiplicamos la matriz resultante por la columna [s_1, s_0]:
    long long res = (power[0][0] * s_1 + power[0][1] * s_0) % MOD;
    return res;
}



