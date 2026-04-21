#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge
{
    int to, weight;
};

vector<int> dijkstra(int start, int n, vector<vector<Edge>> &graph)
{
    vector<int> dist(n + 1, __INT_MAX__);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;
        for (auto &edge : graph[u])
        {
            int v = edge.to;
            int weight = edge.weight;
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main()
{
    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<Edge>> graph(n+1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    vector<int> go_home = dijkstra(x, n, graph);
    int max = 0;
    for (int i = 1; i <= n; i++)
    {
        vector<int> go_to_x = dijkstra(i, n, graph);
        int one = go_to_x[x] + go_home[i];
        if (one > max)
        {
            max = one;
        }
    }
    cout << max << endl;
    return 0;
}