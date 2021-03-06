/*
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t

We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1. 
*/


/* Recursive Solution: $o(4^{n})$ Time */
class Solution {
public:
    bool isScramble(string s1, string s2) {
        // base case for recursion
        if (s1.size() != s2.size())  return false;
        if (s1 == s2)  return true;
        int n = s1.size();
        
        // check if s1 and s2 contain the characters
        vector<int> ht(256,0);
        for (char c : s1) ht[c - 'a']++;
        for (char c : s2) {
            if (--ht[c - 'a'] < 0) return false;
        }
      
        for (int k = 1; k < n; k++) {
            if(isScramble(s1.substr(0, k), s2.substr(0, k)) && isScramble(s1.substr(k), s2.substr(k))) return true;
            if(isScramble(s1.substr(0, k), s2.substr(n-k)) && isScramble(s1.substr(k), s2.substr(0, n-k))) return true;
        }
        
        return false;
    }
};



/*
The above implementation repeats a lot of identical searches. This should ring the "DP bell" in your head: we can use DP as a memorizaton tool to keep track of the intermediate (optimal) results we have alrady computed. In this case the optimal result is knowning substring of s1 and s2 are scrambling string or not.

Everytime DP is used a memorization, there is usually DFS/BFS around since the DFS/BFS *defines* what intermediate means.

DP Memorization + DFS: O(n^4) Time, O(n^3) Space.
*/
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size())  return false;
        if (s1 == s2)  return true;
        int n = s1.size();
        // dp[l][i][j] = 1 if s1.substr(i,l) and s2.substr(j,l) are scrambling
        // dp[l][i][j] = -1 if otherwise
        // dp[l][i][j] = 0 indicates this value has not been computed
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(n, vector<int>(n, 0)));
        return isScrambleRecur(s1, s2, dp, n, 0, 0) == 1 ? true : false;
    }
    
     // compute if s1.substr(n1, len) and s2.substr(n2, len) are scrambling
    int isScrambleRecur(string s1, string s2, vector<vector<vector<int>>> &dp, int len, int n1, int n2) {
        if (dp[len][n1][n2]) return dp[len][n1][n2];
        if (s1.substr(n1, len) == s2.substr(n2, len)) {
            dp[len][n1][n2] = 1;
            return dp[len][n1][n2];
        }
        vector<int> ht(256, 0);
        for (int i = n1; i < n1 + len; i++) ht[s1[i] - 'a']++;
        for (int i = n2; i < n2 + len; i++) {
            if (--ht[s2[i] - 'a'] < 0) {
                dp[len][n1][n2] = -1;
                return dp[len][n1][n2];
            }
        }
        
        for (int k = 1; k < len; k++) {
            if (isScrambleRecur(s1, s2, dp, k, n1, n2) == 1 && isScrambleRecur(s1, s2, dp, len-k, n1+k, n2+k) == 1) {
                dp[len][n1][n2] = 1;
                return dp[len][n1][n2];
            }
            if (isScrambleRecur(s1, s2, dp, k, n1, n2+len-k) == 1 && isScrambleRecur(s1, s2, dp, len-k, n1+k, n2) == 1) {
                dp[len][n1][n2] = 1;
                return dp[len][n1][n2];
            }
        }
        
        dp[len][n1][n2] = -1;
        return dp[len][n1][n2];
    }
};



/* DP Implementation 2: O(n^4) Time, O(n^3) Space */
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size())  return false;
        if (s1.empty())  return true;
        int n = s1.size();
        // dp[l][i][j] = true if s1.substr(i,l) and s2.substr(j,l) are scambling
        vector<vector<vector<bool>>> dp(n+1, 
        vector<vector<bool>>(n, vector<bool>(n, false)));
        // initialization: dp[1][i][j]
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[1][i][j] = (s1[i] == s2[j]);
            }
        }
        // state transfer
        for (int l = 2; l <= n; l++) {
            for (int i = 0; i+l <= n; i++) { // careful with the bound on i
                for (int j = 0; j+l <= n; j++) { // careful with the bound on j
                    for (int k = 1; k < l; k++) {
                        dp[l][i][j] = (dp[k][i][j] && dp[l-k][i+k][j+k]) || 
                        (dp[k][i][j+l-k] && dp[l-k][i+k][j]);
                        if (dp[l][i][j])  break;
                    }
                }
            }
        }
        return dp[n][0][0];
    }
};
