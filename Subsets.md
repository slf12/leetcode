# Subsets系列
## Subsets
### 问题描述
Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

**Example**:

        Input: nums = [1,2,3]
        Output:
        [
          [3],
          [1],
          [2],
          [1,2,3],
          [1,3],
          [2,3],
          [1,2],
          []
        ]

### 解题思路

在构建子集时，每个元素都可以选择加入或者不加入，使用递归

```c++
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> sub;
        subsets(res,sub,nums,0);
        return res;
    }
    void subsets(vector<vector<int>> &res, vector<int> &sub, vector<int> nums, int start){
        if(start == nums.size()){
            res.push_back(sub);
            return;
        }
        //start不加入子集
        subsets(res,sub,nums,start+1);
        //start加入子集
        sub.push_back(nums[start]);
        subsets(res,sub,nums,start+1);
        sub.pop_back();
    }
};
```

## Subsets II
### 问题描述
Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

**Example**:

    Input: [1,2,2]
    Output:
    [
      [2],
      [1],
      [1,2,2],
      [2,2],
      [1,2],
      []
    ]

### 解题方法
如果数组中的某一个数字重复n次，那么在构造子集时这个数字可以选择加入0次，1次，..., n次

```c++
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        vector<int> sub;
        subsets(res,sub,nums,0);
        return res;
    }
    void subsets(vector<vector<int>> &res, vector<int> &sub, vector<int> nums, int start){
        if(start >= nums.size()){
            res.push_back(sub);
            return;
        }
        int end = start+1;
        while(end < nums.size() && nums[end] == nums[start]){
            end++;
        }
        //加入0次
        subsets(res,sub,nums,end);
        //加入1到n次
        for(int i = 1; i <= end-start; i++){
            int j = i;
            while(j > 0){
                sub.push_back(nums[start]);
                j--;
            }
            subsets(res,sub,nums,end);
            j = i;
            while(j > 0){
                sub.pop_back();
                j--;
            }
        }
    }
};
```