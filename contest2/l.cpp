#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <queue>
#include <iomanip>

struct edge {
    int from;
    int to;
    long long weight;
    bool operator<(edge& other) {
        return weight < other.weight;
    }
};

class DSU{
public:
    DSU(int n) {
        dsu.resize(n+1);
        rnk.resize(n+1);
        for(int i = 1; i <= n; i++) {
            dsu[i] = i;
            rnk[i] = 1;
        }
    }

    int get(int v) {
        if(v == dsu[v]) {
            return v;
        }

        return dsu[v] = get(dsu[v]);
    }

    void merge(int a, int b) {
        a = get(a);
        b = get(b);
        if(a == b) {
            return;
        }

        if(rnk[b] < rnk[a]) {
            std::swap(a, b);
        }

        dsu[b] = a;
        rnk[a] += rnk[b];
    }

private:
    std::vector<int> dsu;
    std::vector<int> rnk;
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<edge> edges(m);
    for(int i = 0; i < m; i++) {
        std::cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }

    std::sort(edges.begin(), edges.end());
    long long ans = 0;

    std::vector<int> edgeIndex(n+1, -1);
    DSU dsu(n);
    for(auto e : edges) {
        int from = e.from;
        int to = e.to;
        if(dsu.get(from) != dsu.get(to)) {
            ans += e.weight;
            dsu.merge(from, to);
        }
    }

    std::cout << ans << "\n";

    return 0;
}