# Palindrome系列
## Palindrome Number
### 问题描述
Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

**Example 1**:

        Input: 121
        Output: true
        
**Example 2**:

        Input: -121
        Output: false
        Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
**Example 3**:

        Input: 10
        Output: false
        Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

### 解题思路
如果数字为负，则返回false

如果数字为正，则从两头开始判断数字是否相等

```c++
class Solution {
public:
    bool isPalindrome(int x) {
        if( x < 0)
            return false;
        int length = 0;
        
        //获取x的长度
        int x2 = x;
        while(x2 > 0){
            length++;
            x2 /= 10;
        }
        
        if(length == 1)
            return true;
        
        while(x > 0){
            // x%10获取最低位，  x/((int)pow(10, length-1))获取最高位
            if(x % 10 == x/((int)pow(10, length-1))){
                //去掉最高位
                x = x%((int)pow(10, length-1));
                //去掉最低位
                x = x /10;
                length -= 2;
            }
            else
                return false;
        }
        return true;
    }
};
```

## Valid Palindrome
### 问题描述
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

**Example 1**:

        Input: "A man, a plan, a canal: Panama"
        Output: true
        
**Example 2**:

        Input: "race a car"
        Output: false

### 解题思路
使用两个指针l,r从两边开始遍历，如果不是字母，则跳过，如果是则比较是否相等

```c++
class Solution {
public:
    bool isPalindrome(string s) {
        for (int i = 0, j = s.size() - 1; i < j; i++, j--) { 
            //找到第一个字母
            while (isalnum(s[i]) == false && i < j) 
                i++;
            //找到第一个字母 
            while (isalnum(s[j]) == false && i < j) 
                j--; 
            //比较是否相等
            if (toupper(s[i]) != toupper(s[j])) 
                return false; 
    }   
    return true;       
    }
};
```

## Palindrome Partitioning
### 问题描述
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

**Example**:

        Input: "aab"
        Output:
        [
          ["aa","b"],
          ["a","a","b"]
        ]

### 解题思路
使用递归，递归的是以start开始的并是回文的子字符串，依次加入以start开始的回文字符串s[start, end]，然后从end+1处开始基础递归

```c++
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res; 
        int len = s.length();
        if(len <= 0)
            return res;
        vector<string> cur;
        //flag[i][j]记录的是s[i..j]是否是回文字符串
        vector<vector<bool>> flag(len, vector<bool>(len, false));
        for(int i = 0; i < len; i++)
            flag[i][i] = true;
        for(int i = 0; i < len; i++){
            for(int j=i-1; j >= 0; j--){
                if(s[i] == s[j] && (i-j < 2 || flag[j+1][i-1]))
                    flag[j][i] =  true;
            }
        }
        partition(s,0,cur, res, flag);
        return res;
        
    }
    
    void partition(string s, int start, vector<string> cur,vector<vector<string>> &res,  vector<vector<bool>>& flag){
        if(start == s.length()){
            res.push_back(cur);
            return;
        }
        for(int i = start; i < s.length(); i++){
            //找到start开始的字符串加入递归
            if(flag[start][i] == true){
                cur.push_back(s.substr(start, i-start+1));
                partition(s,i+1,cur,res,flag);
                cur.pop_back();
            }
        }
    }
};
```

## Palindrome Partitioning II
### 问题描述
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

**Example**:

        Input: "aab"
        Output: 1
        Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

### 解题思路
使用动态规划解题，dp[i]记录以i开始到结束的字符串需要划分几次变成全是回文的子字符串。
dp[i] = min(dp[j+1]+1 for j in [i+1, n-1] &&  pal[i][j] = true)

pal[i][j]记录s[i..j]是不是回文字符串

```c++
class Solution {
public:
    int minCut(string s) {
        int len = s.length();
        if(len == 0 || len == 1)
            return 0;
        vector<int> dp(len, 0);
        vector<vector<bool >> pal(len, vector<bool>(len, false));
        for(int i = len-1; i >= 0; i--){
            //初始值
            dp[i] = len-i-1;
           for(int j = i; j < len; j++){
               if(s[i] == s[j] && (j-i < 2 || pal[i+1][j-1])){
                   pal[i][j] = true;
                   if(j == len-1)
                       dp[i] = 0;
                   else if(dp[j+1] + 1 < dp[i])
                       dp[i] = dp[j+1]+1;
               }
           }

        }
        return dp[0];
        
    }
};
```

## Shortest Palindrome
### 问题描述
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

