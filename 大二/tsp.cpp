#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int tsp(vector<vector<int>> &arr)
{
    int n = arr.size();
    if (n <= 0)
        return 0; // 处理空输入
    if (n == 1)
        return 0; // 单个城市情况

    int allVisitedMask = (1 << n) - 1; // 所有城市都访问过的掩码
    vector<vector<long long>> dp(1 << n, vector<long long>(n, LLONG_MAX));
    dp[1][0] = 0; // 初始状态：从城市0出发，访问过城市0

    // 遍历所有可能的状态
    for (int mask = 1; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            if (!(mask & (1 << i)))
                continue; // 如果城市i未被访问，跳过

            for (int j = 0; j < n; j++)
            {
                if ((mask & (1 << j)) && i != j)
                {                                    // 如果城市j已被访问且不是当前城市i
                    int prev_mask = mask ^ (1 << i); // 去掉城市i的访问状态
                    if (dp[prev_mask][j] != LLONG_MAX)
                    { // 检查是否有有效路径
                        dp[mask][i] = min(dp[mask][i], dp[prev_mask][j] + arr[j][i]);
                    }
                }
            }
        }
    }

    // 计算从最后一个状态返回起点的最小路径
    long long result = LLONG_MAX;
    for (int i = 1; i < n; i++)
    {
        if (dp[allVisitedMask][i] != LLONG_MAX)
        {
            result = min(result, dp[allVisitedMask][i] + arr[i][0]);
        }
    }

    return (result == LLONG_MAX) ? -1 : static_cast<int>(result); // 如果无法完成环路，返回-1
}

int main()
{
    vector<vector<int>> arr = {
        {0, 1, 2},
        {1, 0, 2},
        {2, 2, 0},
    };
    vector<vector<int>> arr2 = {
        {0, 10000, 2},
        {5, 0, 10000},
        {10000, 4, 0},
    };
    int result3 = tsp(arr);
    printf("The minimum cost of the TSP is: %d\n", result3);
    return 0;
}