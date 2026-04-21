#include <iostream>
#include <vector>
#include <queue>

struct edge
{
    int to, weight;
};

std::vector<int> dijkstra(int s, int n, std::vector<std::vector<edge>> &graph)
{
    std::vector<int> dist(n + 1, __INT_MAX__);
    dist[s] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;
        for (auto &e : graph[u])
        {
            int v = e.to;
            int weight = e.weight;
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
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    std::vector<std::vector<edge>> graph(n+1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    std::vector<int> dist = dijkstra(s, n, graph);
    int result = dist[t];
    std::cout << result << std::endl;
    return 0;
}