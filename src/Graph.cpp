#include "Graph.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

/* Constructor */

Graph::Graph() {
    numVertices = 0;
    visited = vector<bool>();
    graphMatrix = vector<vector<double>>();
    nodeCoordinates = unordered_map<int, pair<double, double>>();
}

/* Getters */

int Graph::getNumVertices() const {
    return numVertices;
}

const vector<bool> &Graph::getVisited() const {
    return visited;
}

const vector<vector<double>> &Graph::getGraphMatrix() const {
    return graphMatrix;
}

const unordered_map<int, pair<double, double>> &Graph::getNodeCoordinates() const {
    return nodeCoordinates;
}

/* Setters */

void Graph::setNumVertices(int newNumVertices) {
    Graph::numVertices = newNumVertices;
}

void Graph::setVisited(const vector<bool> &newVisitedList) {
    Graph::visited = newVisitedList;
}

void Graph::setGraphMatrix(const vector<vector<double>> &newGraphMatrix) {
    Graph::graphMatrix = newGraphMatrix;
}

void Graph::setNodeCoordinates(const unordered_map<int, pair<double, double>> &newNodeCoordinates) {
    Graph::nodeCoordinates = newNodeCoordinates;
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
