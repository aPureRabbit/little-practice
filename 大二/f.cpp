#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<double> arr(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	double result = arr[0];
	double current_max = arr[0];
	double current_min = arr[0];
	for (int i = 1; i < n; i++)
	{
		double temp = current_max;
		current_max = max({arr[i], arr[i] * current_max, arr[i] * current_min});
		current_min = min({arr[i], arr[i] * temp, arr[i] * current_min});
		result = max(current_max, result);
		// cout << "temp: " << temp
		// 	 << "max: " << current_max
		// 	 << "min: " << current_min
		// 	 << "retult: " << result
		// 	 << endl;
	}
	cout << (int)result;
	return 0;
}
