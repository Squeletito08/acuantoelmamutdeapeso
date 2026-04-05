
template <typename T>
void matmul(vector<vector<T>> &a, vector<vector<T>> b)
{
    int n = a.size(), m = a[0].size(), p = b[0].size();
    assert(m == b.size());
    vector<vector<T>> c(n, vector<T>(p));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            for (int k = 0; k < m; k++)
                // Mult with mod define
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;

    a = c;
}

template <typename T>
struct Matrix
{
    vector<vector<T>> mat;
    Matrix() {}
    Matrix(vector<vector<T>> a) { mat = a; }
    Matrix(int n, int m)
    {
        mat.resize(n);
        for (int i = 0; i < n; i++)
            mat[i].resize(m);
    }
    int rows() const { return mat.size(); }
    int cols() const { return mat[0].size(); }

    vector<T> &operator[](int i) { return mat[i]; }
    const vector<T> &operator[](int i) const { return mat[i]; }

    void makeiden()
    {
        for (int i = 0; i < rows(); i++)
            mat[i][i] = 1;
    }
    Matrix operator*=(const Matrix &b)
    {
        matmul(mat, b.mat);
        return *this;
    }
    Matrix operator*(const Matrix &b) { return Matrix(*this) *= b; }
    void print() const
    {
        for (int i = 0; i < rows(); i++)
        {
            for (int j = 0; j < cols(); j++)
            {
                cout << mat[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};
