#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX; // Infinite capacity for edges

// Implementation of the Ford-Fulkerson algorithm using the Edmonds-Karp method
int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int V = graph.size(); // Number of vertices

    // Residual graph, initialized to the original capacities
    vector<vector<int>> residualGraph(V, vector<int>(V, 0));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            residualGraph[i][j] = graph[i][j];
        }
    }

    vector<int> parent(V); // Store the parent of each vertex in the augmenting path

    int maxFlow = 0; // Initialize the maximum flow

    while (true) {
        // Run a BFS to find an augmenting path in the residual graph
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(source);
        parent[source] = source;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < V; v++) {
                if (parent[v] == -1 && residualGraph[u][v] > 0) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        // If we reached the sink and found an augmenting path, compute the path flow
        if (parent[sink] != -1) {
            int pathFlow = INF;
            int current = sink;

            while (current != source) {
                int prev = parent[current];
                pathFlow = min(pathFlow, residualGraph[prev][current]);
                current = prev;
            }

            // Update the residual capacities and reverse edges along the augmenting path
            current = sink;

            while (current != source) {
                int prev = parent[current];
                residualGraph[prev][current] -= pathFlow;
                residualGraph[current][prev] += pathFlow;
                current = prev;
            }

            maxFlow += pathFlow;
        } else {
            // If there is no augmenting path, we have reached the maximum flow
            break;
        }
    }

    return maxFlow;
}

int main() {
    // Example usage:
    vector<vector<int>> graph = {
        {0, 10, 10, 0, 0, 0},
        {0, 0, 2, 4, 8, 0},
        {0, 0, 0, 0, 9, 0},
        {0, 0, 0, 0, 0, 10},
        {0, 0, 0, 0, 0, 10},
        {0, 0, 0, 0, 0, 0}
    };

    int source = 0;
    int sink = 5;
    int maxFlow = fordFulkerson(graph, source, sink);

    cout << "Max Flow: " << maxFlow << endl;

    return 0;
}
