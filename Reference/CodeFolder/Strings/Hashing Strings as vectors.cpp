vector<ll> P = {325255434, 10018302};
vector<ll> M = {999727999, 1070777777};

/*
  Para tratar todas las permutaciones de una misma cadena como equivalentes,
  se puede representar la cadena mediante su vector de frecuencias.
  Por ejemplo, la cadena "abacb" se representa como:
    f = {2, 2, 1, 0, 0, ...}
         a  b  c  d  e ...
  donde f[i] indica cuántas veces aparece el carácter en la posición i del alfabeto en la string dada.

  Para comparar estas representaciones de forma eficiente, se puede calcular
  un hash del vector de frecuencias. Sea:
    - f el vector de frecuencias de una cadena,
    - |A| el tamaño del alfabeto (por ejemplo, 26 para letras minúsculas),
    - b y M constantes enteras elegidas para el cálculo del hash,

  entonces definimos el hash como:
    hash(f) = (f[0] * b^0 + f[1] * b^1 + ... + f[|A|-1] * b^|A|-1) mod M

  Nota: Si ya se ha calculado el hash del vector correspondiente a la subcadena s[L...R] entonces calcular el hash del vector de la subcadena definida por 
  s[L...R+1] implica:
    hash(S[L...R+1]) = ( hash(S[L...R]) + b^(pos(S[R+1])) ) mod M 
  donde pos(S[R+1]) es la posición del caracter S[R+1] en el alfabeto. 
*/
void Hashing_Strigns_as_Vectors()
{
  string s; 
  int sigma = 27; // Tamaño del alfabeto
  int n = s.size();

  vector<vector<ll>> pot(2, vector<ll>(sigma, 0));
  pot[0][0] = pot[1][0] = 1;

  for (int i = 1; i < sigma; i++)
  {
    pot[0][i] = pot[0][i - 1] * P[0] % M[0];
    pot[1][i] = pot[1][i - 1] * P[1] % M[1];
  }

  // Calcula el hash de todos los vectores de frecuencias de 
  // todas las substrings de s
  for (int i = 0; i < n; i++)
  {
    ll hash1 = 0;
    ll hash2 = 0;
    for (int j = i; j < n; j++)
    {
      int pos_c = s[j] - 'a';
      hash1 += pot[0][pos_c] % M[0];
      hash2 += pot[1][pos_c] % M[1];

      ll final_hash = (hash1 << 32) | hash2;
    }
  }
}

