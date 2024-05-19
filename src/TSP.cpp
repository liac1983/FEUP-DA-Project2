#include "Graph.h"

#include <limits>

using namespace std;

void Graph::TSPUtil(int node, int count, double cost, double &minCost, vector<int> &path, vector<int> &optimalPath) {
    visited[node] = true;
    path.push_back(node);

    if (count == numVertices) {
        cost += graphMatrix[path.back()][path.front()];
        if (cost < minCost) {
            minCost = cost;
            optimalPath = path;
        }
    } else {
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && graphMatrix[node][i] != -1 && cost + graphMatrix[node][i] < minCost) {
                TSPUtil(i, count + 1, cost + graphMatrix[node][i], minCost, path, optimalPath);
            }
        }
    }

    visited[node] = false;
    path.pop_back();
}

pair<double, vector<int>> Graph::TSP() {
    vector<int> path;
    vector<int> optimalPath;
    double minCost = numeric_limits<double>::infinity();

    TSPUtil(0, 1, 0, minCost, path, optimalPath);
    optimalPath.push_back(0);

    return {minCost, optimalPath};
}

void Graph::exhaustiveTSPUtil(int node, int count, double cost, double minCost, vector<int> &path, vector<vector<int>> &optimalPath) {
    visited[node] = true;
    path.push_back(node);

    if (count == numVertices) {
        cost += graphMatrix[path.back()][path.front()];
        if (cost == minCost) {
            path.push_back(0);
            optimalPath.push_back(path);
            path.pop_back();
        }
    } else {
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && graphMatrix[node][i] != -1 && cost + graphMatrix[node][i] < minCost) {
                exhaustiveTSPUtil(i, count + 1, cost + graphMatrix[node][i], minCost, path, optimalPath);
            }
        }
    }

    visited[node] = false;
    path.pop_back();
}

vector<vector<int>> Graph::exhaustiveTSP(double minCost) {
    vector<int> currentPath;
    vector<vector<int>> optimalPathList;

    exhaustiveTSPUtil(0, 1, 0, minCost, currentPath, optimalPathList);

    return optimalPathList;
}

pair<double, vector<int>> Graph::triangularApproximation() {
    vector<int> tour;
    int currentNode = 0;
    double totalCost = 0.0;
    visited = vector<bool>(numVertices, false);

    tour.push_back(currentNode);
    visited[currentNode] = true;

    for (int count = 1; count < numVertices; count++) {
        double minDist = numeric_limits<double>::infinity();
        int nextNode = -1;

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                if (graphMatrix[currentNode][i] == -1) {
                    haversine(currentNode, i);
                }

                if (graphMatrix[currentNode][i] < minDist) {
                    minDist = graphMatrix[currentNode][i];
                    nextNode = i;
                }
            }
        }

        totalCost += minDist;
        currentNode = nextNode;
        visited[currentNode] = true;
        tour.push_back(currentNode);
    }

    totalCost += graphMatrix[currentNode][tour[0]];
    tour.push_back(tour[0]);

    return {totalCost, tour};
}
