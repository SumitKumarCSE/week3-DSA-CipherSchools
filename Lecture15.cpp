#include<bits/stdc++.h>
using namespace std;

// Function for topological sort using DFS
void dfsTopologicalSort(vector<vector<int>>& adjList1, vector<bool>& visited, stack<int>& stk, int v) {
    visited[v] = true;
    
    for (int u : adjList1[v]) {
        if (!visited[u]) {
            dfsTopologicalSort(adjList1, visited, stk, u);
        }
    }
    
    stk.push(v);
}

// Topological sort function
vector<int> topologicalSort(vector<vector<int>>& adjList1) {
    int n = adjList1.size();
    vector<bool> visited(n, false);
    stack<int> stk;
    
    // Perform topological sort
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsTopologicalSort(adjList1, visited, stk, i);
        }
    }
    
    // Reverse the order of nodes in the stack to get the topological order
    vector<int> topologicalOrder;
    while (!stk.empty()) {
        topologicalOrder.push_back(stk.top());
        stk.pop();
    }
    
    return topologicalOrder;
}




// Dijstra Algo
// Structure to represent a node in the graph
struct Node {
    int vertex;
    int distance;
    
    Node(int v, int d) : vertex(v), distance(d) {}
};

// Comparison function for the priority queue
struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.distance > b.distance;
    }
};

// Dijkstra's algorithm function
vector<int> dijkstra(vector<vector<pair<int, int>>>& adjList2, int source) {
    int n = adjList2.size();
    vector<int> distances(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    priority_queue<Node, vector<Node>, Compare> pq;
    
    distances[source] = 0;
    pq.push(Node(source, 0));
    
    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();
        
        if (visited[u]) {
            continue;
        }
        
        visited[u] = true;
        
        for (auto neighbor : adjList2[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push(Node(v, distances[v]));
            }
        }
    }
    
    return distances;
}


// Floyd Warshall
// Function to initialize the distance matrix
void initializeDistances(vector<vector<int>>& dist, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = numeric_limits<int>::max();
            }
        }
    }
}

// Floyd-Warshall algorithm function
void floydWarshall(vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist(n, vector<int>(n));
    initializeDistances(dist, n);
    
    // Initialize the distance matrix with the graph's edge weights
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != 0) {
                dist[i][j] = graph[i][j];
            }
        }
    }
    
    // Compute shortest distances for all pairs of vertices
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != numeric_limits<int>::max() && dist[k][j] != numeric_limits<int>::max()
                    && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    // Print the shortest distances
    cout << "Shortest distances between all pairs of vertices:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == numeric_limits<int>::max()) {
                cout << "INF\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
}


// Alien Dictionary
string alienOrder(vector<string>& words) {
    // Step 1: Create adjacency list and in-degree map
    unordered_map<char, unordered_set<char>> adjList;
    unordered_map<char, int> inDegree;
    
    for (string word : words) {
        for (char c : word) {
            adjList[c] = {};
            inDegree[c] = 0;
        }
    }
    
    // Step 2: Build the adjacency list and in-degree map
    for (int i = 0; i < words.size() - 1; i++) {
        string currWord = words[i];
        string nextWord = words[i + 1];
        
        int minLength = min(currWord.length(), nextWord.length());
        for (int j = 0; j < minLength; j++) {
            char currChar = currWord[j];
            char nextChar = nextWord[j];
            
            if (currChar != nextChar) {
                if (!adjList[currChar].count(nextChar)) {
                    adjList[currChar].insert(nextChar);
                    inDegree[nextChar]++;
                }
                break;
            }
        }
    }
    
    // Step 3: Perform topological sorting using Kahn's algorithm
    string result = "";
    queue<char> q;
    
    for (auto entry : inDegree) {
        if (entry.second == 0) {
            q.push(entry.first);
        }
    }
    
    while (!q.empty()) {
        char currChar = q.front();
        q.pop();
        
        result += currChar;
        
        for (char neighbor : adjList[currChar]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    // Step 4: Check for cycle (invalid dictionary)
    if (result.length() != inDegree.size()) {
        return "";
    }
    
    return result;
}

int main() {
    int n = 6;
    vector<vector<int>> adjList1(n);
    
    // Add edges to the graph
    adjList1[0].push_back(1);
    adjList1[0].push_back(2);
    adjList1[1].push_back(3);
    adjList1[2].push_back(3);
    adjList1[2].push_back(4);
    adjList1[3].push_back(5);
    adjList1[4].push_back(5);
    
    // Perform topological sort
    vector<int> topologicalOrder = topologicalSort(adjList1);
    
    // Print the topological order
    cout << "Topological order: ";
    for (int vertex : topologicalOrder) {
        cout << vertex << " ";
    }
    cout << endl;

    vector<vector<pair<int, int>>> adjList2(n);
    
    // Add edges to the graph
    adjList2[0].push_back(make_pair(1, 5));
    adjList2[0].push_back(make_pair(2, 3));
    adjList2[1].push_back(make_pair(3, 2));
    adjList2[2].push_back(make_pair(1, 1));
    adjList2[2].push_back(make_pair(3, 7));
    adjList2[3].push_back(make_pair(4, 2));
    adjList2[4].push_back(make_pair(5, 3));
    
    int source = 0;
    
    // Perform Dijkstra's algorithm
    vector<int> distances = dijkstra(adjList2, source);
    
    // Print the distances from the source vertex to all other vertices
    cout << "Shortest distances from vertex " << source << ":" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }

    n = 4;
    vector<vector<int>> graph = {
        {0, 5, numeric_limits<int>::max(), 10},
        {numeric_limits<int>::max(), 0, 3, numeric_limits<int>::max()},
        {numeric_limits<int>::max(), numeric_limits<int>::max(), 0, 1},
        {numeric_limits<int>::max(), numeric_limits<int>::max(), numeric_limits<int>::max(), 0}
    };
    
    // Perform Floyd-Warshall algorithm
    cout<<"Floyd Warshall:"<<endl;
    floydWarshall(graph, n);
    
    vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
    string order = alienOrder(words);
    cout << "Order of characters in the alien dictionary: " << order << endl;

    return 0;
}
