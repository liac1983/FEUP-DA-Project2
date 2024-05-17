#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

const double INF = 1e9;

// Define a struct to represent an edge between two points
struct Edge {
    int origin;
    int destination;
    double distance;
    bool visited; // Add visited member

};

// Define a struct to represent a vertex
struct Vertex {
    int id;
    vector<Edge> edges;
};

// Function to load dataset from a CSV file
vector<Edge> loadDataset(const string& filename) {
    vector<Edge> dataset; // Correct return type to vector<Edge>
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return dataset;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines
        if (line[0] == '#') continue; // Skip comment lines

        int origin, destination;
        double distance; // Change to double
        char comma;
        istringstream iss(line);
        iss >> origin >> comma >> destination >> comma >> distance;

        Edge edge1 = {origin, destination, distance, false}; // Initialize visited as false
        Edge edge2 = {destination, origin, distance, false}; // Add reverse edge
        dataset.push_back(edge1);
        dataset.push_back(edge2); // Push both edges into dataset
    }

    file.close();
    return dataset; // Return the correct type
}

// Function to display dataset
void viewDataset(const vector<Edge>& dataset) {
    cout << "===== Dataset =====" << endl;
    for (const auto& edge : dataset) {
        cout << edge.origin << " -> " << edge.destination << " : " << edge.distance << endl;
    }
    cout << "===================" << endl;
}

// Function to create a graph from the dataset
unordered_map<int, vector<pair<int, double>>> createGraph(const vector<Edge>& dataset) {
    unordered_map<int, vector<pair<int, double>>> graph;
    for (const auto& edge : dataset) {
        graph[edge.origin].push_back({edge.destination, edge.distance});
        // Assuming an undirected graph, add the reverse edge as well
        graph[edge.destination].push_back({edge.origin, edge.distance});
    }
    return graph;
}

// Function to print the graph
void printGraph(const unordered_map<int, vector<pair<int, double>>>& graph) {
    cout << "===== Graph =====" << endl;
    for (const auto& entry : graph) {
        cout << entry.first << " -> ";
        for (const auto& neighbor : entry.second) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
    cout << "==================" << endl;
}

// Function to solve TSP using exact algorithm
void solveExactAlgorithm(const vector<Edge>& dataset) {
    // Implement exact algorithm (e.g., backtracking) here
    cout << "Exact algorithm solution" << endl;
}

// Function to solve TSP using heuristic algorithm
void solveHeuristicAlgorithm(const vector<Edge>& dataset) {
    // Implement heuristic algorithm (e.g., nearest neighbor) here
    cout << "Heuristic algorithm solution" << endl;
}

// Function to compare solutions
void compareSolutions() {
    // Implement comparison logic here
    cout << "Comparing solutions" << endl;
}

// Function to export results
void exportResults() {
    // Implement export logic here
    cout << "Exporting results" << endl;
}

// Function to solve TSP using backtracking algorithm
void tspBacktrack(vector<Edge>& graph, int u, int count, double cost, vector<int>& path, vector<int>& bestPath, double& bestCost) {
    if (count == graph.size() && u == 0) {
        if (cost < bestCost) {
            bestCost = cost;
            bestPath = path;
        }
        return;
    }

    for (size_t i = 0; i < graph.size(); ++i) {
        if (graph[i].origin == u && !graph[i].visited) {
            graph[i].visited = true;
            path.push_back(graph[i].destination);
            tspBacktrack(graph, graph[i].destination, count + 1, cost + graph[i].distance, path, bestPath, bestCost);
            graph[i].visited = false;
            path.pop_back();
        }
    }
}

// Function to solve TSP using backtracking algorithm
void solveTSPBacktrack(vector<Vertex>& graph) {
    vector<int> path;
    vector<int> bestPath;
    double bestCost = INF;
    path.push_back(0); // Start from node 0
    // Call tspBacktrack with appropriate arguments
    tspBacktrack(graph[0].edges, 0, 1, 0.0, path, bestPath, bestCost);

    // Output the best path and its cost
    cout << "Best Path: ";
    for (int node : bestPath) {
        cout << node << " ";
    }
    cout << "0" << endl; // Return to the starting node
    cout << "Cost: " << bestCost << endl;
}


// Função para calcular a distância entre dois pontos geográficos usando a fórmula de distância Haversine
double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    // Raio da Terra em quilômetros
    const double R = 6371.0;

    // Converter graus para radianos
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // Calcular a distância entre os pontos usando a fórmula de Haversine
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;
}

