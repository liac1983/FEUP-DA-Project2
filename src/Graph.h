#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

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
    /**
     * @brief Calculate the distance between two nodes using the Haversine formula.
     * @param i The first node id.
     * @param j The second node id.
     */
    void haversine(int i, int j);
    /**
     * @brief Load the graph with the contents from a file.
     * @param fileLocation The location of the file containing the graph data.
     */
    void loadGraphWithFile(const std::string &fileLocation);
    /**
     * @brief Load the node coordinates with the contents from a file.
     * @param fileLocation The location of the file containing the graph data.
     * @param numNodes The number of nodes in the graph.
     */
    void loadNodeCoordinates(const std::string &fileLocation, int numNodes);
    void loadGraphWithCoordinates();

    /* Graph Operations */
    void TSPUtil(int node, int count, double cost, double &minCost, std::vector<int> &path, std::vector<int> &optimalPath);
    std::pair<double, std::vector<int>> TSP();
    void exhaustiveTSPUtil(int node, int count, double cost, double minCost, std::vector<int> &path, std::vector<std::vector<int>> &optimalPath);
    std::vector<std::vector<int>> exhaustiveTSP(double minCost);

private:

    int numVertices;
    std::vector<bool> visited;
    std::vector<std::vector<double>> graphMatrix;
    std::unordered_map<int,std::pair<double,double>> nodeCoordinates;

};

#endif /* GRAPH_H */
