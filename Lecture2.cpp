#include <bits/stdc++.h>
using namespace std;

// Subset sum problem: Divide array into two subsets such that sum of both the subsets is equal
int solve(int* arr, int N, int sum, int i, vector<vector<int>>& dp) {
    if(sum == 0) return 1;
    if(i == N) return 0;
    if(dp[i][sum]!=-1) return dp[i][sum];
    return dp[i][sum] = max(solve(arr, N, sum-arr[i], i+1, dp), solve(arr, N, sum, i + 1, dp));
}
int equalPartition(int N, int arr[]) {
    int sum = 0, res=0;
    for(int i = 0; i<N;i++){
        sum+=arr[i];
    }
    if(sum % 2 != 0) return 0;
    vector<vector<int>> dp(N+1, vector<int>(sum+1, -1));
    return solve(arr, N, sum/2, 0, dp);
}

// Rod Cutting
int cutRod(int price[], int n) {
    vector<int> dp(n+1,0);
    for(int i=1;i<=n;i++) {
        dp[i] = price[i-1];
        for(int j = 1; j <= i;j++) {
            dp[i] = max(dp[i], dp[j] + dp[i - j]);
        }
    }
    return dp[n];
}

// Jump Game
bool canJump(vector<int>& nums) {
    if(nums.size()==1) return true;
    int max=nums[0];
    for(auto it:nums) {
        if(max==0) {
            return false;
        }
        if(it>=max) {
            max=it;
        } else {
            max--;
        }
    }
    return true;
}

// Longest Increasing Subsequence
int lengthOfLIS(vector<int>& arr) {
    vector<int> temp;
    temp.push_back(arr[0]);
    int len = 1;
    for(int i=1; i<arr.size(); i++){
        if(arr[i]>temp.back()){
           temp.push_back(arr[i]);
           len++;
        } else {
            int ind = lower_bound(temp.begin(),temp.end(),arr[i]) - temp.begin();
            temp[ind] = arr[i];
        }
    }
    return len;
}

int main() {
    int arr[4] = {1,5,5,11};
    int N = 4;
    cout<<"Is Subset Sum Possible: ";
    if(equalPartition(N, arr)) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    
    int price[8] = {1, 5, 8, 9, 10, 17, 17, 20};
    int n = 8;
    cout<<"Cut Rod: "<<cutRod(price, n)<<endl;

    return 0;
}
