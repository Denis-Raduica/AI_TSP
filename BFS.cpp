#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include<algorithm>

using namespace std;

// Function to find the minimum cost using BFS
int tspBFS(const vector<vector<int>>& graph, int startNode) {
    int n = graph.size();
    int minCost = numeric_limits<int>::max();

    // BFS queue stores pairs of (current path, current cost)
    queue<pair<vector<int>, int>> bfsQueue;

    // Initialize the BFS queue with the start node
    bfsQueue.push({{startNode}, 0});

    while (!bfsQueue.empty()) {
        auto [currentPath, currentCost] = bfsQueue.front();
        bfsQueue.pop();

        int lastNode = currentPath.back();

        // If we have visited all nodes, check if we can return to the start node
        if (currentPath.size() == n) {
            int returnCost = currentCost + graph[lastNode][startNode];
            if (returnCost < minCost) {
                minCost = returnCost;
            }
            continue;
        }

        // Try to visit all unvisited nodes
        for (int nextNode = 0; nextNode < n; ++nextNode) {
            if (find(currentPath.begin(), currentPath.end(), nextNode) == currentPath.end()) {
                vector<int> newPath = currentPath;
                newPath.push_back(nextNode);
                int newCost = currentCost + graph[lastNode][nextNode];
                bfsQueue.push({newPath, newCost});
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
    int minCost = tspBFS(graph, startNode);

    cout << "Minimum cost to complete the TSP: " << minCost << endl;

    return 0;
}
