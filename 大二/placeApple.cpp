#include <iostream>
#include <vector>
using namespace std;

int countWays(int m, int n) {
    if (n == 0) {
        return m == 0 ? 1 : 0;
    }
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // 初始化边界条件
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = 1; // 0个苹果只有一种分法
    }
    for (int i = 0; i <= m; ++i) {
        dp[i][1] = 1; // 1个盘子只有一种分法
    }
    
    // 动态规划填表
    for (int i = 1; i <= m; ++i) {
        for (int j = 2; j <= n; ++j) {
            if (i < j) {
                dp[i][j] = dp[i][j - 1];
            } else {
                dp[i][j] = dp[i][j - 1] + dp[i - j][j];
            }
        }
    }
    
    return dp[m][n];
}

int main() {
    int m, n;
    cin >> m >> n; // 输入苹果数量和盘子数量
    cout << countWays(m, n) << endl;
    return 0;
}