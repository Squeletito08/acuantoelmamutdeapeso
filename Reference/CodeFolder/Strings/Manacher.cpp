vector<int> manacher_odd(string &s)
{
    int n = s.size();
    s = "$" + s + "^"; // caracteres que no estén en la string
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = min(r - i, p[l + (r - i)]);
        while (s[i - p[i]] == s[i + p[i]])
        {
            p[i]++;
        }
        if (i + p[i] > r)
        {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

/*
s = aaabbacab -> t = #a#a#a#b#b#a#c#a#b#

i % 2 == 0 en t
manacher[i] - 1 corresponde a la longitud del palindromo
par más grande centrado en (i / 2) y (i / 2) - 1
en la string s.

i % 2 != 0 en t
manacher[i] - 1 corresponde a la longitud del palindromo
impar más grande centrado en (i - 1) / 2 en la
string s.
*/
pair<vector<int>, vector<int>> manacher(string &s)
{
    string t = "";
    for (auto c : s)
    {
        t += '#';
        t += c;
    }
    t += '#';

    auto res = manacher_odd(t);

    vector<int> m_even(s.size());
    vector<int> m_odd(s.size());

    for (int i = 0; i < s.size() * 2; i++)
    {
        if (i % 2 == 0)
        {
            m_even[i / 2] = res[i] - 1;
        }
        else
        {
            m_odd[(i - 1) / 2] = res[i] - 1;
        }
    }

    return {m_even, m_odd};
}

// Encontrar el palindromo más grande de una string en O(n)
int main()
{
    string s;
    cin >> s;

    auto [m_even, m_odd] = manacher(s);

    int max_l = 1;
    int centro = 0;

    for (int i = 0; i < m_odd.size(); i++)
    {
        if (m_odd[i] > max_l)
        {
            max_l = m_odd[i];
            centro = i;
        }
    }

    for (int i = 0; i < m_even.size(); i++)
    {
        if (m_even[i] > max_l)
        {
            max_l = m_even[i];
            centro = i;
        }
    }

    int inicio = centro - (max_l / 2);
    int fin = inicio + max_l - 1;

    for (int k = inicio; k <= fin; k++)
    {
        cout << s[k];
    }

    cout << endl;

    return 0;
}