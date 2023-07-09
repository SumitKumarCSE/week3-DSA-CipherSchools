#include<bits/stdc++.h>
using namespace std;

// Longest Increasing Path in a Matrix
int solve(vector<vector<int>>& matrix, int i, int j, int m, int n, vector<vector<int>>& vis) {
    if(vis[i][j] != -1) return vis[i][j];
    long count1= 1, count2 = 1, count3 = 1, count4 = 1;
    if(i-1 >= 0 && matrix[i][j] > matrix[i-1][j]) 
        count1 = 1 + solve(matrix, i-1, j, m, n, vis);
    if(j-1 >= 0 && matrix[i][j] > matrix[i][j-1])
        count2 = 1 + solve(matrix, i, j-1, m, n, vis);
    if(i+1 < m && matrix[i][j] > matrix[i+1][j]) 
        count3 = 1 + solve(matrix, i+1, j, m, n, vis);
    if(j+1 < n && matrix[i][j] > matrix[i][j+1])
        count4 = 1 + solve(matrix, i, j+1, m, n, vis);
    return vis[i][j] = max(max(count1, count2), max(count3, count4));
}
int longestIncreasingPath(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> vis(m, vector<int>(n, -1));
    int maxi = 1, res = 1;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(vis[i][j] == -1)
                res = max(solve(matrix, i, j, m, n, vis), res);
    
    return res;
}

// Longest Palindromic Subsequence
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};
    cout<<"Longest Increasing Path In a Matrix: "<<longestIncreasingPath(matrix)<<endl;
    cout<<"Longest Palindromic Subsequence: "<<longestPalindromeSubseq("bbbab")<<endl;
    return 0;
}
