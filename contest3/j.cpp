#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class BipartiteGraph {
private:
    long long left, right;
    vector<vector<long long>> graph;
    vector<long long> matchR;

    bool bpm(long long u, vector<bool>& seen) {
        for (long long v = 0; v < right; ++v) {
            if (graph[u][v] && !seen[v]) {
                seen[v] = true;
                if (matchR[v] == -1 || bpm(matchR[v], seen)) {
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

public:
    BipartiteGraph(long long n, long long m, const vector<vector<long long>>& edges) {
        left = n;
        right = m;
        graph = vector<vector<long long>>(left, vector<long long>(right, 0));
        matchR = vector<long long>(right, -1);

        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; edges[i][j] != 0; ++j) {
                graph[i][edges[i][j] - 1] = 1;
            }
        }
    }

    long long max_bipartite_matching() {
        long long maxMatching = 0;
        for (long long i = 0; i < left; ++i) {
            vector<bool> seen(right, false);
            if (bpm(i, seen)) {
                ++maxMatching;
            }
        }
        return maxMatching;
    }

    vector<pair<long long, long long>> get_matching_edges() {
        vector<pair<long long, long long>> matchingEdges;
        for (long long v = 0; v < right; ++v) {
            if (matchR[v] != -1) {
                matchingEdges.push_back({matchR[v] + 1, v + 1});
            }
        }
        return matchingEdges;
    }
};

int main() {
    long long n, m;
    cin >> n >> m;

    vector<vector<long long>> edges(n);
    for (long long i = 0; i < n; ++i) {
        long long vertex;
        while (cin >> vertex && vertex != 0) {
            edges[i].push_back(vertex);
        }
    }

    BipartiteGraph bipartiteGraph(n, m, edges);
    long long maxMatching = bipartiteGraph.max_bipartite_matching();
    cout << maxMatching << endl;

    vector<pair<long long, long long>> matchingEdges = bipartiteGraph.get_matching_edges();
    for (const auto& edge : matchingEdges) {
        cout << edge.first << " " << edge.second << endl;
    }

    return 0;
}
