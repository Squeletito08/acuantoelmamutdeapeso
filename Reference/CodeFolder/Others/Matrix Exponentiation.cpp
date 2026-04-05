
// Uso: Matrix<T> M = matPow<T>(A, n - 1);
template <typename T>
Matrix<T> matPow(Matrix<T> &base, ll p)
{
  Matrix<T> ans(base.rows(), base.cols());
  ans.makeiden();
  while (p)
  {
    if (p & 1)
      ans *= base;

    base *= base;
    p >>= 1;
  }
  return ans;
}