#include<iostream>
#include<cstdlib>

using namespace std;

void cmpCountSort(int a[],int b[],int n)
{
    int i, j, *count;
    count = (int *)calloc(n,sizeof(int));
    for (i=0; i<n-1; i++) 
        for (j=i+1; j<n; j++)
            if (a[i] < a[j])
                count[j]++;
            else 
                count[i]++;
    for (i = 0; i<n; i++) 
        b[count[i]] = a[i];
    for ( i = 0; i < n; i++)
    {
        a[count[i]]=i;
    }
    free(count);
}

int main()
{
    int n, *a, *b;
    cin>>n;
    a=(int *)malloc(n*sizeof(int));
    b=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cmpCountSort(a,b,n);
    for(int i=0;i<n;i++)
    {
        cout<<b[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    free(a);
    free(b);
    return 0;
}