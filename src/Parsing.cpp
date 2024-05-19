#include "Graph.h"

#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

void filterString(string& input) {
    string temp;
    for (char c : input)
        if (isdigit(c) || c == '.' || c == '-')
            temp += c;
    input = temp;
}

void Graph::haversine(int i, int j) {
    double lat1 = nodeCoordinates[i].first;
    double lon1 = nodeCoordinates[i].second;
    double lat2 = nodeCoordinates[j].first;
    double lon2 = nodeCoordinates[j].second;

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::sin(dLon / 2) * std::sin(dLon / 2) * std::cos(lat1) * std::cos(lat2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    graphMatrix[i][j] = 6371.0 * c;
    graphMatrix[j][i] = 6371.0 * c;
}

void Graph::loadGraphWithFile(const string &fileLocation) {
    fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"loadGraphWithFile\" could not read the graph data");

    visited = vector<bool>(numVertices, false);
    graphMatrix = vector<vector<double>>(numVertices, vector<double>(numVertices, -1));
    for (int i = 0; i < numVertices; i++) graphMatrix[i][i] = 0;

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

    file.close();
}

void Graph::loadNodeCoordinates(const string &fileLocation) {
    fstream file;
    file.open(fileLocation, ios::in);
    if (!file.is_open())
        throw runtime_error("ERROR - The function \"loadNodeCoordinates\" could not read the node coordinates data");

    visited = vector<bool>(numVertices, false);
    graphMatrix = vector<vector<double>>(numVertices, vector<double>(numVertices, -1));
    for (int i = 0; i < numVertices; i++) graphMatrix[i][i] = 0;

    string line;
    getline(file, line); // Skip first line

    string id, latitude, longitude;

    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream ss(line);

        getline(ss, id, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude);

        if (stoi(id) == numVertices) break;

        nodeCoordinates[stoi(id)] = {stod(latitude), stod(longitude)};
    }

    file.close();
}

void Graph::loadGraphWithCoordinates() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (graphMatrix[i][j] == 0) {
                haversine(i, j);
            }
        }
    }
}
