#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Coin {
    int m;       // 重量
    int v;       // 价值
    double ratio; // 单位价值
};

int main()
{
    int N, T;
    cin >> N >> T;
    vector<Coin> coins(N);
    for (int i = 0; i < N; i++)
    {
        cin >> coins[i].m >> coins[i].v;
        coins[i].ratio = double(coins[i].v) / coins[i].m;
    }
    // 按照单位价值降序排列
    sort(coins.begin(), coins.end(), [](const Coin& a, const Coin& b){
        return a.ratio > b.ratio;
    });
    
    double ans = 0;
    int remain = T;
    for (int i = 0; i < N && remain > 0; i++)
    {
        if (remain >= coins[i].m)
        {
            ans += coins[i].v;
            remain -= coins[i].m;
        }
        else
        {
            ans += coins[i].ratio * remain;
            remain = 0;
        }
    }
    cout <<(int)ans<<endl;
    return 0;
}
