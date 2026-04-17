/*
    Cuenta ocurrencias de t en s usando el Suffix Array.
    Complejidad: O(|t| * log |s|)
*/

// Lower bound: primera posición en SA tal que s[SA[m]...] >= t
int lwb(const SuffixArray &sa_obj, const string &s, const string &t) {
  int l = 0, r = sa_obj.n - 1;
  int res = sa_obj.n;
  int sz = t.size();

  while (l <= r) {
    int m = l + (r - l) / 2;
    if (s.compare(sa_obj.sa[m], sz, t) >= 0) {
      res = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return res;
}

// Upper bound: primera posición en SA tal que s[SA[m]...] > t
// (Limitamos la comparación al tamaño de t)
int upb(const SuffixArray &sa_obj, const string &s, const string &t) {
  int l = 0, r = sa_obj.n - 1;
  int res = sa_obj.n;
  int sz = t.size();

  while (l <= r) {
    int m = l + (r - l) / 2;
    if (s.compare(sa_obj.sa[m], sz, t) > 0) {
      res = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return res;
}

// SuffixArray sa_obj(s);
// int count = upb(sa_obj, s, t) - lwb(sa_obj, s, t);
