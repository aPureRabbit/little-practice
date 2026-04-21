#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 自定义比较器：如果 a+b 大于 b+a，则认为 a 应排在 b 前面
bool cmp(const string &a, const string &b) {
    return a + b > b + a;
}

int main() {
    int n;
    
    while(cin>>n&&n!=0)
    {
        vector<string> nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        
        sort(nums.begin(), nums.end(), cmp);
        
        // 如果最大的数字是 "0"，说明所有数字均为0
        if (nums[0] == "0") {
            cout << "0" << endl;
            return 0;
        }
        
        string result;
        for (const string &s : nums) {
            result += s;
        }
        
        cout << result << endl;
    }
    return 0;
}