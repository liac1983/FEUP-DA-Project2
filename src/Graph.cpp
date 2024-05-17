#include "Graph.h"

/* Constructor */

Graph::Graph() {
    numVertices = 0;
    visited = std::vector<bool>(numVertices, false);
    graphMatrix = std::vector<std::vector<double>>(numVertices, std::vector<double>(numVertices, 0));
}

/* Getters */

int Graph::getNumVertices() const {
    return numVertices;
}

const std::vector<bool> &Graph::getVisited() const {
    return visited;
}

const std::vector<std::vector<double>> &Graph::getGraphMatrix() const {
    return graphMatrix;
}

/* Setters */

void Graph::setNumVertices(int newNumVertices) {
    Graph::numVertices = newNumVertices;
}

void Graph::setVisited(const std::vector<bool> &newVisitedList) {
    Graph::visited = newVisitedList;
}

void Graph::setGraphMatrix(const std::vector<std::vector<double>> &newGraphMatrix) {
    Graph::graphMatrix = newGraphMatrix;
}

/* Functions */

void Graph::addEdge(int src, int dest, double distance)
{
    graphMatrix[src][dest] = distance;
}

void Graph::removePipe(int src, int dest)
{
    graphMatrix[src][dest] = 0;
}

double Graph::getEdgeValue(int src, int dest)
{
    return graphMatrix[src][dest];
}
