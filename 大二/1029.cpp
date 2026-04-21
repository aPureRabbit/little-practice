#include<iostream>
#include<vector>

using namespace std;

// int max(int a,int b)
// {
//     return (a>b)?a:b;
// }

int solve(int r,int c,vector<vector<int>>& graph,vector<vector<int>>& dp_table)
{
    if(dp_table[r][c]!=-1)
    {
        return dp_table[r][c];
    }
    int dr[4]={-1,1,0,0};
    int dc[4]={0,0,-1,1};
    int max_len_from_here=0;
    for(int i=0;i<4;i++)
    {
        int new_r=r+dr[i];
        int new_c=c+dc[i];
        if(new_r>=0 && new_r<graph.size() && new_c>=0 && new_c<graph[0].size() && graph[new_r][new_c]>graph[r][c])
        {
            max_len_from_here=max(max_len_from_here,solve(new_r,new_c,graph,dp_table));
        }
    }
    dp_table[r][c]=1+max_len_from_here;
    return dp_table[r][c];
}

int main()
{
    int r,c;
    cin>>r>>c;
    vector<vector<int>> graph(r,vector<int>(c));
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>graph[i][j];
        }
    }
    vector<vector<int>> dp_table(r,vector<int>(c,-1));
    int len=0;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            len=max(len,solve(i,j,graph,dp_table));
        }
    }
    cout<<len<<endl;
    return 0;
}