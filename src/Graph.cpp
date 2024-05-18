#include "Graph.h"

#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

/* Constructor */

Graph::Graph() {
    numVertices = 0;
    visited = vector<bool>(numVertices, false);
    graphMatrix = vector<vector<double>>(numVertices, vector<double>(numVertices, 0));
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

void filterString(string& input) {
    string temp;
    for (char c : input)
        if (isdigit(c) || c == '.')
            temp += c;
    input = temp;
}

void Graph::loadGraph(const string &fileLocation) {
    fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"loadGraph\" could not read the graph data");

    string line;
    getline(file, line); // Skip first line

    int maxVertex = -1;
    string src, dest, dist;

    // First pass to find the maximum vertex number
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream ss(line);

        getline(ss, src, ',');
        getline(ss, dest, ',');
        getline(ss, dist);

        if (src.empty() || dest.empty()) continue;

        maxVertex = max(maxVertex, max(stoi(src), stoi(dest)));
    }

    numVertices = maxVertex + 1;
    visited = vector<bool>(numVertices, false);
    graphMatrix = vector<vector<double>>(numVertices, vector<double>(numVertices, 0));
    file.close();

    file.open(fileLocation, ios::in);
    getline(file, line); // Skip first line

    // Second pass to fill the graphMatrix
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream ss(line);

        getline(ss, src, ',');
        getline(ss, dest, ',');
        getline(ss, dist);

        filterString(dist);

        if (src.empty() || dest.empty()) continue;

        graphMatrix[stoi(src)][stoi(dest)] = stof(dist);
        graphMatrix[stoi(dest)][stoi(src)] = stof(dist);
    }

    file.close();
}

void Graph::TSPUtil(int node, int count, double cost, double &minCost, vector<int> &path, vector<int> &optimalPath) {
    visited[node] = true;
    path.push_back(node);

    if (count == numVertices) {
        // If all nodes are visited, add the cost of the edge from the last node to the first node
        cost += getEdgeValue(path.back(), path.front());
        if (cost < minCost) {
            minCost = cost;
            optimalPath = path;
        }
    } else {
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && cost + getEdgeValue(node, i) < minCost) {
                TSPUtil(i, count + 1, cost + getEdgeValue(node, i), minCost, path, optimalPath);
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

