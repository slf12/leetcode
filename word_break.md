# word break 
## 题目描述

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:



- The same word in the dictionary may be reused multiple times in the segmentation.
- You may assume the dictionary does not contain duplicate words.

**Example 1**:


    Input: s = "leetcode", wordDict = ["leet", "code"]
    Output: true
    Explanation: Return true because "leetcode" can be segmented as "leet code".

**Example 2**:

    Input: s = "applepenapple", wordDict = ["apple", "pen"]
    Output: true
    Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
    Note that you are allowed to reuse a dictionary word.

**Example 3**:

    Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
    Output: false

## 解题思路

使用动态规划数组*dp*来记录s中前i个字符能否拆分成字典中的数字

    dp[i] = true if 存在j属于0到i-1，且dp[j]为true, s[j..i]在字典中
    否则为false

```c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int len = s.length();
        // dp[i]表示s前i个字符能否被字典表示
        vector<bool> dp(len+1, false);
        dp[0]=true;
        for(int i = 1; i <= len;i++){
            //循环0到i-1，判断是否存在0..j为true, 并s[j..i]在字典中
            for(int j = 0; j < i;j++){
                vector<string>::iterator it = find(wordDict.begin(), wordDict.end(), s.substr(j, i-j));
                if(dp[j] && it != wordDict.end()){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[len];
                                                   
    }
};
```
