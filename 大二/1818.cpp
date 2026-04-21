#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> bisc(n);
    vector<int> eat(n);
    cin >> bisc[0];
    eat[0] = bisc[0];
    for (int i = 1; i < n; i++)
    {
        cin >> bisc[i];
        eat[i] = bisc[i] + eat[i - 1];
    }
    for (int i = 0; i < q; i++)
    {
        int ques;
        cin >> ques;
        int left = 0, right = n;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (eat[mid] < ques)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        cout << left + 1 << " ";
    }
    return 0;
}