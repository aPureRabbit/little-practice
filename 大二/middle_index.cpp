#include<iostream>
#include<vector>

using namespace std;

int pivotIndex (vector <int> &nums)
{
    int total=0;
    for(auto num:nums)
    {
        total+= num;
    }
    int left_sum=0;
    for(int i=0;i<nums.size();i++)
    {
        if(left_sum==total-left_sum-nums[i])
            return i;
        left_sum+=nums[i];
    }
    return -1;
}

vector <int> largestSubarray(vector <int> &A, int k) 
{
    vector<int> max(A.begin(),A.begin()+k);
    for(int i=1;i<=A.size()-k;i++)
    {
        for (int i = 1; i <= A.size() - k; i++) 
        {
            vector<int> B(A.begin() + i, A.begin() + i + k);
            bool update = false;
            for (int m = 0; m < k; m++) 
            {
                if (B[m] > max[m]) 
                {
                    update = true;
                    break;
                }
            }
            if (update) 
            {
                max = B;
            }
        }
    }
    return max;
}

int ParkingDilemma (vector <int> &cars, int k)
{
    sort(cars.begin(),cars.end());
    int min=cars[k-1]-cars[0];
    for(int i=1;i<=cars.size()-k;i++)
    {
        int temp=cars[k-1+i]-cars[i];
        if(min>temp)
        {
            min=temp;
        }
    }
    return min+1;
}

int main()
{
    /*vector<int> nums;
    nums={1,7,3,6,5,6};
    cout<<pivotIndex(nums)<<'\n';*/

    vector<int> cars;
    cars={2,10,8,17};
    cout<<ParkingDilemma(cars,3);
}