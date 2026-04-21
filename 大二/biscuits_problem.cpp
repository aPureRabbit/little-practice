#include <iostream>
#include <vector>
#include <algorithm>

//前缀和数组    
using namespace std;
int main()
{
    int n, q;
    cin >> n >> q;
    
    vector<int> bis(n);
    for(int i = 0; i < n; i++)
    {
        cin >> bis[i];
    }
    
    vector<int> ask(q);
    for(int i = 0; i < q; i++)
    {
        cin >> ask[i];
    }
    
    // 构造前缀和数组
    vector<int> prefix(n);
    prefix[0] = bis[0];
    for (int i = 1; i < n; i++)
    {
        prefix[i] = prefix[i - 1] + bis[i];
    }
    
    // 对于每个询问，使用二分查找
    for (int i = 0; i < q; i++)
    {
        // lower_bound 返回第一个不小于 ask[i] 的迭代器
        auto it = lower_bound(prefix.begin(), prefix.end(), ask[i]);
        if (it == prefix.end())
        {
            // 如果没有满足条件的，则输出 -1，或者根据题意调整处理
            cout << -1 << " ";
        }
        else
        {
            // 下标从 0 开始，计数需要 +1
            cout << (it - prefix.begin() + 1) << " ";
        }
    }
    return 0;
}