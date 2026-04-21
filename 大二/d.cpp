#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> dish(n);
    for (int i = 0; i < n; i++)
    {
        cin >> dish[i];
    }
    sort(dish.begin(), dish.end());
    for (int i = 0; i < m; i++)
    {
        int max;
        cin >> max;
        int left = 0, right = n;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (dish[mid] <= max)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        cout << left << endl;
    }
    return 0;
}
