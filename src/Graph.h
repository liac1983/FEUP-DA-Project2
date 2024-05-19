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
     * @complexity O(1)
     */
    void haversine(int i, int j);
    /**
     * @brief Load the graph with the contents from a file.
     * @param fileLocation The location of the file containing the graph data.
     * @complexity O(E), where E is the number of edges.
     */
    void loadGraphWithFile(const std::string &fileLocation);
    /**
     * @brief Load the node coordinates with the contents from a file.
     * @param fileLocation The location of the file containing the graph data.
     * @param numNodes The number of nodes in the graph.
     * @complexity O(V), where V is the number of vertices.
     */
    void loadNodeCoordinates(const std::string &fileLocation, int numNodes);
    /**
     * @brief Calculate distances between nodes based on coordinates and populate the adjacency matrix.
     * @complexity O(V^2), where V is the number of vertices.
     */
    void loadGraphWithCoordinates();

    /* Graph Operations */
    void TSPUtil(int node, int count, double cost, double &minCost, std::vector<int> &path, std::vector<int> &optimalPath);
    std::pair<double, std::vector<int>> TSP();
    void exhaustiveTSPUtil(int node, int count, double cost, double minCost, std::vector<int> &path, std::vector<std::vector<int>> &optimalPath);
    std::vector<std::vector<int>> exhaustiveTSP(double minCost);


    /* Triangular Approximation Heuristic */
    /**
     * @brief Solve the TSP using the Triangular Approximation Heuristic.
     * @return std::pair<double, std::vector<int>> The cost and the approximate path.
     * @complexity O(V^2), where V is the number of vertices.
     */
    std::pair<double, std::vector<int>> triangularApproximation();
private:

    int numVertices;
    std::vector<bool> visited;
    std::vector<std::vector<double>> graphMatrix;
    std::unordered_map<int,std::pair<double,double>> nodeCoordinates;

};

#endif /* GRAPH_H */
