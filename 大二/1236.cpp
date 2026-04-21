#include <iostream>
#include <vector>

using namespace std;

long long solve(int i, int j, vector<vector<int>> &table, vector<vector<long long>> &dp)
{
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    int dr[2] = {0, 1};
    int dc[2] = {1, 0};
    long long max_value_from_here = 0;
    for (int k = 0; k < 2; k++)
    {
        int new_i = i + dr[k];
        int new_j = j + dc[k];
        if (new_i >= 0 && new_i < table.size() && new_j >= 0 && new_j < table[0].size())
        {
            max_value_from_here = max(max_value_from_here, solve(new_i, new_j, table, dp));
        }
    }
    dp[i][j] = max_value_from_here + table[i][j];
    return dp[i][j];
}

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<int>> table(m, vector<int>(n));
    vector<vector<long long>> dp(m, vector<long long>(n, -1));
    long long max_value = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> table[i][j];
        }
    }
    max_value = max(max_value, solve(0, 0, table, dp));
    cout << max_value << endl;
    return 0;
}