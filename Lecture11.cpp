#include <bits/stdc++.h>
using namespace std;

// Fibonacci Series
int fib1(int n, vector<int> &dp) {
    if (n <= 1)
        return n;
    if (dp[n] != -1)
        return dp[n];
    return dp[n] = fib1(n - 1, dp) + fib1(n - 2, dp);
}
int fib(int n) {
    vector<int> dp(n + 1, -1);
    return fib1(n, dp);
}

// nCr
int nCr(int n, int r) {
    if (r > n) {
        return 0;
    }
    if (n == r || r == 0) {
        return 1;
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    int count = 1;
    long long int mod = 1000000007;
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            if (i == j) {
                dp[i][j] = 1;
                break;
            }
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod;
            if (i == n && j == r)
                return dp[i][j];
        }
    }
    return -1;
}

int main() {
    cout<<"Fibonacci No. at position 8: " << fib(8) << endl;
    cout<<"8C7: "<<nCr(8,7)<<endl;
    return 0;
}