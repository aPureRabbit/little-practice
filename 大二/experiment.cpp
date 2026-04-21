#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Interval
{
    int start;
    int end;
};

bool canAttendMeetings(vector<Interval> &intervals)
{
    if (intervals.empty())
    {
        return true;
    }
    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b)
         { return a.start < b.start; });
    for (int i = 1; i < intervals.size(); i++)
    {
        if (intervals[i].start < intervals[i - 1].end)
        {
            return false;
        }
    }
    return true;
}

int minMeetingRooms(vector<Interval> &intervals)
{
    if (intervals.empty())
    {
        return 0;
    }
    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b)
         { return a.start < b.start; });

    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (const auto &interval : intervals)
    {
        if (!minHeap.empty() && minHeap.top() <= interval.start)
        {
            minHeap.pop();
        }
        minHeap.push(interval.end);
    }

    return minHeap.size();
}

string largestNumber(vector<int> &nums)
{
    sort(nums.begin(), nums.end(), [](int a, int b)
         { return to_string(a) + to_string(b) > to_string(b) + to_string(a); });
    if (nums[0] == 0)
    {
        return "0";
    }
    string result;
    for (int num : nums)
    {
        result += to_string(num);
    }
    return result;
}

int main()
{
    vector<Interval> intervals = {{0, 30}, {5, 10}, {15, 20}};
    // bool flag = canAttendMeetings(intervals);
    // if (flag)
    // {
    //     cout << "True" << endl;
    // }
    // else
    // {
    //     cout << "False" << endl;
    // }
    // int count=minMeetingRooms(intervals);
    // cout << "Minimum number of meeting rooms required: " << count << endl;
    vector<int> nums={1,20,23,4,8};
    string str=largestNumber(nums);
    cout << "Largest number: " << str << endl;
}