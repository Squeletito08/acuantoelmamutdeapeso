using C = double;
using CX = complex<C>;
const C PI = acos(-1);

// FFT + inverse FFT
void fft(vector<CX> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        C ang = 2 * PI / len * (invert ? -1 : 1);
        CX wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            CX w(1);
            for (int j = 0; j < len / 2; j++) {
                CX u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (CX & x : a)
            x /= n;
    }
}

// multiplicación de polinomios en O(nlogn) [recibe coefs enteros]
vector<ll> polyn_multiply(vector<int> const& a, vector<int> const& b) {
    vector<CX> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

// de cuántas maneras se puede escojer (i,j) tal que a[i]+b[j]=k?
ll count_sum(vector<int> const& a, vector<int> const& b, int k)
{
    vector<int> pa = ..., pb = ...;
                       // aquí guardamos entradas de 0 (o min spg) hasta el
                       // valor max de a y b, donde en cada casilla arr[i]
                       // llenamos el número de ocurrencias de i.
    // si tenemos a=[1,2,3], b=[2,4], construimos
    //      pa = 0x^0 + 1x^1 + 1x^2 + 1x^3 + 0x^4
    //      pb = 0x^0 + 0x^1 + 1x^2 + 0x^3 + 1x^4
    // donde el coef. de x^i es el número de apariencias de i
    auto r = polyn_multiply(pa, pb);
    // el resultado es el coeficiente de x^k
    return r[k];
}

// dado vectores a y b de dimension n, encuentra el producto punto de a con
// cada shift circular de b.
vector<int> all_dot_shifts(vector<int> const& a, vector<int> const& b, int n)
{
    vector<int> fa(2*n), fb(2*n);
    fa = reverse(a) + [0]*n; // pseudocódigo pythonesco
    fb = b + b; // pseudocódigo pythonesco
    r = polyn_multiply(fa,fb);

    // así, r[k] nos da el producto punto de a con el shift (k-(n-1)) de b
}

// string matching con wildcards
vector<bool> str_match(const string& txt, const string& pat, char wildcard='*')
{
    int n = txt.size(), m = pat.size();
    int wilds = 0;
    for (char c : pat) if (c == wildcard) wilds++;
    vector<CX> a(n), b(m,0);
    for (int i = 0; i < n; i++)
    {
        C t = (2*PI*(txt[i]-'a'))/26;
        a[i] = {cos(t), sin(t)};
    }
    for (int i = 0; i < m; i++)
    {
        int j = m-i-1;
        if (pat[j] == wildcard) continue;
        C t = (2*PI*(pat[j]-'a'))/26;
        b[i] = {cos(t), sin(t)};
    }
    ab = polyn_multiply(a, b);
    vector<bool> r(n);
    for (int i = 0; i < n; i++) r[i] = ab[i] == (m - wilds);
    return r; // si r[i]=true entonces hay un match en la pos i
}
