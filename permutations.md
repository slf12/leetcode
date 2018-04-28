# Permutations 系列
## Permutations
### 问题描述
Given a collection of distinct integers, return all possible permutations.

**Example**:

    Input: [1,2,3]
    Output:
    [
      [1,2,3],
      [1,3,2],
      [2,1,3],
      [2,3,1],
      [3,1,2],
      [3,2,1]
    ]

### 解题思路
使用和后面的数字逐一交换的方式来实现改位置上应该出现的所有数字的可能
比如 1,2,3
第一个位置上有3种可能，1已经符合，2和3通过和1交换位置出现在位置1上

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        //替换0位置的数字
        permute(res, nums, 0);
        return res;
    }
    void permute(vector<vector<int>> &res, vector<int>& nums, int start){
        if(start >= nums.size())
        {
            res.push_back(nums);
            return;
        }
        //从start开始, 和start交换位置，实现所有可能
        for(int i = start; i < nums.size();i++)
        {
            swap(nums[start], nums[i]);
            //交换start+1处的数字，实现排列
            permute(res, nums, start+1);
            //交换后需要变回原来的位置，以便下一次交换
            swap(nums[start], nums[i]);

        }
    }
};
```

## Permutations II
### 问题描述
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

**Example**:

    Input: [1,1,2]
    Output:
    [
    [1,1,2],
    [1,2,1],
    [2,1,1]
    ]

### 解题思路
和上一个问题的不同之处在于数字有重复，那么在交换时遇到已经交换过的数字则不再交换

    错误代码
下面代码结果有重复，因为在交换时使用```if(i != pos && nums[i] == nums[pos]) continue; ```来判断是否交换过，是不正确的，因为虽然刚开始对数组进行了排序，但是经过交换后，数组不再有序

```c++
class Solution {
public:
    void permute(vector<vector<int>>& res, int pos, vector<int>& nums)//0...pos-1 already permutated
    {
        if(pos == nums.size())
        {
            res.push_back(nums);
            return;
        }
        for(int i = pos; i < nums.size(); ++i)
        {
            if(i != pos && nums[i] == nums[pos]) continue;
            swap(nums[i], nums[pos]);
            permute(res, pos + 1, nums);
            swap(nums[i], nums[pos]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
         vector<vector<int>> res;
        if(nums.empty())return res;
        sort(nums.begin(), nums.end());
        permute(res, 0, nums);
        return res;
    }

};
```

    正确代码

```c++
class Solution {
public:
    void permute(vector<vector<int>>& res, int pos, vector<int>& nums)//0...pos-1 already permutated
    {
        if(pos == nums.size())
        {
            res.push_back(nums);
            return;
        }
        for(int i = pos; i < nums.size(); ++i)
        {
            //if(i != pos && nums[i] == nums[pos]) continue;
            int j = i-1;
            while(j >= pos){
                if(nums[j] == nums[i])
                    break;
                j--;
            }
            if(j >= pos)
                continue;
            swap(nums[i], nums[pos]);
            permute(res, pos + 1, nums);
            swap(nums[i], nums[pos]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
         vector<vector<int>> res;
        if(nums.empty())return res;
        sort(nums.begin(), nums.end());
        permute(res, 0, nums);
        return res;
    }

};
```

## Next Permutation

### 问题描述
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

    1,2,3 → 1,3,2
    3,2,1 → 1,2,3
    1,1,5 → 1,5,1

### 解题思路
字典序思想, 设数组为A
1、find k = max{i | A<sub>i</sub> < A<sub>i+1</sub>}
2、find l = max{i | A<sub>i</sub> > A<sub>j</sub>}
3、交换 A<sub>k</sub>和A<sub>l</sub>
4、将A<sub>k+1</sub>...A<sub>n</sub>翻转
即可得到下一个全排列

```c++
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int k = -1;
      for (int i = nums.size() - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
          k = i;
          break;
        }
      } 
      if (k == -1) {
          reverse(nums.begin(), nums.end());
          return;
      }
      int l = -1;
      for (int i = nums.size() - 1; i > k; i--) {
        if (nums[i] > nums[k]) {
          l = i;
          break;
        } 
      } 
      swap(nums[k], nums[l]);
      reverse(nums.begin() + k + 1, nums.end()); 
    }
};
```

## Permutation Sequence
### 问题描述

The set [1,2,3,...,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

1. "123"
2. "132"
3. "213"
4. "231"
5. "312"
6. "321"
Given n and k, return the kth permutation sequence.

Note:

Given n will be between 1 and 9 inclusive.
Given k will be between 1 and n! inclusive.
**Example 1**:

    Input: n = 3, k = 3
    Output: "213"
    Example 2:

    Input: n = 4, k = 9
    Output: "2314"

###解题思路

从高位开始逐一确定

例如n=4, 最小的数字是1开头，如果k <= 3! 即2,3,4三个数字的全排列，则第一个数字是1，同理如果3! < k <= 2*3!, 则最高位是2

当确定完最高位之后，确定下一位，以此类推

```c++
class Solution {
public:
    string getPermutation(int n, int k) {
        string ret;
        //记录i!
        vector<int> factorial(n,1);
        vector<char> num(n,1);
        
        for(int i=1; i<n; i++) 
            factorial[i] = factorial[i-1]*i;
        
        for(int i=0; i<n; i++)
            num[i] = (i+1)+'0';
        
        k--;
        for(int i=n; i>=1; i--) {
            //最高位在数组中的顺序
            int j = k/factorial[i-1];
            //剩下的个数
            k %= factorial[i-1];
            ret.push_back(num[j]);
            //除去已经用过的数字
            num.erase(num.begin()+j);
        }
        
        return ret;
    }
};
```