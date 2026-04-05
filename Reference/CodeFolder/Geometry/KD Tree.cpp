#include <bits/stdc++.h>
using namespace std;

using Coord = double; // tipo de coordenadas
constexpr Coord EPS = 1e-9;
const int MAX_D = 5; // numero de dimensiones máximo

struct KDTree {
    struct Point {
        Coord x[MAX_D];
        int id;
    };
    struct Node {
        Point p;
        int dim;
        Node *l, *r;
    };
    int D;
    Node* root;

    KDTree(int _D) : D(_D), root(nullptr) {}

    Node* build(vector<Point>& pts, int l, int r, int depth) {
        if (l >= r) return nullptr;
        int dim = depth % D;
        int m = (l + r) / 2;
        nth_element(pts.begin()+l, pts.begin()+m, pts.begin()+r,
            [dim](const Point& a, const Point& b){ return a.x[dim] < b.x[dim]; });
        Node* node = new Node{pts[m], dim, nullptr, nullptr};
        node->l = build(pts, l, m, depth+1);
        node->r = build(pts, m+1, r, depth+1);
        return node;
    }

    void build(vector<Point>& pts) { root = build(pts, 0, pts.size(), 0); }

    // ---- Distance function ----
    Coord dist(const Point& a, const Point& b) {
    #ifdef MANHATTAN
        Coord d = 0;
        for (int i=0;i<D;i++) d += abs(a.x[i]-b.x[i]);
        return d;
    #else
        Coord d = 0;
        for (int i=0;i<D;i++){ Coord diff=a.x[i]-b.x[i]; d += diff*diff; }
        return d;
    #endif
    }

    // ---- Nearest neighbor ----
    void nearest(Node* node, const Point& target, Point& best, Coord& bestd) {
        if (!node) return;
        Coord d = dist(node->p, target);
    #ifdef MANHATTAN
        if (d + EPS < bestd) { bestd = d; best = node->p; }
    #else
        if (d < bestd - EPS) { bestd = d; best = node->p; }
    #endif
        int dim = node->dim;
        Node *first = target.x[dim] < node->p.x[dim] ? node->l : node->r;
        Node *second = first == node->l ? node->r : node->l;
        nearest(first, target, best, bestd);
        Coord diff = abs(target.x[dim] - node->p.x[dim]);
    #ifdef MANHATTAN
        if (diff < bestd - EPS) nearest(second, target, best, bestd);
    #else
        if (diff*diff < bestd - EPS) nearest(second, target, best, bestd);
    #endif
    }

    Point nearest(const Point& target) {
        Point best; Coord bestd = numeric_limits<Coord>::max();
        nearest(root, target, best, bestd);
        return best;
    }

    void range_query(Node* node, const Coord low[], const Coord high[], vector<Point>& out) {
        if (!node) return;
        const auto& P = node->p;
        bool inside = true;
        for (int i=0; i<D; i++) {
            if (P.x[i] < low[i] - EPS || P.x[i] > high[i] + EPS)
            { inside = false; break; }
        }
        if (inside) out.push_back(P);

        int dim = node->dim;
        if (low[dim] - EPS <= P.x[dim]) range_query(node->l, low, high, out);
        if (high[dim] + EPS >= P.x[dim]) range_query(node->r, low, high, out);
    }

    vector<Point> range_query(const vector<Coord>& low, const vector<Coord>& high) {
        vector<Point> res;
        Coord lo[MAX_D], hi[MAX_D];
        for (int i=0;i<D;i++){ lo[i] = low[i]; hi[i] = high[i]; }
        range_query(root, lo, hi, res);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, D; cin >> n >> D; // n - #pts, D - #dims
    vector<KDTree::Point> pts(n);
    for (int i=0;i<n;i++) {
        for (int j=0;j<D;j++) cin >> pts[i].x[j];
        pts[i].id = i;
    }
    KDTree tree(D);
    tree.build(pts);

    // Example nearest neighbor query
    KDTree::Point q;
    for (int j=0;j<D;j++) cin >> q.x[j];
    auto nearest_pt = tree.nearest(q);
    cout << "Nearest id: " << nearest_pt.id << "\n";

    // Example range query
    vector<Coord> low(D), high(D);
    for (int j=0;j<D;j++) cin >> low[j];
    for (int j=0;j<D;j++) cin >> high[j];
    auto ans = tree.range_query(low, high);
    for (auto &p : ans) {
        cout << p.id;
        for (int j=0;j<D;j++) cout << " " << p.x[j];
        cout << "\n";
    }
}
