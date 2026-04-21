#include<iostream>
#include<queue>
#include<vector>
#include<limits>

using namespace std;
const long long INF = numeric_limits<long long>::max();

struct Edge
{
    int to, weight;
};

vector<long long> dijkstra(int start,int n,vector<vector<Edge>> &graph)
{
    vector<long long> dist(n+1,INF);
    dist[start] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, start});

    while(!pq.empty())
    {
        long long d=pq.top().first;
        int u=pq.top().second;
        pq.pop();

        if(d > dist[u]) continue;
        for(const auto &edge:graph[u])
        {
            int v=edge.to;
            int weight=edge.weight;
            if(dist[u]+weight<dist[v])
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
    int n,m,x,y;
    cin >> n >> m >> x >> y;
    vector<vector<Edge>> graph(n + 1);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    vector<long long> lx = dijkstra(x, n, graph);
    long long lx_time =lx[n];
    vector<long long> zs = dijkstra(y, n, graph);
    long long zs_time = zs[n];
    if(lx_time<=zs_time)
    {
        cout<<"YES "<<lx_time<<endl;
    }
    else
    {
        cout<<"NO "<<zs_time<<endl;
    }
    return 0;
}