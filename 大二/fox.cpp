#include <iostream>

int main()
{
    int n, m;
    std::cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    // if (n - m < m)
    // {
    //     m = n - m;
    // }
    int count = 1;
    for (int i = 1; i < m + 1; i++)
    {
        count = count * (n - m + i) / i;
    }
    std::cout << count;
    return 0;
}