#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
typedef long long ll;
ll sn, sn_1;

vector<vector<ll>> multiply(const vector<vector<ll>>& A, const vector<vector<ll>>& B) {
    int N = A.size();
    vector<vector<ll>> C(N, vector<ll>(N, 0)); 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                ll r = A[i][k] * B[k][j] % MOD;
                C[i][j] = (C[i][j] + r) % MOD;
            }
        }
    }
    return C;
}

vector<vector<ll>> matrixExpo(vector<vector<ll>> T, ll p) {
    int N = T.size();
    vector<vector<ll>> res(N, vector<ll>(N, 0)); 
    for (int i = 0; i < N; i++) res[i][i] = 1; 
    while (p > 0) {
        if (p & 1)
            res = multiply(res, T);
        T = multiply(T, T); 
        p >>= 1;
    }
    return res;
}

void calculateFib(int sk){
    vector<vector<ll>> F = {{1, 1}, 
                            {1, 0}};
    vector<vector<ll>> base = {{sn}, 
                                {sn_1}};
    vector<vector<ll>> res = multiply(matrixExpo(F, sk), base);
    sn= res[0][0];
    sn_1 = res[1][0];
}

