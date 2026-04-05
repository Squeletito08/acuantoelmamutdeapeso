// Ver si n es divisible por 2^k
bool isDivisibleByPowerOf2(int n, int k) {
  int powerOf2 = 1 << k;
  return (n & (powerOf2 - 1)) == 0;
}

bool isPowerOfTwo(unsigned int n) {
  return n && !(n & (n - 1));
}

int countSetBits(int n)
{
  int count = 0;
  while (n)
  {
      n = n & (n - 1);
      count++;
  }
  return count;
}

// Cuenta el número de bits encendidos hasta el número n 
int countSetBits(int n) {
  int count = 0;
  while (n > 0) {
      int x = std::bit_width(n) - 1;
      count += x << (x - 1);
      n -= 1 << x;
      count += n + 1;
  }
  return count;
}

// Encender el i-ésimo bit
n |= (1 << i);

// Apagar el i-ésimo bit
n &= ~(1 << i);

// Alternar el i-ésimo bit
n ^= (1 << i);

// Apagar el bits más a la derecha 
n = n & (n-1); 

// Limpia todos los "trailing ones"
// 0011 0111 -> 0011 0000
n = n & (n+1)

// Enciende el último bit apagado 
// 0011 0101 -> 0011 0111
n = n | (n+1) 

// Extrae el último bit prendido
// 0011 0100 -> 0000 0100 
n = n & ~n 

// Número de bits encendidos
__builtin_popcount(x); 
__builtin_popcountll(x); 

// Posición del primer 1 desde la derecha (1-indexado)
__builtin_ffs(x);     
__builtin_ffsll(x); 

// 1 si número impar de bits encendidos
__builtin_parity(x); 
__builtin_parityll(x); 

// Nota:  clzll y ctzll no son seguras si x == 0

// Ceros a la izquierda después del primer bit encendido desde la derecha
//__builtin_clz(00000000 00000000 00000000 00010000) = 27
__builtin_clz(x); 
__builtin_clzll(x); 

// Ceros a la derecha despu+es del primer bit encendido desde la derecha 
// __builtin_ctz(00000000 00000000 00000000 00010000) = 4 
__builtin_ctz(x); 
__builtin_ctzll(x); 
