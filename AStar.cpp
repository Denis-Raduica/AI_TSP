#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

struct Node {
    vector<int> path;
    int cost;
    int heuristic;
    int vertex;

    // Overload the < operator for the priority queue to sort by f(n) = g(n) + h(n)
    bool operator<(const Node& other) const {
        return (cost + heuristic) > (other.cost + other.heuristic);
    }
};

// Function to calculate the MST cost using Prim's algorithm
int calculateMSTCost(const vector<vector<int>>& graph, const set<int>& remainingNodes) {
    if (remainingNodes.empty()) return 0;

    vector<int> minEdge(graph.size(), numeric_limits<int>::max());
    vector<bool> inMST(graph.size(), false);
    int totalCost = 0;

    auto it = remainingNodes.begin();
    minEdge[*it] = 0;

    for (size_t i = 0; i < remainingNodes.size(); ++i) {
        int u = -1;

        for (int v : remainingNodes) {
            if (!inMST[v] && (u == -1 || minEdge[v] < minEdge[u])) {
                u = v;
            }
        }

        if (minEdge[u] == numeric_limits<int>::max()) {
            return numeric_limits<int>::max(); // MST not possible
        }

        inMST[u] = true;
        totalCost += minEdge[u];

        for (int v : remainingNodes) {
            if (!inMST[v] && graph[u][v] < minEdge[v]) {
                minEdge[v] = graph[u][v];
            }
        }
    }

    return totalCost;
}

// Heuristic function for A* (estimated cost to complete the tour)
int heuristic(const vector<vector<int>>& graph, const vector<int>& path, int startNode) {
    set<int> remainingNodes;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (find(path.begin(), path.end(), i) == path.end()) {
            remainingNodes.insert(i);
        }
    }
    return calculateMSTCost(graph, remainingNodes);
}

// Function to find the minimum cost using A* search
int tspAStarSearch(const vector<vector<int>>& graph, int startNode) {
    int n = graph.size();
    int minCost = numeric_limits<int>::max();

    // Priority queue for A* search
    priority_queue<Node> pq;

    // Initialize the priority queue with the start node
    pq.push({{startNode}, 0, heuristic(graph, {startNode}, startNode), startNode});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int lastNode = current.vertex;

        // If we have visited all nodes, check if we can return to the start node
        if (current.path.size() == n) {
            int returnCost = current.cost + graph[lastNode][startNode];
            if (returnCost < minCost) {
                minCost = returnCost;
            }
            continue;
        }

        // Try to visit all unvisited nodes
        for (int nextNode = 0; nextNode < n; ++nextNode) {
            if (find(current.path.begin(), current.path.end(), nextNode) == current.path.end()) {
                vector<int> newPath = current.path;
                newPath.push_back(nextNode);
                int newCost = current.cost + graph[lastNode][nextNode];
                int h = heuristic(graph, newPath, startNode);
                pq.push({newPath, newCost, h, nextNode});
            }
        }
    }

    return minCost;
}

int main() {
    int option;
    cout << "Choose an option:\n";
    cout << "1. Execute with hardcoded matrix.\n";
    cout << "0. Execute with input from keyboard.\n";
    cout << "Enter your choice: ";
    cin >> option;

    vector<vector<int>> graph;

    if (option == 1) {
        // Hardcoded matrix
        graph = {
            {0, 10, 15, 20},
            {10, 0, 35, 25},
            {15, 35, 0, 30},
            {20, 25, 30, 0}
        };
    } else if (option == 0) {
        // Read matrix from keyboard
        int size;
        cout << "Enter the size of the matrix: ";
        cin >> size;

        graph.resize(size, vector<int>(size));
        cout << "Enter the elements of the matrix:\n";
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cin >> graph[i][j];
            }
        }
    } else {
        cout << "Invalid option! Exiting...\n";
        return 1;
    }

    int startNode = 0;
    int minCost = tspAStarSearch(graph, startNode);

    cout << "Minimum cost to complete the TSP: " << minCost << endl;

    return 0;
}
