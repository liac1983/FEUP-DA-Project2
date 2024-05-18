#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

struct Node {
    int id;
    double latitude;
    double longitude;
    std::string label;
};

struct Edge {
    int source;
    int target;
    double weight;
};

/**
 * @brief Class representing the graph's data structure.
 */
class Graph {
public:
    friend class Menu;

    /* Constructor */
    Graph();

    /* Getters */
    int getNumVertices() const;
    const std::vector<bool> &getVisited() const;
    const std::vector<std::vector<double>> &getGraphMatrix() const;
    const std::unordered_map<int, std::pair<double, double>> &getNodeCoordinates() const;

    /* Setters */
    void setNumVertices(int numVertices);
    void setVisited(const std::vector<bool> &visited);
    void setGraphMatrix(const std::vector<std::vector<double>> &graphMatrix);
    void setNodeCoordinates(const std::unordered_map<int, std::pair<double, double>> &nodeCoordinates);

    /* Parsing */

    void loadNodeCoordinates(const std::string &fileLocation);

    /**
     * @brief Load the graph with the contents from a file.
     * @param fileLocation The location of the file containing the graph data.
     */
    void loadGraph(const std::string &fileLocation);
    /**
     * @brief Load the extra large graphs with the contents from a file.
     * @param fileLocation The location of the file containing the graph data.
     */
    void loadExtraLargeGraph(const std::string &fileLocation);

    /* Graph Operations */
    void TSPUtil(int node, int count, double cost, double &minCost, std::vector<int> &path, std::vector<int> &optimalPath);
    std::pair<double, std::vector<int>> TSP();

    std::unordered_map<int, Node> nodes;
    std::unordered_map<int, std::vector<Edge>> adjacencyList;

    void addNode(int id, double latitude, double longitude, const std::string& label);
    void addEdge(int source, int target, double weight);
    void display() const;
    double tspApproximation(int start) const;
private:

    int numVertices;
    std::vector<bool> visited;
    std::vector<std::vector<double>> graphMatrix;
    std::unordered_map<int,std::pair<double,double>> nodeCoordinates;

};

double haversine(double lat1, double lon1, double lat2, double lon2);

#endif /* GRAPH_H */
