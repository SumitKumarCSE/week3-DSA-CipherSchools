#include <bits/stdc++.h>
using namespace std;

// Minimum Spanning Tree using Kruskal Algo
// Data structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Data structure to represent a disjoint set
struct DisjointSet {
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        
        // Initialize each node as a separate set with rank 0
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find the set to which a node belongs
    int find(int x) {
        if (parent[x] != x) {
            // Path compression
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    // Union of two sets
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootX] = rootY;
            rank[rootY]++;
        }
    }
};

// Function to compare edges based on their weights
bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

// Function to find the Minimum Spanning Tree using Kruskal's algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int numVertices) {
    // Sort the edges in non-decreasing order of their weights
    sort(edges.begin(), edges.end(), compareEdges);
    
    vector<Edge> mst;
    DisjointSet ds(numVertices);
    
    // Iterate through each edge in sorted order
    for (Edge edge : edges) {
        int srcParent = ds.find(edge.src);
        int destParent = ds.find(edge.dest);
        
        // Check if including the edge forms a cycle
        if (srcParent != destParent) {
            mst.push_back(edge);
            ds.unionSets(srcParent, destParent);
        }
    }
    
    return mst;
}

int main() {
    int numVertices = 4;
    vector<Edge> edges = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    
    vector<Edge> mst = kruskalMST(edges, numVertices);
    
    cout << "Minimum Spanning Tree Edges:\n";
    for (Edge edge : mst) {
        cout << edge.src << " -- " << edge.dest << " : " << edge.weight << endl;
    }
    return 0;
}
