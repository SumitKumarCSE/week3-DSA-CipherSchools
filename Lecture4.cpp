#include<bits/stdc++.h>
using namespace std;

// 0-1 Knapsack
int solve(int W, int *wt, int *val, int n, int i, vector<vector<int>>& dp) {
    if(i == 0){
        if(wt[0] <= W) return val[0];
        return 0;
    }
    if(dp[i][W]!= -1) return dp[i][W];
    int notPick = solve(W, wt, val, n, i-1, dp);
    int pick = INT_MIN;
    if(wt[i] <= W){
        pick = val[i] + solve(W - wt[i], wt, val, n, i-1, dp);
    }
    return dp[i][W] = max(pick,notPick);
}
int knapSack(int W, int wt[], int val[], int n) {  
    vector<vector<int>> dp(n,vector<int> (W+1, -1));
    return solve(W, wt, val, n, n-1, dp);
}

// Count total number of palicdromic substrings
int countSubstrings(string s) {
    int count = 0;
    int n = s.size();
        
    for (int i = 0; i < n; i++) {
        int left = i;
        int right = i;
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
            
        left = i;
        right = i + 1;
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    }
    return count;
}
    
int main() {
    int N = 4, W = 8;
    int values[] = {2,3,1,4};
    int weight[] = {3,4,6,5};
    cout<<"Knapsack: "<<knapSack(W, weight, values, N)<<endl;
    cout<<"Number of Palindromic Substrings: "<<countSubstring("aaabbbccc")<<endl;
    return 0;
}
