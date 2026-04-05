// Obtiene en O(n) el área de un polígono simple con vértices en orden
// horario o anti-horario.
double shoelaceArea(const vector<pair<int, int>>& P) {
    int n = P.size();
    long long area = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += 1LL * P[i].first * P[j].second;
        area -= 1LL * P[j].first * P[i].second;
    }
    return abs(area) / 2.0;
}
