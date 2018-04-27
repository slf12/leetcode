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

<img src="http://chart.googleapis.com/chart?cht=tx&chl=\Large dp[i]= test " style="border:none;">

When \\( a \ne 0 \\), there are two solutions to \\(ax^2 + bx + c = 0\\) and they are:
$$ x = {-b \pm \sqrt{b^2-4ac} \over 2a} $$

$$
\begin{aligned}
\dot{x} & = \sigma(y-x) \\
\dot{y} & = \rho x - y - xz \\
\dot{z} & = -\beta z + xy
\end{aligned}
$$

