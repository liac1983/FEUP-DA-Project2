#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

/**
 * @brief Class representing a graph data structure.
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

    /* Setters */
    void setNumVertices(int numVertices);
    void setVisited(const std::vector<bool> &visited);
    void setGraphMatrix(const std::vector<std::vector<double>> &graphMatrix);

    /* Functions */
    /**
     * @brief Add an edge to the graph
     * @param src The source node of the edge.
     * @param dest The destination node of the edge.
     * @param cap The distance of the edge.
     */
    void addEdge(int src, int dest, double distance);
    /**
     * @brief Remove an edge from the graph.
     * @param src The source node of the edge.
     * @param dest The destination node of the edge.
     */
    void removePipe(int src, int dest);
    /**
     * @brief Get the distance value of an edge.
     * @param src The source node of the edge.
     * @param dest The destination node of the edge.
     * @return The distance value of the edge.
     */
    double getEdgeValue(int src, int dest);
    /**
     * @brief Load the graph with the contents from a file.
     * @param fileLocation The location of the file containing the graph data.
     */
    static void loadGraph(const std::string &fileLocation);

    void TSPUtil(int node, int count, double cost, double &minCost, std::vector<int> &path, std::vector<int> &optimalPath);
    std::pair<double, std::vector<int>> TSP();

private:

    int numVertices;
    std::vector<bool> visited;
    std::vector<std::vector<double>> graphMatrix;

};

#endif /* GRAPH_H */
