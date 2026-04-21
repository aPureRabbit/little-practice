
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int capacity, vector<int>& weights, vector<int>& values) {
    int n = weights.size();
    vector<int> dp(capacity + 1, 0);
    
    for (int i = 0; i < n; ++i) {
        for (int j = capacity; j >= weights[i]; --j) {
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
        }
    }
    
    return dp[capacity];
}

int main() {
    int n, capacity;
    cin >> capacity;
    cin >> n;
    
    vector<int> weights(n), values(n);
    for (int i = 0; i < n; ++i) {
        cin >> weights[i] >> values[i];
    }
    
    cout << knapsack(capacity, weights, values) << endl;
    
    return 0;
}