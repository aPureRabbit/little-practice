#include<iostream>
#include<cmath>

using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int x=0;
        cin>>x;
        int y=0;
        int temp=sqrt(x);
        if(temp*temp==x)
        {
            cout<<temp<<endl;
        }
        else if(temp*temp<x)
        {
            if(x-temp*temp<(temp+1)*(temp+1)-x)
            {
                cout<<temp<<endl;
            }
            else
            {
                cout<<temp+1<<endl;
            }
        }
    }
    return 0;
}