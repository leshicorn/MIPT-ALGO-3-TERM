#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to;
    int cost;
    int time;
};

const int INF = INT_MAX;

int main() {
    int N, M, T;
    cin >> N >> M >> T;

    vector<vector<Edge>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int Ai, Bi, Pi, Ti;
        cin >> Ai >> Bi >> Pi >> Ti;
        graph[Ai].push_back({Bi, Pi, Ti});
        graph[Bi].push_back({Ai, Pi, Ti});
    }

    vector<vector<int>> distance(N + 1, vector<int>(T + 1, INF));
    vector<vector<int>> cost(N + 1, vector<int>(T + 1, INF));
    vector<vector<int>> parent(N + 1, vector<int>(T + 1, -1));

    distance[1][0] = 0;
    cost[1][0] = 0;

    priority_queue<pair<pair<int, int>, int>> pq;  // {{-distance, -time}, vertex}
    pq.push({{-distance[1][0], 0}, 1});

    while (!pq.empty()) {
        int current_vertex = pq.top().second;
        int current_distance = -pq.top().first.first;
        int current_time = -pq.top().first.second;
        pq.pop();

        for (const Edge& edge : graph[current_vertex]) {
            int to = edge.to;
            int new_distance = current_distance + edge.cost;
            int new_time = current_time + edge.time;

            if (new_time <= T && new_distance < distance[to][new_time]) {
                distance[to][new_time] = new_distance;
                cost[to][new_time] = cost[current_vertex][current_time] + edge.cost;
                parent[to][new_time] = current_vertex;
                pq.push({{-new_distance, -new_time}, to});
            }
        }
    }

    int min_cost = INF;
    int min_time = -1;
    for (int time = 0; time <= T; ++time) {
        if (distance[N][time] < INF && cost[N][time] < min_cost) {
            min_cost = cost[N][time];
            min_time = time;
        }
    }

    if (min_time == -1) {
        cout << -1 << endl;
    } else {
        cout << min_cost << endl;

        vector<int> path;
        int current_vertex = N;
        int current_time = min_time;

        while (current_vertex != -1) {
            path.push_back(current_vertex);
            int next_vertex = parent[current_vertex][current_time];
            if (next_vertex == -1) break;
            current_time -= graph[next_vertex][0].time;  // Assuming all edges from a vertex have the same time
            current_vertex = next_vertex;
        }

        cout << path.size() << endl;
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
