// Cuenta el número de subcadenas que están en 1-Dyck en O(n)
// (subcadenas que están en el leng. de paréntesis balanceados)

ll aux_subdyck(const vector<int>& to_open, int start, int end) // auxiliar
{
    ll streak = 0, acc = 0; // acc es la cuenta, streak es la racha de 
                             // paréntesis adyacentes en el mismo nivel
    for (int i = end-1; i >= start; --i)
    {
        int op = to_open[i];
        if (op < 0) { acc += (streak*(streak+1))>>1; streak = 0; }
        else { streak++; acc += aux_subdyck(to_open, op+1, i); i = op; }
    }
    acc += (streak*(streak+1))>>1;
    return acc;
}

ll cnt_subdyck(const string& s, char opensymb, char closesymb) // O(n) dp
{
    int n = s.length();
    vector<int> opens; opens.reserve(n); // pila de idx de parens abiertos
    vector<int> to_open(n,-1); // dónde se encuentra la pareja '(' de cada ')'
    for (int i = 0; i < n; i++)
    {
        if (s[i] == opensymb)
            opens.push_back(i);
        else if (s[i] == closesymb and opens.size())
        {
            to_open[i] = opens[opens.size()-1];
            opens.pop_back();
        }
    }
    return aux_subdyck(to_open, 0, n); // cuenta por niveles de parens
}
