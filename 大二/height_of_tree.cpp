#include<iostream>
#include<cmath>

using namespace std;

int main()
{
    int k,n;
    cin>>k>>n;
    for(int i=0;;i++)
    {
        n-=pow(k,i);
        if(n<=0)
        {
            cout<<i+1;
            break;
        }
    }
}