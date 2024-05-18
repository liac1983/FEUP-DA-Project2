#include "Menu.h"
#include "Graph.h"
#include <limits>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// -------------------- Constructor -------------------- //

Menu::Menu() {
    setUpMenu();
}

// ----------------------- SetUp ----------------------- //

void Menu::setUpMenu() {
    int input;

    system("clear || cls");
    cout << endl
         << "   Please select the data set:" << endl << endl
         << "     1. Small Data Set" << endl << endl
         << "     2. Large Data Set" << endl << endl
         << "     3. Extra Large Data Set" << endl << endl
         << "   Select your option: ";

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option: ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 1:
                setUpSmall();
                return;
            case 2:
                setUpLarge();
                return;
            case 3:
                setUpExtraLarge();
                return;
            default:
                cout << endl << "   Please select a valid option: ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option: ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::setUpSmall() {
    int input;

    system("clear || cls");
    cout << endl
         << "   Please select the data set:" << endl << endl
         << "     1. Tourism" << endl << endl
         << "     2. Shipping" << endl << endl
         << "     3. Stadiums" << endl << endl
         << "   Select your option: ";

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option: ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 1:
                graph.loadGraph("../data/small/tourism.csv");
                mainMenu(true);
                return;
            case 2:
                graph.loadGraph("../data/small/shipping.csv");
                mainMenu(true);
                return;
            case 3:
                graph.loadGraph("../data/small/stadiums.csv");
                mainMenu(true);
                return;
            default:
                cout << endl << "   Please select a valid option: ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option: ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::setUpLarge() {

}

void Menu::setUpExtraLarge() {

}

// --------------------- Main Menu --------------------- //

