# Combinations 系列
## Combinations
### 问题描述
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

**Example**:

        Input: n = 4, k = 2
        Output:
        [
          [2,4],
          [3,4],
          [2,3],
          [1,2],
          [1,3],
          [1,4],
        ]

### 解题思路

为了防止重复，生成的组合有序，因为每个位置上的数字有最大值，比如设组合数组为C，则C[i]的最大值为n-k+1+i;
因此，在产生下一个组合时，从后向前找到没有达到最大值的数，加1，并将后面的数设为初始组合.

        n = 4, k = 2时，初始组合为
        1,2 ，2处的最大值为3，因此可加1
        1,3 同理
        1,4 4达到最大值，以1为开头的组合遍历完毕
        2,3 将1变成2,2后的数字变成初始组合3，即对2依次加1，保证大小顺序
        2,4
        3,4 均达到最大值，遍历结束

```c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> cur;
        for(int i=1; i<=k; i++)
            cur.push_back(i);
        res.push_back(cur);
        while(1){
            int i;
            //找到可以加1的数
            for(i = k-1; i>=0; i--){
                if(cur[i] - i < n - k +1)
                    break;
            }
            //如果没有，遍历结束
            if(i<0)
                break;
            cur[i]++;
            //将加1的数后面的数字变为初始组合
            for(int j = i+1; j < k;j++)
                cur[j] = cur[j-1]+1;
            res.push_back(cur);
            
        }
        
        return res;
    }
};
```

## Combination Sum
### 问题描述
Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

**Note**:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
**Example 1**:

        Input: candidates = [2,3,6,7], target = 7,
        A solution set is:
        [
          [7],
          [2,2,3]
        ]
**Example 2**:

        Input: candidates = [2,3,5], target = 8,
        A solution set is:
        [
          [2,2,2,2],
          [2,3,3],
          [3,5]
        ]

### 解题思路
使用递归实现

```c
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> combination;
        combinationSum(candidates, target, res, combination, 0);
        return res;
        
    }
    void combinationSum(vector<int>& candidates, int target, vector<vector<int>> &res, vector<int>& combination, int start)
    {
        if(target == 0)
        {
            res.push_back(combination);
            return;
        }
        for(int i = start; i < candidates.size() && candidates[i] <= target; i++){
            combination.push_back(candidates[i]);
            //循环时从i开始来实现将同一个数多次使用
            combinationSum(candidates, target-candidates[i], res,combination,i);
            combination.pop_back();

        }
    }
};
```

## Combination Sum II
### 问题描述
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

Each number in candidates may only be used once in the combination.

**Note**:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

        Input: candidates = [10,1,2,7,6,1,5], target = 8,
        A solution set is:
        [
          [1, 7],
          [1, 2, 5],
          [2, 6],
          [1, 1, 6]
        ]
**Example 2**:

        Input: candidates = [2,5,2,1,2], target = 5,
        A solution set is:
        [
          [1,2,2],
          [5]
        ]

### 解题思路
使用递归，但是相邻的相等数字，只添加一次

```c
class Solution {
public:
   vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> combination;
        combinationSum(candidates, target, res, combination, 0);
        return res;
        
    }
    void combinationSum(vector<int>& candidates, int target, vector<vector<int>> &res, vector<int>& combination, int start)
    {
        if(target == 0)
        {
            res.push_back(combination);
            return;
        }
        for(int i = start; i < candidates.size() && candidates[i] <= target; i++){
            // 避免重复
            if(i > start && candidates[i] == candidates[i-1])
                continue;
            combination.push_back(candidates[i]);
            //使用i+1循环，避免同一个数字使用多次
            combinationSum(candidates, target-candidates[i], res,combination,i+1);
            combination.pop_back();

        }
    }
};
```

## Combination Sum III
### 问题描述
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.


**Example 1**:

        Input: k = 3, n = 7
        Output:
        [[1,2,4]]

**Example 2**:

        Input: k = 3, n = 9
        Output:
        [[1,2,6], [1,3,5], [2,3,4]

### 解题思路
和2相似，将数组变成{1,2,3,4,5,6,7,8,9}

## 