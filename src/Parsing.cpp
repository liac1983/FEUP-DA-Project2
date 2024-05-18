#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

void filterString(string& input) {
    string temp;
    for (char c : input)
        if (isdigit(c) || c == '.' || c == '-')
            temp += c;
    input = temp;
}

void Graph::loadNodeCoordinates(const string &fileLocation) {
    fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"loadNodeCoordinates\" could not read the node coordinates data");

    string line;
    getline(file, line); // Skip first line

    int maxVertex = -1;
    string id, latitude, longitude;

    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream ss(line);

        getline(ss, id, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude);

        if (maxVertex < stoi(id)) maxVertex = stoi(id);

        nodeCoordinates[stoi(id)] = {stod(latitude), stod(longitude)};
    }

    numVertices = maxVertex + 1;
    visited = vector<bool>(numVertices, false);
    graphMatrix = vector<vector<double>>(numVertices, vector<double>(numVertices, 0));

    file.close();
}

void Graph::loadGraph(const string &fileLocation) {
    fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"loadGraph\" could not read the graph data");

    string line;
    getline(file, line); // Skip first line

    string src, dest, dist;

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

void Graph::loadExtraLargeGraph(const std::string &fileLocation) {
    fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"loadExtraLargeGraph\" could not read the graph data");

    string line;
    getline(file, line); // Skip first line

    string src, dest, dist;

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

    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (graphMatrix[i][j] == 0) {
                haversine(i, j);
            }
        }
    }

    file.close();
}

bool loadNodes(const std::string& filename, Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        int id;
        double latitude, longitude;
        std::string label;

        if (ss >> id >> latitude >> longitude >> label) {
            graph.addNode(id, latitude, longitude, label);
        }
    }

    file.close();
    return true;
}

bool loadEdges(const std::string& filename, Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        int source, target;
        double weight;

        if (ss >> source >> target >> weight) {
            graph.addEdge(source, target, weight);
        }
    }

    file.close();
    return true;
}