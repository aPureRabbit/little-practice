#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m; // 菜品数量和客人数量
    cin >> n >> m;
    vector<long int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 对每位客人，利用二分查找找到第一个满足 a[j] <= b 的位置
    for (int i = 0; i < m; i++)
    {
        long int b;
        cin >> b;
        int left = 0, right = n; // 搜索区间 [left, right)
        while (left < right)
        {
            int mid = (left + right) / 2;
            // 如果 a[mid] <= b，可能还存在更靠前的位置
            if (a[mid] <= b) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        
        // left 即为第一个满足 a[left] <= b 的位置，如果 left == n 则无解
        if (left < n) {
            cout << n - left << "\n";
        }
        else {
            cout << "0\n";
        }
    }
    
    return 0;
}