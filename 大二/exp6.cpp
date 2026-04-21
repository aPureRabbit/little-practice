#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int maxSubArray(vector<int> &nums)
{
    int current_max = nums[0];
    int global_max = nums[0];
    for (int i = 1; i < nums.size(); ++i)
    {
        current_max = max(nums[i], current_max + nums[i]);
        global_max = max(global_max, current_max);
    }
    return global_max;
}

int chooseTasks(vector<int> &low, vector<int> &high)
{
    int n = low.size();
    if (n == 0)
        return 0; // 没有任务
    if (n == 1)
        return low[0]; // 只有一周，只能选择简单任务

    vector<int> dp(n + 1, 0);
    dp[1] = low[0]; // 第 1 周只能选择简单任务

    for (int i = 2; i <= n; ++i)
    {
        dp[i] = max(dp[i - 1] + low[i - 1], dp[i - 2] + high[i - 1]);
    }

    return dp[n];
}

int tsp(std::vector<std::vector<int>> &arr)
{
    int n = arr.size();

    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 0;
    }

    int num_other_cities = n - 1;
    std::vector<std::vector<int>> dp(1 << num_other_cities, std::vector<int>(num_other_cities, std::numeric_limits<int>::max()));

    for (int k_idx = 0; k_idx < num_other_cities; ++k_idx)
    {
        int city_k_actual_val = k_idx + 1;
        if (arr[0][city_k_actual_val] != std::numeric_limits<int>::max())
        {
            dp[1 << k_idx][k_idx] = arr[0][city_k_actual_val];
        }
    }

    for (int mask = 1; mask < (1 << num_other_cities); ++mask)
    {
        // 对于当前mask所代表路径的终点城市 i_city (由i_idx代表)
        for (int i_idx = 0; i_idx < num_other_cities; ++i_idx)
        {
            // 检查城市 (i_idx + 1) 是否真的在当前 mask 中
            if (!((mask >> i_idx) & 1))
            {
                continue;
            }

            // 如果 dp[mask][i_idx] 是无穷大，说明无法到达此状态，不能从此扩展
            if (dp[mask][i_idx] == std::numeric_limits<int>::max())
            {
                continue;
            }

            int city_i_actual_val = i_idx + 1;
            for (int j_idx = 0; j_idx < num_other_cities; ++j_idx)
            {

                if ((mask >> j_idx) & 1)
                {
                    continue;
                }

                int city_j_actual_val = j_idx + 1;
                if (arr[city_i_actual_val][city_j_actual_val] == std::numeric_limits<int>::max())
                {
                    continue;
                }

                int next_mask = mask | (1 << j_idx); // 将城市 (j_idx+1) 加入到mask中
                int new_cost = dp[mask][i_idx] + arr[city_i_actual_val][city_j_actual_val];

                // 更新到下一个状态的最小成本
                if (new_cost < dp[next_mask][j_idx])
                {
                    dp[next_mask][j_idx] = new_cost;
                }
            }
        }
    }

    int final_mask_all_others_visited = (1 << num_other_cities) - 1;
    int min_total_distance = std::numeric_limits<int>::max();

    for (int last_visited_idx = 0; last_visited_idx < num_other_cities; ++last_visited_idx)
    {
        if (dp[final_mask_all_others_visited][last_visited_idx] != std::numeric_limits<int>::max())
        {
            int last_city_actual_val = last_visited_idx + 1;

            if (arr[last_city_actual_val][0] == std::numeric_limits<int>::max())
            {
                continue;
            }

            int cost_to_return = arr[last_city_actual_val][0];
            int path_cost_so_far = dp[final_mask_all_others_visited][last_visited_idx];

            int current_total_distance = path_cost_so_far + cost_to_return;
            min_total_distance = std::min(min_total_distance, current_total_distance);
        }
    }

    return (min_total_distance == std::numeric_limits<int>::max()) ? -1 : min_total_distance;
}

int main()
{
    // vector<int> nums = {-2, 2, -3, 4, -1, 2, 1, -5, 3};
    // int result = maxSubArray(nums);
    // // 输出结果
    // printf("The maximum subarray sum is: %d\n", result);

    // vector<int> low = {4, 2, 3, 7};
    // vector<int> high = {3, 5, 6, 9};
    // int result2 = chooseTasks(low, high);
    // printf("The maximum task sum is: %d\n", result2);

    vector<vector<int>> arr = {
        {0, 10000, 2},
        {5, 0, 10000},
        {10000, 4, 0},
    };
    int result3 = tsp(arr);
    printf("The minimum cost of the TSP is: %d\n", result3);
    return 0;
}