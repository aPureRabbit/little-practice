#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int gcd(int a, int b)
{
    if (a < b)
    {
        swap(a, b);
    }
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int ans(vector<int> &a)
{
    int len = a.size();
    if (len == 0)
    {
        return 0;
    }
    vector<int> dp(len, 1);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (gcd(a[i], a[j]) == 1)
            {
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
    }
    // sort(dp.begin(), dp.end());
    // return dp[0];
    return *max_element(dp.begin(), dp.end());
}

int main()
{
    int n;
    cin>>n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int s = ans(a);
    cout << s;
    return 0;
}