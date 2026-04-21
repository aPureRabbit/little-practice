#include <iostream>
#include <vector>

using namespace std;

int CountPaths(int currentX, int currentY, int targetX, int targetY, vector<vector<int>> &memo)
{
    if (currentX == targetX && currentY == targetY)
        return 1;

    if (currentX > targetX || currentY > targetY)
        return 0;

    if (memo[currentX][currentY] != -1)
        return memo[currentX][currentY];

    int paths = 0;
    int dx[] = {2, 1};
    int dy[] = {1, 2};
    for (int i = 0; i < 2; ++i)
    {
        int newX = currentX + dx[i];
        int newY = currentY + dy[i];
        if (newX <= targetX && newY <= targetY)
            paths += CountPaths(newX, newY, targetX, targetY, memo);
    }
    memo[currentX][currentY] = paths;
    return paths;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
    int paths = CountPaths(1, 1, n, m, memo);
    cout << paths << endl;
    return 0;
}