**For example**:

        Given "aacecaaa", return "aaacecaaa".

        Given "abcd", return "dcbabcd"

### 解题思路
本题的本质是求以0开头的最长的回文子字符串

```c++
class Solution {
public:
    string shortestPalindrome(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        int longest = 1, start, end;
        //循环回文字符串的中心，并且需要的是以0开头的字符串，那么只需要循环到len/2
        for (int begin = 0; begin <= len / 2;) {
            start = end = begin;
            //将连在一起的相等字符过滤
            while (end < len - 1 && s[end + 1] == s[end])
                ++end;
            //修改begin
            begin = end + 1;
            //从start和end向两头循环，找到以begin为中心的最长的回文串
            while (end < len - 1 && start > 0 && s[end + 1] == s[start - 1]) {
                ++end;
                --start;
            }
            // start = 0表示回文串从0开始，并且需要比已经记录的longest长
            if (start == 0 && longest < end - start + 1)
                longest = end - start + 1;
        }
        // reverse剩下的不是回文的字符串，并添加在字符串之前
        std::string remaining = s.substr(longest, len - longest);
        std::reverse(remaining.begin(), remaining.end());
        return remaining + s;
    }
};
```

## Palindrome Linked List 
### 问题描述
Given a singly linked list, determine if it is a palindrome.

**Follow up**:
Could you do it in O(n) time and O(1) space?

### 解题思路
将链表中点前的节点翻转，和后半部分同时一边向前，一边向后进行比较

- 找中点，使用walk和run两个指针，walk一次走一步，run一次走两步
如果链表是1 -> 2 -> 3 -> 4, run走到3结束，walk走到2，如果链表是1 -> 2 -> 3 -> 4 -> 5，run走到5结束，walk走到3
- 在walk向后的同时将walk走过的节点翻转
- 将walk向前，walk->next向后进行比较

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head == NULL || head->next == NULL)
            return true;
        ListNode* walk = head;
        ListNode* pre = NULL;
        ListNode* tmp = NULL;
        ListNode* runner = head;
        //找到中点并翻转前半部分
        while(runner->next !=NULL && runner->next->next !=NULL){
            runner = runner->next->next;
            tmp = pre;
            pre = walk;
            walk = walk->next;
            pre->next = tmp;
        }
        //如果list长度是奇数
        if(runner->next == NULL) {
            walk = walk->next;
        } else {
            //如果链表长度是偶数
            if(walk->val != walk->next->val)
                return false;
            walk = walk->next->next;
        }
        //一边向前，一边向后比较
        while(pre !=NULL && walk !=NULL){
                if(pre->val != walk->val)
                    return false;
                pre = pre->next;
                walk = walk->next;
        }
        
        return true;
    }
};
```

## Palindrome Permutation
### 问题描述
Given a string, determine if a permutation of the string could form a palindrome.

        For example, "code" -> False, "aab" -> True, "carerac" -> True.

**Hint**:

Consider the palindromes of odd vs even length. What difference do you notice? Count the frequency of each character. If each character occurs even number of times, then it must be a palindrome. How about character which occurs odd number of times?

### 解题方法
可用哈希表法，在字符串中出现的字符的出现次数至多只能有一个奇数
```c++
bool canPermutePalindrome(string s) {
    unordered_map<char, int> map;
    for (char c : s)
        map[c] ++;
    int num = 0;
    for (auto iter = map.begin(); iter != map.end(); iter++) {
        if ((iter->second & 1) == 1)
            num++;
    }
    if (num <= 1)
        return true;
    return false;

}
```

## Palindrome Permutation II
### 问题描述
Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

**For example**:

        Given s = "aabb", return ["abba", "baab"].

        Given s = "abc", return [].

Hint:

If a palindromic permutation exists, we just need to generate the first half of the string.
To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

### 解题思路
提示已经说了，我们只需生成回文字符串的前半个字符串，前半个字符串是生成没有重复的全排列。

```c++
void permute(string &s, char mid, int start, vector<string> &res) {
    if (start >= s.length()) {
        res.push_back(s + mid + string(s.rbegin(), s.rend()));
        return;
    }
    for (int i = start; i < s.length(); i++) {
        int j = i - 1;
        for (j = i - 1; j >= start; j--)
            if (s[j] == s[i])
                break;
        //如果和i同样的字符已经和i交换过，则避免重复，不再交换
        if (j >= start)
            continue;
        swap(s[i], s[start]);
        permute(s, mid, start + 1, res);
        swap(s[i], s[start]);
    }
}

