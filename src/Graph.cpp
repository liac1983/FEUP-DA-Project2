#include "Graph.h"

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
