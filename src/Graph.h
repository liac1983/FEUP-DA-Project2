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

private:

    int numVertices;
    std::vector<bool> visited;
    std::vector<std::vector<double>> graphMatrix;
    std::unordered_map<int,std::pair<double,double>> nodeCoordinates;

};

#endif /* GRAPH_H */
