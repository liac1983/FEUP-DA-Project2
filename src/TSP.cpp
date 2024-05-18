#include "Graph.h"

#include <limits>
#include <complex>
#include <iostream>
#include <algorithm>

using namespace std;

void Graph::TSPUtil(int node, int count, double cost, double &minCost, vector<int> &path, vector<int> &optimalPath) {
    visited[node] = true;
    path.push_back(node);

    if (count == numVertices) {
        // If all nodes are visited, add the cost of the edge from the last node to the first node
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

const double EARTH_RADIUS = 6371.0; // Earth radius in kilometers

void Graph::addNode(int id, double latitude, double longitude, const std::string& label) {
    nodes[id] = {id, latitude, longitude, label};
}

void Graph::addEdge(int source, int target, double weight) {
    adjacencyList[source].push_back({source, target, weight});
}

void Graph::display() const {
    std::cout << "Nodes:" << std::endl;
    for (const auto& pair : nodes) {
        std::cout << pair.second.id << ": " << pair.second.label << " (" << pair.second.latitude << ", " << pair.second.longitude << ")" << std::endl;
    }
    std::cout << "Edges:" << std::endl;
    for (const auto& pair : adjacencyList) {
        for (const auto& edge : pair.second) {
            std::cout << edge.source << " -> " << edge.target << " [weight: " << edge.weight << "]" << std::endl;
        }
    }
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::sin(dLon / 2) * std::sin(dLon / 2) * std::cos(lat1) * std::cos(lat2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return EARTH_RADIUS * c;
}

double Graph::tspApproximation(int start) const {
    std::vector<int> tour;
    std::vector<bool> visited(nodes.size(), false);
    double totalDistance = 0.0;
    int currentNode = start;

    while (tour.size() < nodes.size()) {
        visited[currentNode] = true;
        tour.push_back(currentNode);

        double minDistance = std::numeric_limits<double>::infinity();
        int nextNode = -1;

        for (const auto& node : nodes) {
            if (!visited[node.first]) {
                double distance;
                auto it = adjacencyList.find(currentNode);
                if (it != adjacencyList.end()) {
                    auto edgeIt = std::find_if(it->second.begin(), it->second.end(),
                                               [&](const Edge& edge) { return edge.target == node.first; });
                    if (edgeIt != it->second.end()) {
                        distance = edgeIt->weight;
                    } else {
                        distance = haversine(nodes.at(currentNode).latitude, nodes.at(currentNode).longitude,
                                             node.second.latitude, node.second.longitude);
                    }
                } else {
                    distance = haversine(nodes.at(currentNode).latitude, nodes.at(currentNode).longitude,
                                         node.second.latitude, node.second.longitude);
                }

                if (distance < minDistance) {
                    minDistance = distance;
                    nextNode = node.first;
                }
            }
        }

        if (nextNode != -1) {
            totalDistance += minDistance;
            currentNode = nextNode;
        } else {
            break;
        }
    }

    if (tour.size() == nodes.size()) {
        totalDistance += haversine(nodes.at(currentNode).latitude, nodes.at(currentNode).longitude,
                                   nodes.at(start).latitude, nodes.at(start).longitude);
    }

    return totalDistance;
}
