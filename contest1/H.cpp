#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<class ForwardIt, class T>
constexpr
void iota(ForwardIt first, ForwardIt last, T value)
{
    while (first != last)
    {
        *first++ = value;
        ++value;
    }
}

vector<int> taskOrder(vector<int> a) {
    int n = a.size();
    vector<int> b(n), order(n), invOrder(n);

    iota(b.begin(), b.end(), 0);
    sort(b.begin(), b.end(), [&](int i, int j) { return a[i] > a[j]; });

    for (int i = 0; i < n; i++) order[b[i]] = i;
    for (int i = 0; i < n; i++) invOrder[order[i]] = i;

    vector<int> result;
    int j = 0;
    while (true) {
        result.push_back(a[j]);
        if (result.size() == n) break;
        int i = j + 1;
        while (i < n && order[i] <= order[j]) i++;
        if (i == n) break;
        j = i;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> result = taskOrder(a);
    cout << result.size() << endl;
    for (int x : result) cout << x + 1 << " ";
    return 0;
}