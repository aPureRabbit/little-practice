#include<iostream>
#include<vector>

using namespace std;
int counter=0;

//行矩阵，行和，要求的和
void traceback(vector<int> &row,int index,int rowSum,int sum)
{
    if(index==row.size())
    {
        if(rowSum==sum)
        {
            counter++;
        }
        return;
    }

    for(int i=0;i<=sum-rowSum;i++)
    {
        row[index]=i;
        traceback(row,index+1,rowSum+i,sum);
    }
}

int main()
{
    int sum;
    int n;
    cin>>sum>>n;
    vector <int> row(n,0);
    traceback(row,0,0,sum);
    cout<<counter<<endl;
}