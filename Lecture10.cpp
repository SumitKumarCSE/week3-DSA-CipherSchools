#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        makeSet();
    }

    void makeSet() {
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return;
        }

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    // Create a disjoint set with 5 elements
    DisjointSet ds(5);

    // Perform union operations
    ds.unionSets(0, 1);
    ds.unionSets(1, 2);
    ds.unionSets(3, 4);

    // Check if elements are connected
    cout << ds.isConnected(0, 2) << endl;   // Output: 1 (true)
    cout << ds.isConnected(1, 4) << endl;   // Output: 0 (false)

    // Perform another union operation
    ds.unionSets(0, 4);

    // Check if elements are connected
    cout << ds.isConnected(1, 4) << endl;   // Output: 1 (true)

    return 0;
}
