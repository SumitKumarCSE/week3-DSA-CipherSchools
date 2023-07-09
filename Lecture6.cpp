#include<bits/stdc++.h>
using namespace std;

// Edit Distance
int solve(string& s, string& t, int i, int j, vector<vector<int>>& dp) {
    if(i < 0) return j+1;
    if(j < 0) return i+1;
    if(dp[i][j] != -1) return dp[i][j];
    if(s[i] == t[j]) return dp[i][j] = solve(s, t, i-1, j-1, dp);
    return dp[i][j] = 1 + min(solve(s, t, i, j-1, dp), min(solve(s, t, i-1, j, dp), solve(s, t, i-1, j-1, dp)));
}
int minDistance(string s, string t) {
    if(s == t) return 0;
    int n = s.length(), m = t.length();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    int i = s.length()-1, j = t.length() -1;
    return solve(s, t, i ,j, dp);
}
    
int main() {
    string word1 = "intention", word2 = "execution";
    cout<<"Minimum Operations to convert word1 to word2: "<<minDistance(word1, word2)<<endl;
    return 0;
}
