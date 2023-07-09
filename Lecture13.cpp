#include <bits/stdc++.h>
using namespace std;

// Detect cycle in an undirected graph
bool check_cycle(vector<int> adj[], int V, vector<bool> &vis, int u, int par)
{
    vis[u] = true;
    for (auto v : adj[u])
    {
        if (vis[v] and v != par)
            return true;
        if (vis[v])
            continue;

        if (check_cycle(adj, V, vis, v, u))
            return true;
        vis[v] = true;
    }

    return 0;
}
bool isCycle(int V, vector<int> adj[])
{
    vector<bool> vis(V, 0);
    for (int i = 0; i < V; i++)
    {
        if (vis[i])
            continue;
        if (check_cycle(adj, V, vis, i, -1))
        {
            return true;
        }
    }
    return 0;
}

// Detect cycle in a directed graph
bool cycle(int node, vector<bool> &vis, vector<bool> &dfsvis, vector<int> adj[])
{
    vis[node] = 1;
    dfsvis[node] = 1;
    for (auto it : adj[node])
    {
        if (!vis[it] && cycle(it, vis, dfsvis, adj))
        {
            return true;
        }
        else if (dfsvis[it] == 1)
            return true;
    }
    dfsvis[node] = 0;
    return false;
}
bool isCyclic(int V, vector<int> adj[])
{
    vector<bool> vis(V, 0);
    vector<bool> dfsvis(V, 0);
    for (int i = 0; i < V; i++)
    {
        if (!vis[i] && cycle(i, vis, dfsvis, adj))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int V = 5;
    vector<int> adj[] = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}};
    cout << "Is Graph have a cycle in undirected graph: " << isCycle(V, adj) << endl;
    V = 4;
    vector<int> adj[V] = {{1},{2},{3},{3}};
    cout << "Is Graph have a cycle in directed graph: " << isCyclic(V, adj) << endl;
}