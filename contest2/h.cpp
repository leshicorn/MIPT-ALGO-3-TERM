#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
#include <limits.h>

using namespace std;

long long ambig_component = 0;
long long timer = 0;
vector<vector<long long>> graph;
vector<bool> visited;
vector<long long> return_time;
vector<long long> in_time;
vector<long long> out_time;
vector<long long> parents;
vector<long long> answer;
set<long long> strong_comp_set;
long long strong_comp_count = 0;


void dfs(const vector<vector<pair<long long, long long>>>& graph, long long s, long long parent = -1);
void updateReturnTime(long long s, long long child);
void processStrongComponent(long long s, long long child);

void dfs(const vector<vector<pair<long long, long long>>>& graph, long long s, long long parent) {
    parents[s] = parent;
    in_time[s] = timer++;
    return_time[s] = in_time[s];
    visited[s] = true;

    for (auto to : graph[s]) {
        if (to.first == parent) {
            continue;
        }

        if (visited[to.first]) {
            return_time[s] = min(return_time[s], in_time[to.first]);
        } else {
            dfs(graph, to.first, s);
            updateReturnTime(s, to.first);

            if (return_time[to.first] == in_time[to.first]) {
                processStrongComponent(s, to.second);
            }
        }
    }
}

void updateReturnTime(long long s, long long child) {
    return_time[s] = min(return_time[s], return_time[child]);
}

void processStrongComponent(long long s, long long child) {
    strong_comp_set.insert(child);
    strong_comp_count++;
}


void dfs_ambig_comp(const vector<vector<long long>>& graph, long long s, vector<int>& color, vector<long long>& parents, vector<long long>& answer, long long parent = -1) {
    color[s] = 1;
    parents[s] = parent;

    for (auto to : graph[s]) {
        if (color[to] != 0) {
            continue;
        } else {
            answer[to] = ambig_component;
            dfs_ambig_comp(graph, to, color, parents, answer, s);
        }
    }

    color[s] = 2;
}

int main() {

    long long n, m;
    cin >> n >> m;

    visited.assign(n + 1, false);
    vector<vector<pair<long long, long long>>> graph(n + 1);
    in_time.assign(n + 1, 0);
    out_time.assign(n + 1, 0);
    return_time.assign(n + 1, INT_MAX - 100);
    vector<pair<long long, long long>> pers(m + 1);
    vector<int> color(n + 1, 0);
    vector<long long> parentss(n + 1);
    vector<long long> answers(n + 1);
    parents.assign(n + 1, 0);

    for (long long i = 1; i <= m; i++) {
        long long first, second;
        cin >> first >> second;
        pers[i] = make_pair(first, second);
        graph[first].push_back(make_pair(second, i));
        graph[second].push_back(make_pair(first, i));
    }

    for (long long i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(graph, i);
        }
    }

    vector<long long> components(n + 1, 0);
    vector<vector<long long>> graphs(n + 1);

    for (long long i = 1; i <= m; i++) {
        if (strong_comp_set.find(i) == strong_comp_set.end()) {
            long long first, second;
            first = pers[i].first;
            second = pers[i].second;
            graphs[first].push_back(second);
            graphs[second].push_back(first);
        }
    }

    ambig_component = 0;

    for (long long i = 1; i <= n; i++) {
        if (color[i] == 0) { 
            ambig_component++;
            answers[i] = ambig_component;
            dfs_ambig_comp(graphs, i, color, parentss, answers);
        }
    }

    long long ambig_componentrr = 0;

    for (auto iter : strong_comp_set) {
        components[answers[pers[iter].first]]++;
        components[answers[pers[iter].second]]++;
    }

    for (auto dstrong_comp_count : components) {
        if (dstrong_comp_count == 1) {
            ambig_componentrr++;
        }
    }

    cout << (ambig_componentrr + 1) / 2 << '\n';
}
