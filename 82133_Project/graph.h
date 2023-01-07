#ifndef GRAPH
#define GRAPH

#include <vector>

struct Graph {
    int n; // Number of nodes
    int m; // Number of edges
    std::vector<int> adj[100]; // Adjacency list for each node
    // adj[i] is a list of node IDs that are neighbors of node i

    // Constructor
    Graph(int n, int m) : n(n), m(m) {}

    // Add an edge to the graph
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
};

#endif // !GRAPH
