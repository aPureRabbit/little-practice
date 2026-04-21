#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Edge
{
    int u, v;
    int weight;
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

struct DSU
{
    std::vector<int> parent;
    DSU(int n)
    {
        parent.resize(n + 1);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int i)
    {
        if (parent[i] == i)
        {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j)
        {
            parent[root_i] = root_j;
        }
    }
};

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    std::sort(edges.begin(), edges.end());
    DSU dsu(n);
    int edges_in_mst = 0;
    int longest_edge_in_mst = 0;
    for (const Edge &edge : edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            dsu.unite(edge.u, edge.v);
            longest_edge_in_mst = edge.weight;
            edges_in_mst++;
        }
        if (edges_in_mst == n - 1)
        {
            break;
        }
    }

    std::cout << longest_edge_in_mst << std::endl;
    return 0;
}