/**
 * LIS / NON-DECREASING / DILWORTH
 * -----------------------------------------
 * 1. Longest Increasing (LIS): lower_bound
 * 2. Longest Non-Decreasing: upper_bound
 * * Para versiones DECREASING: Multiplicar todo por -1 y calcular la respectiva
 * INCREASING. Para COBERTURA MÍNIMA (Dilworth):
 * - Min Non-Decreasing covers = Longest Strictly Decreasing
 * - Min Strictly Increasing covers = Longest Non-Increasing
 */

// Función base: Calcula Longest Increasing Subsequence
// strictly = true  -> a < b < c (LIS)
// strictly = false -> a <= b <= c (Non-Decreasing)
int solve_lis(vector<int> nums, bool strictly) {
  if (nums.empty())
    return 0;
  vector<int> tails;
  for (int x : nums) {
    auto it = strictly ? lower_bound(tails.begin(), tails.end(), x)
                       : upper_bound(tails.begin(), tails.end(), x);
    if (it == tails.end())
      tails.push_back(x);
    else
      *it = x;
  }
  return tails.size();
}

// 1. Longest Strictly Increasing (LIS):
//    solve_lis(nums, true);

// 2. Longest Non-Decreasing:
//    solve_lis(nums, false);

// 3. Longest Strictly Decreasing (LDS):
//    Transformar: x -> -x. Luego: solve_lis(nums, true);

// 4. Longest Non-Increasing:
//    Transformar: x -> -x. Luego: solve_lis(nums, false);

/* --- COBERTURA MÍNIMA (TEOREMA DE DILWORTH) --- */

// 5. Mínimo número de cadenas NON-DECREASING para cubrir el arreglo:
//    = Longest Strictly Decreasing (Caso 3)

// 6. Mínimo número de cadenas STRICTLY INCREASING para cubrir el arreglo:
//    = Longest Non-Increasing (Caso 4)

// 7. Mínimo número de cadenas NON-INCREASING para cubrir el arreglo:
//    = Longest Strictly Increasing (Caso 1)

// 8. Mínimo número de cadenas STRICTLY DECREASING para cubrir el arreglo:
//    = Longest Non-Decreasing (Caso 2)
