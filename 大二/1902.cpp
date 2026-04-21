#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, d;
    cin >> n >> d;
    
    vector<vector<int>> graph(n+1);
    for (int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    
    vector<int> dist(n+1, -1);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (dist[i] <= d) {
            count++;
        }
    }
    
    cout << count << endl;
    return 0;
}