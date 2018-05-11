## Maximum Gap

### 问题描述
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Return 0 if the array contains less than 2 elements.

**Example 1:**

	Input: [3,6,9,1]
	Output: 3
	Explanation: The sorted form of the array is [1,3,6,9], either
	             (3,6) or (6,9) has the maximum difference 3.
**Example 2:**

	Input: [10]
	Output: 0
	Explanation: The array contains less than 2 elements, therefore return 0.
	
Note:

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
Try to solve it in linear time/space.


### 解决方法
**使用系统排序**

```c++
class Solution {
public:
   int maximumGap(vector<int>& nums) {
        int size = nums.size();
        if(size < 2)
            return 0;
        sort(nums.begin(), nums.end());
        int res = -1;
        for(int i = 1; i < size; i++)
            res = max(res, nums[i]-nums[i-1]);
        return res;
     }
};
```
时间复杂度为O(nlogn)，不符合要求

**桶排序法**

题目中要求最大差，最大差值的下限为(max\_val - min\_val) / length, 这是均匀分布的情况下，如果不均与分布，那么最大差肯定会比这个大，那么可以确定一个桶中数字的范围是(max\_val - min\_val) / length+1， 在这个桶中，只需记录最大值和最小值，因为桶内部的差值肯定小于最大值的下限。然后找到相邻桶之间的差值即可。

```c++
class Solution {
public:
   int maximumGap(vector<int>& nums) {
        int size = nums.size();
        if(size < 2)
            return 0;
       int min_val = nums[0];
       int max_val = nums[0];
       for(int n : nums){
           min_val = min(n, min_val);
           max_val = max(n, max_val);
       }
       //桶中数字的长度
       int len = (max_val - min_val) / size+1;
       //桶的个数
       vector<vector<int>> bucket((max_val - min_val) / len + 1);
       for(int n : nums){
       	 //计算数字n属于哪个桶
           int i = (n-min_val) / len;
           if(bucket[i].empty()){
               bucket[i].reserve(2);
               bucket[i].push_back(n);
               bucket[i].push_back(n);              
           }
           else{
               bucket[i][0] = min(bucket[i][0], n);
               bucket[i][1] = max(bucket[i][1], n);
           }
       }
       
       int res = 0;
       int prev = 0;
       for(int i = 1; i < (max_val - min_val) / len + 1; i++){
           if(bucket[i].empty())
               continue;
           res = max(res, bucket[i][0] - bucket[prev][1]);
           prev = i;
       }
       return res;
    }
};
```