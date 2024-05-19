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
     * @brief Load the node coordinates map with the contents from a file.
     * @param fileLocation The location of the file containing the graph data.
     * @complexity O(V), where V is the number of vertices.
     */
    void loadNodeCoordinates(const std::string &fileLocation);
    /**
     * @brief Calculate distances between nodes based on coordinates and populate the adjacency matrix.
     * @complexity O(V^2), where V is the number of vertices.
     */
    void loadGraphWithCoordinates();

    /* Backtracking Algorithm */
    /**
     * @brief Utility function for the TSP function.
     *
     * This function is responsible for exploring all possible paths in the graph and finding the optimal solution.
     * When the function reaches a leaf node, it checks if the cost of the path is less than the minimum cost found so far.
     * If it is, the function updates the minimum cost and the optimal path.
     *
     * @param node The current node.
     * @param count The number of nodes visited so far.
     * @param cost The cost of the path so far.
     * @param minCost The minimum cost found so far.
     * @param path The path taken so far.
     * @param optimalPath The optimal path found so far.
     *
     * @complexity O(n!), where n is the number of vertices.
     */
    void TSPUtil(int node, int count, double cost, double &minCost, std::vector<int> &path, std::vector<int> &optimalPath);
    /**
     * @brief Solves the Travelling Salesman Problem (TSP) using a backtracking approach.
     *
     * @return std::pair<double, std::vector<int>> The cost and the path of the optimal solution.
     */
    std::pair<double, std::vector<int>> TSP();

    /* Exhaustive Backtracking Algorithm */

    /**
     * @brief Utility function for the exhaustiveTSP function.
     *
     * This function is responsible for exploring all possible paths in the graph and finding the optimal solution.
     * When the function reaches a leaf node, it checks if the cost of the path is equal to the minimum cost found so far.
     * If it is, the function adds the path to the optimal paths vector.
     *
     * @param node The current node.
     * @param count The number of nodes visited so far.
     * @param cost The cost of the path so far.
     * @param minCost The minimum cost found so far.
     * @param path The path taken so far.
     * @param optimalPath The optimal paths found so far.
     *
     * @complexity O(n!), where n is the number of vertices.
     */
    void exhaustiveTSPUtil(int node, int count, double cost, double minCost, std::vector<int> &path, std::vector<std::vector<int>> &optimalPath);
    /**
     * @brief Solves the Travelling Salesman Problem (TSP) using an exhaustive backtracking approach.
     *
     * @param minCost The minimum cost found so far.
     * @return std::vector<std::vector<int>> The optimal paths found.
     */
    std::vector<std::vector<int>> exhaustiveTSP(double minCost);

    /* Triangular Approximation Heuristic */
    /**
     * @brief Solve the TSP using the Triangular Approximation Heuristic.
     *
     * @return std::pair<double, std::vector<int>> The cost and the approximate path.
     *
     * @complexity O(V^2), where V is the number of vertices.
     */
    std::pair<double, std::vector<int>> triangularApproximation();

private:

    int numVertices; /**< Number of vertices. */
    std::vector<bool> visited; /**< Vector of visited nodes. */
    std::vector<std::vector<double>> graphMatrix; /**< Adjacency matrix. */
    std::unordered_map<int,std::pair<double,double>> nodeCoordinates; /**< Map of node geographical coordinates. */

};

#endif /* GRAPH_H */
