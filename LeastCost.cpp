#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> path;
    int cost;
    int vertex;

    // Overload the < operator for the priority queue to sort by cost in ascending order
    bool operator<(const Node& other) const {
        return cost > other.cost;
    }
};

// Function to find the minimum cost using Least-Cost Search (Uniform Cost Search)
int tspLeastCostSearch(const vector<vector<int>>& graph, int startNode) {
    int n = graph.size();
    int minCost = numeric_limits<int>::max();

    // Priority queue for least-cost search
    priority_queue<Node> pq;

    // Initialize the priority queue with the start node
    pq.push({{startNode}, 0, startNode});

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
                pq.push({newPath, newCost, nextNode});
            }
        }
    }

    return minCost;
}

int main() {
    // Example graph represented as a matrix
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int startNode = 0;
    int minCost = tspLeastCostSearch(graph, startNode);

    cout << "Minimum cost to complete the TSP: " << minCost << endl;

    return 0;
}
