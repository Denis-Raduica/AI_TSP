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
    int minCost = tspBFS(graph, startNode);

    cout << "Minimum cost to complete the TSP: " << minCost << endl;

    return 0;
}
