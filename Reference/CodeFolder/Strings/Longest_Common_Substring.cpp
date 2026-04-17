string LCS() {
  string a, b;
  cin >> a >> b;
  int n1 = a.size();

  // a = "banana", b = "anana" -> "banana$anana#"
  string s = a + "$" + b + "#";
  SuffixArray sa_obj(s);

  int max_len = 0;
  int start_pos = 0;
  int total_n = s.size();

  // Recorremos el Suffix Array buscando sufijos adyacentes
  // que pertenezcan a strings distintas
  for (int i = 1; i < total_n; i++) {
    int pos1 = sa_obj.sa[i];
    int pos2 = sa_obj.sa[i - 1];

    // Verificamos si uno pertenece a 'a' y el otro a 'b'
    // 'a' está en el rango [0, n1-1]
    // '$' está en n1
    // 'b' está en el rango [n1+1, total_n-2]
    bool belongs_a_1 = (pos1 < n1);
    bool belongs_a_2 = (pos2 < n1);

    bool belongs_b_1 = (pos1 > n1 && pos1 < total_n - 1);
    bool belongs_b_2 = (pos2 > n1 && pos2 < total_n - 1);

    if ((belongs_a_1 && belongs_b_2) || (belongs_a_2 && belongs_b_1)) {
      // El LCP entre SA[i] y SA[i-1] es sa_obj.lcp[i]
      if (sa_obj.lcp[i] > max_len) {
        max_len = sa_obj.lcp[i];
        start_pos = pos1;
      }
    }
  }

  return s.substr(start_pos, max_len);
}
