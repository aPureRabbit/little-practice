#include<iostream>

using namespace std;

int main()
{
    int m,v1,v2,t1,t2;
    cin>>m>>v1>>v2>>t1>>t2;
    int time1 = m/v1;
    int time2 = m/(v2*t1)*(t2+t1)+m%(v2*t1)/v2;
    if(m%(v2*t1)==0)
    {
        time2-=t2;
    }
    if(time1<time2)
    {
        cout<<"1";
    }
    else if(time1>time2)
    {
        cout<<"2";
    }
    else
    {
        cout<<"0";
    }
}