void Menu::mainMenu(bool isLoading) {
    Graph graph;
    int input;

    mainMenuOptions(isLoading);

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    vector<Graph> dataset;

    do {
        switch (input) {
            case 0:
                return;
            case 1:
                Graph::loadGraph("../shipping.csv");
                return;
            case 2:
                lineFailuresMenu();
                return;
            case 3:
                graph.display();
                break;

            case 4:
                int startNode = 0; // Assume starting node has the ID 0
                double result = graph.tspApproximation(startNode);
                std::cout << "Approximate TSP tour distance: " << result << std::endl;
                return;
            case 9:
                if (confirmChoice(true)) setUpMenu();
                else mainMenu(false);
                return;
            default:
                cout << endl << "   Please select a valid option : ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option : ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::mainMenuOptions(bool isLoading) {
    system("clear || cls");
    if (isLoading) {
        cout << endl
             << "   Routing Algorithm for Ocean Shipping and Urban Deliveries                     A.Neves | L.Cunha" << endl
             << "   ---------------------------------------------------------------------" << endl;
    }
    else
        cout << endl
             << "   Main Menu" << endl
             << "   ---------------------------------------------------------------------" << endl;

    cout << "   Please select your desired option by typing it on the selector intake" << endl << endl
         << "     1. load Graph" << endl
         << "     2. Display graph" << endl
         << "     3. Solve TSP (Backtracking Algorithm)" << endl << endl
         << "     4. Solve TSP (TriangularApproximation)" << endl << endl
         << "     5. Solve TSP (Heuristic Algorithm)" << endl << endl << endl
         << "     9. Change Data Set" << endl << endl
         << "     0. Exit application" << endl << endl
         << "   Select your option : ";
}




// ------------------- Line Failures ------------------- //

void Menu::lineFailuresMenu() {
    int input;

    lineFailuresMenuPrinter();

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 0:
                return;
            case 1:
                failuresRemovePipe();
            case 9:
                mainMenu(false);
                return;
            default:
                cout << endl << "   Please select a valid option : ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option : ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::lineFailuresMenuPrinter() {
    system("clear || cls");
    cout << endl
         << "   Reliability and Sensitivity to Line Failures" << endl
         << "   ---------------------------------------------------------------------" << endl
         << "   Please select your desired option by typing it on the selector intake" << endl << end
         << "     1. Remove a Pipe" << endl << endl << endl
         << "     9. Return to Main Menu" << endl << endl
         << "     0. Exit application" << endl << endl
         << "   Select your option : ";
}



void Menu::failuresRemovePipe() {
    system("clear || cls");
    cout << endl << "   | SOURCE |" << endl
         << endl << "   Please enter a valid station code : ";

    auto* src = receiveNode<Node>("", false);

    cout << endl << "   | TARGET |" << endl
         << endl << "   Please enter a valid station code : ";

    auto* dest = receiveNode<Node>("", false);

    Pipe* pipeSD = src->getPipeTo(dest);
    if (pipeSD != nullptr) pipeSD->setCapacity(0);
    Pipe* pipeDS = dest->getPipeTo(src);
    if (pipeDS != nullptr) pipeDS->setCapacity(0);

    network.edmondsKarp(); subNetwork.edmondsKarp();

    cout << endl
         << "   " << src->getCode() << " -> " << dest->getCode() << " has been removed from the network." << endl << endl
         << "   | CITIES AFFECTED |" << endl << endl;

    int n = 0;

    for (int i = 0; i < network.getCitySet().size(); i++)
    {
        City *city1 = network.getCitySet()[i];
        City *city2 = subNetwork.getCitySet()[i];
        if (city1->getCapacity() != city2->getCapacity()) {
            cout << "   " << city1->getCode() << " | " << city1->getName() << endl
                 << "     Old Flow: " << city1->getCapacityValue() - city1->getCapacity() << endl
                 << "     New Flow: " << city2->getCapacityValue() - city2->getCapacity() << endl
                 << "     Deficit: " << (city1->getCapacityValue() - city1->getCapacity()) -
                                        (city2->getCapacityValue() - city2->getCapacity()) << endl << endl;
            n++;
        }
    }

    if (n == 0) cout << "   No city has been affected." << endl << endl;

    if (confirmChoice(1))
    {
        string filename = getFilename();
        filename = "../output/" + filename + ".txt";

        ofstream outFile(filename);
        if(!outFile.is_open()) outFile.open(filename);

        outFile << "| CITIES AFFECTED |" << endl << endl;

        for (int i = 0; i < network.getCitySet().size(); i++)
        {
            City *city1 = network.getCitySet()[i];
            City *city2 = subNetwork.getCitySet()[i];
            if (city1->getCapacity() != city2->getCapacity()) {
                outFile << city1->getCode() << " | " << city1->getName() << endl
                        << "  Old Flow: " << city1->getCapacityValue() - city1->getCapacity() << endl
                        << "  New Flow: " << city2->getCapacityValue() - city2->getCapacity() << endl
                        << "  Deficit: " << (city1->getCapacityValue() - city1->getCapacity()) -
                                            (city2->getCapacityValue() - city2->getCapacity()) << endl << endl;
                n++;
            }
        }

        if (n == 0) outFile << "   No city has been affected." << endl << endl;

        outFile << src->getCode() << " -> " << dest->getCode() << " has been removed from the network." << endl;

        outFile.close();

        subNetwork.deleteNetwork();
        subNetwork.createNetwork(dataPath);

        pressEnterToReturn();
        lineFailuresMenu();
        return;
    }

    subNetwork.deleteNetwork();
    subNetwork.createNetwork(dataPath);

    lineFailuresMenu();
}

// ----------------- Auxiliary Functions ---------------- //

int Menu::receiveNode() {
    string input;

    getline(cin >> ws, input);

    do {
        int node = stoi(input);
        if (node >= 0 && node < graph.getNumVertices()) return node;
        cout << endl << "   Please enter a valid code : ";
        getline(cin >> ws, input);
    }
    while(true);
}

bool Menu::confirmChoice(int flag) {
    int input;

    switch (flag) {
        case 0:
            cout << endl
                 << "   -------------------------" << endl << endl
                 << "   ! WARNING !" << endl << endl
                 << "   You're about to change the data set!" << endl << endl
                 << "     1. Confirm" << endl << endl
                 << "     2. Go back" << endl << endl
                 << "   Select your option : ";
            break;
        case 1:
            cout << "   -------------------------" << endl << endl
                 << "   Do you wish to save the results?" << endl << endl
                 << "     1. Save results to file" << endl << endl
                 << "     2. Go back" << endl << endl
                 << "   Select your option : ";
            break;
        case 2:
            cout << endl
                 << "     1. Advance" << endl << endl
                 << "     2. Retype" << endl << endl
                 << "   Select your option : ";
            break;
        default:
            throw invalid_argument("Invalid option selected.");
    }

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 1:
                return true;
            case 2:
                return false;
            default:
                cout << endl << "   Please select a valid option : ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option : ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::pressEnterToReturn() {
    cout << endl << "   Press ENTER to return...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// -------------------- END OF FILE -------------------- //
