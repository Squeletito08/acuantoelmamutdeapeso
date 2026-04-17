/*
Encuentra la subcadena repetida más larga.
Si hay empate, devuelve la primera que aparece en orden lexicográfico.
*/
string Repeating_Substring() {
  string s;
  cin >> s;

  SuffixArray sa_obj(s);

  int max_len = 0;
  int pos_in_sa = -1;

  // El arreglo LCP tiene n elementos. lcp[i] es el prefijo común
  // entre sa[i] y sa[i-1].
  for (int i = 1; i < sa_obj.n; i++) {
    if (sa_obj.lcp[i] > max_len) {
      max_len = sa_obj.lcp[i];
      pos_in_sa = i;
    }
  }

  if (max_len == 0)
    return "";

  // Usamos sa[pos_in_sa] para obtener el índice original en el string
  return s.substr(sa_obj.sa[pos_in_sa], max_len);
}
