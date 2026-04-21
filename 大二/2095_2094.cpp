#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<vector<int>> graph(n,vector<int>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>graph[i][j];
        }
    }
    int count=0;
    for(int i=0;i<n;i++)
    {
        int degree=0;
        for(int j=0;j<n;j++)
        {
            if(graph[i][j]==1)
            {
                degree++;
            }
        }
        if(degree%2!=0)
        {
            count++;
        }
    }
    if(count==0||count==2)
    {
        cout<<"YES"<<endl;
    }
    else
    {
        cout<<"NO"<<endl;
    }
    return 0;
}