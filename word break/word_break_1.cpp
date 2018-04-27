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