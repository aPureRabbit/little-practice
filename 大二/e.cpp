#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int n,w;
	cin>>n>>w;
	vector<int> stu(n);
	for(int i=0; i<n; i++)
	{
		cin>>stu[i];
	}
	sort(stu.begin(),stu.end());
	int left = 0, right = n - 1;
	int pairs = 0;

	while (left < right)
	{
		if (stu[left] + stu[right] <= w)
		{
			++pairs;
			++left;
			--right;
		}
		else
		{
			--right;
		}
	}

	cout << n - pairs << endl;
	return 0;
}