#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }
    
    sort(points.begin(), points.end());
    int total_length = points.back() - points.front() + 1;
    
    vector<int> gaps;
    for (int i = 1; i < n; i++) {
        int gap = points[i] - points[i - 1] - 1;
        if (gap > 0) {
            gaps.push_back(gap);
        }
    }
    
    sort(gaps.rbegin(), gaps.rend());
    
    int skip_sum = 0;
    int skip_count = min(m - 1, (int)gaps.size());
    for (int i = 0; i < skip_count; i++) {
        skip_sum += gaps[i];
    }
    
    int min_total = total_length - skip_sum;
    cout << min_total << endl;
    
    return 0;
}