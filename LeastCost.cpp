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
    int minCost = tspLeastCostSearch(graph, startNode);

    cout << "Minimum cost to complete the TSP: " << minCost << endl;

    return 0;
}


