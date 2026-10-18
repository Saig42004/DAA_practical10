#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Edge structure
struct Edge {
    int u, v, w; // from, to, weight
};

// ---------- Disjoint Set Union (Union-Find) ----------
class DSU {
    vector<int> parent, rank_;
public:
    DSU(int n) {
        parent.resize(n);
        rank_.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by rank
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false; // already connected -> cycle!

        if (rank_[rx] < rank_[ry])
            parent[rx] = ry;
        else if (rank_[rx] > rank_[ry])
            parent[ry] = rx;
        else {
            parent[ry] = rx;
            rank_[rx]++;
        }
        return true;
    }
};

// ---------- Kruskal's Algorithm ----------
vector<Edge> kruskalMST(int V, vector<Edge>& edges) {
    // 1. Sort edges by weight
    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) { return a.w < b.w; });

    DSU dsu(V);
    vector<Edge> mst;

    // 2. Pick edges, skip cycles
    for (auto& e : edges) {
        if (mst.size() == V - 1) break; // MST complete

        if (dsu.unite(e.u, e.v)) {  // no cycle formed
            mst.push_back(e);
        }
    }

    return mst;
}

int main() {
    int V = 5;
    vector<Edge> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    vector<Edge> mst = kruskalMST(V, edges);

    cout << "Edge \tWeight\n";
    int totalWeight = 0;
    for (auto& e : mst) {
        cout << e.u << " - " << e.v << "\t" << e.w << "\n";
        totalWeight += e.w;
    }
    cout << "Total MST weight: " << totalWeight << "\n";

    return 0;
}