// Função para resolver TSP usando o algoritmo de aproximação triangular
void solveTriangularApproximation(const vector<Vertex>& graph) {
    // Inicializar variáveis para armazenar o custo total e o caminho percorrido
    double totalCost = 0.0;
    vector<int> path;

    // Iniciar a partir do nó 0
    int currentVertex = 0;
    int startingVertex = 0;
    path.push_back(startingVertex);

    // Marcar todos os nós como não visitados
    vector<bool> visited(graph.size(), false);
    visited[startingVertex] = true;

    // Continuar até todos os nós serem visitados
    while (path.size() < graph.size()) {
        double minDistance = INF;
        int nextVertex = -1;

        // Percorrer todas as arestas do nó atual
        for (const auto& edge : graph[currentVertex].edges) {
            // Se o destino da aresta não foi visitado e a distância é menor que a mínima até agora
            if (!visited[edge.destination] && edge.distance < minDistance) {
                minDistance = edge.distance;
                nextVertex = edge.destination;
            }
        }

        // Adicionar o próximo nó ao caminho e atualizar o custo total
        path.push_back(nextVertex);
        totalCost += minDistance;

        // Marcar o próximo nó como visitado
        visited[nextVertex] = true;

        // Atualizar o nó atual para o próximo nó
        currentVertex = nextVertex;
    }

    // Adicionar o nó inicial novamente para formar um ciclo
    path.push_back(startingVertex);

    // Calcular a distância da última aresta para formar um ciclo completo
    double lastEdgeDistance = 0.0;
    for (const auto& edge : graph[currentVertex].edges) {
        if (edge.destination == startingVertex) {
            lastEdgeDistance = edge.distance;
            break;
        }
    }

    // Adicionar a distância da última aresta ao custo total
    totalCost += lastEdgeDistance;

    // Exibir o caminho percorrido e o custo total
    cout << "Best Path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << startingVertex << endl; // Retornar ao nó inicial para formar um ciclo
    cout << "Cost: " << totalCost << endl;
}



int main() {
    vector<Edge> dataset;
    vector<Vertex> graph;

    int choice;
    do {
        cout << "===== TSP Solver Interface Menu =====" << endl;
        cout << "1. Load Dataset" << endl;
        cout << "2. View Dataset" << endl;
        cout << "3. Solve TSP (Backtracking Algorithm)" << endl;
        cout << "4. Solve TSP (TriangularApproximation)" << endl;
        cout << "5. Solve TSP (Heuristic Algorithm)" << endl;
        cout << "6. Compare Solutions" << endl;
        cout << "7. Export Results" << endl;
        cout << "8. Exit" << endl;
        cout << "======================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Load dataset from file
                dataset = loadDataset("shipping.csv");
                break;
            case 2:
                // View loaded dataset
                viewDataset(dataset);
                break;
            case 3:
                // Solve TSP using exact algorithm
                solveTSPBacktrack(graph);
                // Exibir resultados
                cout << "\nPressione qualquer tecla e Enter para continuar...";
                cin.ignore(); // Ignorar a entrada anterior
                cin.get();    // Esperar por uma nova entrada
                break;
            case 4:
                // Resolver TSP usando o algoritmo de aproximação triangular
                solveTriangularApproximation(graph);
                // Exibir resultados
                cout << "\nPressione qualquer tecla e Enter para continuar...";
                cin.ignore(); // Ignorar a entrada anterior
                cin.get();    // Esperar por uma nova entrada
                break;
            case 5:
                // Solve TSP using heuristic algorithm
                solveHeuristicAlgorithm(dataset);
                break;
            case 6:
                // Compare solutions
                compareSolutions();
                break;
            case 7:
                // Export results
                exportResults();
                break;
            case 8:
                // Exit the program
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
                break;
        }
    } while (choice != 9);

    return 0;
}
