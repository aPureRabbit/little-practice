#include <iostream>
#include <vector>
using namespace std;

// 生成所有可能的行向量（元素和为L）
vector<vector<int>> generate_vectors(int N, int L) {
    vector<vector<int>> res;
    if (N == 2) {
        for (int a0 = 0; a0 <= L; a0++) {
            int a1 = L - a0;
            res.push_back({a0, a1, 0, 0});
        }
    } else if (N == 3) {
        for (int a0 = 0; a0 <= L; a0++) {
            for (int a1 = 0; a1 <= L - a0; a1++) {
                int a2 = L - a0 - a1;
                res.push_back({a0, a1, a2, 0});
            }
        }
    } else if (N == 4) {
        for (int a0 = 0; a0 <= L; a0++) {
            for (int a1 = 0; a1 <= L - a0; a1++) {
                for (int a2 = 0; a2 <= L - a0 - a1; a2++) {
                    int a3 = L - a0 - a1 - a2;
                    res.push_back({a0, a1, a2, a3});
                }
            }
        }
    }
    return res;
}

int main() {
    int L, N;
    cin >> L >> N;
    
    // 预处理所有行向量
    vector<vector<int>> vectors = generate_vectors(N, L);
    
    // 初始化DP数组（5维：行数×各列和）
    int dp[5][10][10][10][10] = {};
    dp[0][0][0][0][0] = 1;
    
    // DP过程：逐行处理
    for (int row = 0; row < N; row++) {
        for (int c0 = 0; c0 <= L; c0++) {
            for (int c1 = 0; c1 <= L; c1++) {
                for (int c2 = 0; c2 <= L; c2++) {
                    for (int c3 = 0; c3 <= L; c3++) {
                        if (dp[row][c0][c1][c2][c3] == 0) continue;
                        
                        // 遍历所有行向量
                        for (auto& vec : vectors) {
                            int a0 = vec[0], a1 = vec[1], a2 = vec[2], a3 = vec[3];
                            
                            // 检查向量是否有效（元素不超过列剩余容量）
                            if (a0 <= L - c0 && a1 <= L - c1 && 
                                (N < 3 || a2 <= L - c2) && 
                                (N < 4 || a3 <= L - c3)) {
                                
                                // 更新下一行状态
                                int n0 = c0 + a0;
                                int n1 = c1 + a1;
                                int n2 = (N >= 3) ? c2 + a2 : 0;
                                int n3 = (N >= 4) ? c3 + a3 : 0;
                                dp[row+1][n0][n1][n2][n3] += dp[row][c0][c1][c2][c3];
                            }
                        }
                    }
                }
            }
        }
    }
    
    // 提取结果（根据N取不同状态）
    int ans = 0;
    if (N == 2) {
        ans = dp[N][L][L][0][0];
    } else if (N == 3) {
        ans = dp[N][L][L][L][0];
    } else if (N == 4) {
        ans = dp[N][L][L][L][L];
    }
    cout << ans << endl;
    
    return 0;
}