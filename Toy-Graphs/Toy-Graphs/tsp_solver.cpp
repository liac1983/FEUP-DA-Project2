#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Define a struct to represent an edge between two points
struct Edge {
    int origin;
    int destination;
    double distance;
};

// Function to load dataset from a CSV file
vector<Edge> loadDataset(const string& filename) {
    vector<Edge> dataset;
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
        double distance;
        char comma;
        istringstream iss(line);
        iss >> origin >> comma >> destination >> comma >> distance;

        Edge edge;
        edge.origin = origin;
        edge.destination = destination;
        edge.distance = distance;
        dataset.push_back(edge);
    }

    file.close();
    return dataset;
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

int main() {
    vector<Edge> dataset;
    unordered_map<int, vector<pair<int, double>>> graph;

    int choice;
    do {
        cout << "===== TSP Solver Interface Menu =====" << endl;
        cout << "1. Load Dataset" << endl;
        cout << "2. View Dataset" << endl;
        cout << "3. Create Graph" << endl;
        cout << "4. Print Graph" << endl;
        cout << "5. Solve TSP (Exact Algorithm)" << endl;
        cout << "6. Solve TSP (Heuristic Algorithm)" << endl;
        cout << "7. Compare Solutions" << endl;
        cout << "8. Export Results" << endl;
        cout << "9. Exit" << endl;
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
                // Create graph from dataset
                graph = createGraph(dataset);
                break;
            case 4:
                // Print the created graph
                printGraph(graph);
                break;
            case 5:
                // Solve TSP using exact algorithm
                solveExactAlgorithm(dataset);
                break;
            case 6:
                // Solve TSP using heuristic algorithm
                solveHeuristicAlgorithm(dataset);
                break;
            case 7:
                // Compare solutions
                compareSolutions();
                break;
            case 8:
                // Export results
                exportResults();
                break;
            case 9:
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