vector<string> generatePalindromes(string s) {
    unordered_map<char, int> map;
    for (char c : s)
        map[c] ++;
    int num = 0;
    string t = "";
    char mid;
    for (auto iter = map.begin(); iter != map.end(); iter++) {
        t += string(iter->second / 2, iter->first);
        if ((iter->second & 1) == 1) {
            num++;
            mid = iter->first;
        }
    }
    vector<string> res;
    //不能生成回文字符串，返回空
    if (num > 1)
        return res;
    permute(t, mid, 0, res);
    return res;
    
}
```

## Palindrome Pairs
### 问题描述
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

**Example 1**:

        Given words = ["bat", "tab", "cat"]
        Return [[0, 1], [1, 0]]
        The palindromes are ["battab", "tabbat"]

**Example 2**:

        Given words = ["abcd", "dcba", "lls", "s", "sssll"]
        Return [[0, 1], [1, 0], [3, 2], [2, 4]]
        The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]

### 解题思路
对于一个word, 将其分成两部分，如果一部分是回文字符串，且另一部分在字典中，则可以组成一个结果

```c++
class Solution {
public:
    bool ispalindrome(string s){
        if(s == "" || s.size() == 1)
            return true;
        int l = 0, r = s.size()-1;
        while(l <=r && s[l] == s[r]){
            l++;
            r--;
        }
        if(l <= r)
            return false;
        return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
         vector<vector<int>> res;
        unordered_map<string, int> map;
        for(int i = 0; i < words.size();i++){
            map[words[i]] = i+1;
        }

        for(int i = 0; i < words.size();i++){
            if(words[i] == ""){
                for(int j = 0; j < words.size(); j++){
                    if( j == i)
                        continue;
                    if(ispalindrome(words[j])){
                        vector<int> v = { j,i};
                        res.push_back(v);
                    }

                }
                continue;
            }
            for(int j = 1; j <= words[i].size(); j++){
                string str1 = words[i].substr(0,j);
                string str2 = words[i].substr(j);
                if(ispalindrome(str1)){
                    string temp = str2;
                    reverse(temp.begin(), temp.end());
                    if(map[temp] != 0){
                        vector<int> v = {map[temp]-1, i};
                        if(map[temp]-1 != i)
                            res.push_back(v);
                    }
                }
                
                if(ispalindrome(str2)){
                    string temp = str1;
                    reverse(temp.begin(), temp.end());
                    if(map[temp] != 0){
                        vector<int> v = { i,map[temp]-1};
                       if(map[temp]-1 != i)
                            res.push_back(v);;
                    }
                }
            }
        }
        return res;
    }
};
```

## Longest Palindrome
### 问题描述
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

**Example**:

    Input:
    "abccccdd"

    Output:
    7
    Explanation:
    One longest palindrome that can be built is "dccaccd", whose length is 7.

###  解题思路
统计字符串中各个数字的出现次数，将每个字符出现的最大的偶数个加入到结果中

```c++
class Solution {
public:
    int longestPalindrome(string s) {
        vector<int> map(256, 0);
        for(auto ch : s)
            map[ch]++;
        int sum = 0;
        for(int i = 0; i < 256; i++){
            if(map[i] % 2 == 0)
                sum+=map[i];
            else {
                sum += map[i]-1;
            }
        }
        
        return sum < s.length() ? sum + 1:sum; 
    }
};
```

## Valid Palindrome II
### 问题描述
Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

**Example 1**:

    Input: "aba"
    Output: True
**Example 2**:

    Input: "abca"
    Output: True
    Explanation: You could delete the character 'c'.

### 解题思路
从两头开始判断，如果遇到不相等的字符，则忽略其中一个继续进行

```c++
class Solution {
public:
    bool validPalindrome(string s) {
        int i = 0, j = s.length() - 1;
        while(i <= j) {
            if(s[i] != s[j]) {
                int p = i+1, q = j;
                while(p <= q){
                    if(s[p] == s[q]){
                        p++;
                        q--;
                    }
                    else
                        break;
                }
                
                if(p > q)
                    return true;
                 p = i, q = j-1;
                while(p <= q){
                    if(s[p] == s[q]){
                        p++;
                        q--;
                    }
                    else
                        break;
                }
                
                if(p > q)
                    return true;
                else
                    return false;
            }
            i++;
            j--;
        }
        return true;
    }
};
```
