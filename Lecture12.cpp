#include<bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

public:
    Graph(int V) {
        this->V = V;
        this->adj = new list<int>[this->V];
    }

    void AddEdge(int u, int v) {
        adj[u].push_back(v);
        // if undirected
        adj[v].push_back(u);
    }

    // RemoveEdge()
    void DFS(int source, bool *visited, vector<int> &result) {
        visited[source] = true;
        result.push_back(source);

        for(auto itr = adj[source].begin(); itr != adj[source].end(); itr++) {
            if(!visited[*itr]) {
                DFS(*itr, visited, result);
            }
        }
    }
    vector<int> DFS() {
        vector<int> result;
        bool * visited = new bool[this->V];
        for(int i=0;i<this->V;i++) {
            visited[i] = false;
        }

        int count = 0;
        for(int i=0; i < this->V; i++) {
            if(!visited[i]) {
                count++;
                DFS(i, visited, result);
            }
        }
        cout<< count; // number of connected components
        return result;
    }

    vector<int> BFS() {
        vector<int> result;
        bool *visited = new bool[this->V];
        for(int i=0;i<this->V;i++) {
            visited[i] = false;
        }

        list<int> Q; // Doubly Ended Queue
        int source = 0;
        visited[source] = true;
        Q.push_back(source);
        while(!Q.empty()) {
            source = Q.front();
            Q.pop_front();
            result.push_back(source);

            for(auto itr = adj[source].begin(); itr != adj[source].end(); itr++) {
                if(!visited[*itr]) {
                    visited[*itr] = true;
                    Q.push_back(*itr);
                }
            }
        }
    }
};

int main() {

}