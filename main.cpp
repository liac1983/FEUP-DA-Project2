#include "src/Graph.h"
#include <vector>

int main()
{
    Graph graph;
    graph.loadGraph("../data/small/tourism.csv");

    int i = 0;

    std::pair<double, std::vector<int>> result = graph.TSP();

    return 0;
}
