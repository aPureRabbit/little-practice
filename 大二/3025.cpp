#include<iostream>
#include<vector>
#include<queue>

int main()
{
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n+1);
    for(int i=0; i<m; i++)
    {
        int x,y;
        std::cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    std::queue<int> q;
    std::vector<bool> visited(n+1, false);
    q.push(1);
    visited[1] = true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v:graph[u])
        {
            if(!visited[v])
            {
                visited[v]=true;
                q.push(v);
            }
        }
    }
    int count = 0;
    for(int i=1; i<=n; i++)
    {
        if(!visited[i])
        {
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}