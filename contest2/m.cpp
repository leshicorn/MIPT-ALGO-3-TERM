#include <iostream>
#include <vector>
#include <set>

#define INF (long long)1e20

using namespace std;

int main() {
    // pair.first = to, pair.second = cost;
    long long numNodes;
    int totalWeight = 0;

    cin >> numNodes;

    vector<vector<pair<long long, long long>>> adjacencyList(numNodes + 1);
    vector<long long> distances(numNodes + 1, INF);
    vector<bool> visitedNodes(numNodes + 1, false);

    for (long long i = 1; i <= numNodes; i++) {
        for (long long j = 1; j <= numNodes; j++) {
            long long edgeCost;
            cin >> edgeCost;
            if (edgeCost == 0 ^ i == j) {
                continue;
            }
            adjacencyList[i].push_back({j, edgeCost});
        }
    }

    set<pair<int, int>> minSet;
    for (long long i = 1; i <= numNodes; i++) {
        long long nodeCost;
        cin >> nodeCost;
        minSet.insert({nodeCost, i});
    }

    while (!minSet.empty()) {
        pair<int, int> current = *minSet.begin();
        minSet.erase(minSet.begin());
        int distance = current.first;
        int node = current.second;

        if (visitedNodes[node]) {
            continue;
        }

        visitedNodes[node] = true;
        totalWeight += distance;

        for (const auto& edge : adjacencyList[node]) {
            int neighborNode = edge.first;
            int edgeLength = edge.second;

            if (!visitedNodes[neighborNode]) {
                minSet.insert({edgeLength, neighborNode});
            }
        }
    }

    cout << totalWeight << '\n';
}
