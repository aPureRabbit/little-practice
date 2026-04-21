#include<iostream>
#include<queue>

using namespace std;

int main()
{
    int T; //游戏轮数
    cin >> T;
    while(T--)
    {
        int n; //排数
        cin>>n;
        queue<int> q;
        for(int i=1; i<=n; i++)
        {
            q.push(i);
        }
        while(q.size()>1)
        {
            q.pop();
            q.push(q.front());
            q.pop();
        }
        cout<<q.front()<<endl;
    }
}