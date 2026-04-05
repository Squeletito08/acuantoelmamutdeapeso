// Se le suma uno MAX_SIDE para trabajar con 1-indexed y
// que la primera fila y columnas estén llenas de 0 y no haya problema
// al acceder a incides anteriores
constexpr int MAX_SIDE = 1000;
int mtxPrefix[MAX_SIDE + 1][MAX_SIDE + 1];
int mtx[MAX_SIDE + 1][MAX_SIDE + 1];
int main()
{
  int N, Q;
  cin >> N >> Q;

  for(int i = 1; i<= N; i++)
    for(int j = 1; j <= N; j++)
      cin >> mtx[i][j]; 
  
  // Construye la prefix matrix
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++)
      mtxPrefix[i][j] = mtx[i][j] + mtxPrefix[i - 1][j] 
                        + mtxPrefix[i][j - 1] - mtxPrefix[i - 1][j - 1];

  // Responder a querys donde te piden la suma de la matriz con esquina
  // superior izquierda (from_row, from_col) y esquina inferior derecha
  // (to_row, to_col), en este caso 1-indexed
  while (Q--)
  {
    int from_row, to_row, from_col, to_col;
    cin >> from_row >> from_col >> to_row >> to_col;
    ll total_sum = mtxPrefix[to_row][to_col] - mtxPrefix[from_row - 1][to_col] -
                   mtxPrefix[to_row][from_col - 1] +
                   mtxPrefix[from_row - 1][from_col - 1];
    cout << total_sum << endl;
  }
}