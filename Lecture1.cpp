#include <bits/stdc++.h>
using namespace std;

// Cousins in a Binary Tree
bool isCousins(TreeNode* root, int x, int y) {
    if(root->val==x || root->val==y) return false;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        bool find1 = false, find2 = false;
        int size = q.size();
        while(size--) {
            TreeNode* curr = q.front();
            q.pop();
            if(curr->left!=NULL && curr->right!=NULL && ((curr->left->val == x && curr->right->val == y) || (curr->left->val == y && curr->right->val == x))) return false;
            if(curr->val == x) find1 = true;
            if(curr->val == y) find2 = true;
            if(curr->left != NULL) q.push(curr->left);
            if(curr->right != NULL) q.push(curr->right);
        }
        if(find1 && find2) return true;
        if(((find1 == true) && (find2 == false)) || ((find1 == false) && (find2 == true))) return false;
    }
    return false;
}

// All nodes at K distance
unordered_map<int, vector<int>> graph;
vector<int> answer;
unordered_set<int> visited;

void buildGraph(TreeNode* cur, TreeNode* parent) {
    if (cur != nullptr && parent != nullptr) {
        graph[cur->val].push_back(parent->val);
        graph[parent->val].push_back(cur->val);
    }
    if (cur->left != nullptr) {
        buildGraph(cur->left, cur);
    }
    if (cur->right != nullptr) {
        buildGraph(cur->right, cur);
    }
}

void dfs(int cur, int distance, int k) {
    if (distance == k) {
        answer.push_back(cur);
        return;
    }
    for (int neighbor : graph[cur]) {
        if (visited.find(neighbor) == visited.end()) {
            visited.insert(neighbor);
            dfs(neighbor, distance + 1, k);
        }
    }
}
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    buildGraph(root, nullptr);

    answer.clear();
    visited.clear();
    visited.insert(target->val);

    dfs(target->val, 0, k);
    return answer;
}

// Optimal binary tree
int sumOfFrequencies(const vector<int>& freq, int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += freq[i];
    }
    return sum;
}

int constructOBST(const vector<int>& keys, const vector<int>& freq) {
    int n = keys.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Base case: for a single key, the cost is equal to its frequency
    for (int i = 1; i <= n; i++) {
        dp[i][i] = freq[i - 1];
    }

    // Fill the table in a bottom-up manner
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            // Try making each key as the root and find the optimal cost
            for (int k = i; k <= j; k++) {
                int cost = dp[i][k - 1] + dp[k + 1][j] + sumOfFrequencies(freq, i - 1, j - 1);
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][n];
}

// Coin Change with infinite supply
int coinChange(vector<int>& coins, int n) {
    int dp[++n];
    dp[0] = 0;
    sort(begin(coins), end(coins));
    for (int i = 1; i < n; i++) {
        dp[i] = INT_MAX;
        for (int c: coins) {
            if (i - c < 0) break;
            if (dp[i - c] != INT_MAX) dp[i] = min(dp[i], 1 + dp[i - c]);
        }
    }
    return dp[--n] == INT_MAX ? -1 : dp[n];
}

int main() {
    vector<int> keys = {10, 20, 30, 40, 50};
    vector<int> freq = {4, 2, 6, 3, 1};

    int optimalCost = constructOBST(keys, freq);

    cout << "Optimal cost of constructing the binary search tree: " << optimalCost << endl;

    return 0;
}
