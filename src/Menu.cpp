#include "Menu.h"

#include <chrono>
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
                setUpMedium();
                return;
            case 3:
                setUpLarge();
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
         << "   Please select the graph to be used:" << endl << endl
         << "     1. Tourism" << endl << endl
         << "     2. Stadiums" << endl << endl
         << "     3. Shipping" << endl << endl
         << "   Select your option: ";

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option: ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 1:
                graphSize = 0;
                graph.numVertices = 5;
                dataPath = "../data/small/tourism.csv";
                mainMenu(true);
                return;
            case 2:
                graphSize = 0;
                graph.numVertices = 11;
                dataPath = "../data/small/stadiums.csv";
                mainMenu(true);
                return;
            case 3:
                graphSize = 0;
                graph.numVertices = 14;
                dataPath = "../data/small/shipping.csv";
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

void Menu::setUpMedium() {
    string input;
    int selectedOption;

    vector<int> options = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};

    system("clear || cls");
    cout << endl
         << "   Please type the number of nodes you want to use:" << endl << endl
         << "     Available options:" << endl
         << "     [25,50,75,100,200,300,400,500,600,700,800,900]" << endl << endl
         << "   Type your option: ";

    getline(cin >> ws, input);

    do {
        try {
            selectedOption = stoi(input);
        } catch (invalid_argument& e) {
            cout << endl << "   Please enter a valid code : ";
            getline(cin >> ws, input);
            continue;
        }
        if (find(options.begin(), options.end(), stoi(input)) != options.end()) {
            graphSize = 1;
            graph.numVertices = selectedOption;
            dataPath = "../data/large/edges_" + input + ".csv";
            mainMenu(true);
            return;
        }
        cout << endl << "   Please enter a valid code : ";
        getline(cin >> ws, input);
    }
    while(true);
}

void Menu::setUpLarge() {
    int input;

    system("clear || cls");
    cout << endl
         << "   Please select the graph to be used:" << endl << endl
         << "     1. Graph 999" << endl << endl
         << "     2. Graph 4999" << endl << endl
         << "     3. Graph 9999" << endl << endl
         << "   Select your option: ";

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option: ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 1:
                graphSize = 2;
                graph.numVertices = 999;
                dataPath = "../data/extra_large/graph1/";
                mainMenu(true);
                return;
            case 2:
                graphSize = 2;
                graph.numVertices = 4999;
                dataPath = "../data/extra_large/graph2/";
                mainMenu(true);
                return;
            case 3:
                graphSize = 2;
                graph.numVertices = 9999;
                dataPath = "../data/extra_large/graph3/";
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

// --------------------- Main Menu --------------------- //

void Menu::mainMenu(bool isLoading) {
    int input;

    mainMenuOptions(isLoading);

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 0:
                return;
            case 1:
                BTMenu();
                return;
            case 2:
                TAHMenu();
                return;
            case 9:
                if (confirmChoice(0)) setUpMenu();
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
             << "   Routing Manager - Ocean and Urban Deliveries        A.Neves | L.Cunha" << endl
             << "   ---------------------------------------------------------------------" << endl;
    }
    else
        cout << endl
             << "   Main Menu" << endl
             << "   ---------------------------------------------------------------------" << endl;

    cout << "   Please select your desired option by typing it on the selector intake" << endl << endl
         << "     1. Backtracking Algorithm" << endl << endl
         << "     2. Triangular Approximation Heuristic" << endl << endl << endl
         << "     9. Change Data Set" << endl << endl
         << "     0. Exit application" << endl << endl
         << "   Select your option : ";
}

// -------------------- Backtracking ------------------- //

void Menu::BTMenu() {
    if (graphSize == 2) {
        system("clear || cls");
        cout << endl
             << "   | BACKTRACKING ALGORITHM |" << endl << endl
             << "   Due to the complexity of the Backtracking Algorithm, it is not available for this data set." << endl;

        pressEnterToReturn();
        mainMenu(false);
        return;
    }
    else {
        auto start = chrono::high_resolution_clock::now();

        graph.loadGraphWithFile(dataPath);

        auto load = chrono::high_resolution_clock::now();

        pair<int, vector<int>> result = graph.TSP();

        auto end = chrono::high_resolution_clock::now();

        auto loadTime = chrono::duration_cast<chrono::microseconds>(load - start).count();
        auto algorithmTime = chrono::duration_cast<chrono::milliseconds>(end - load).count();

        system("clear || cls");
        cout << endl
             << "   | BACKTRACKING ALGORITHM |" << endl << endl
             << "   Data Load Time: " << loadTime << " us" << endl
             << "   Algorithm Time: " << algorithmTime << " ms" << endl << endl
             << "   Optimal Path: " << endl
             << "      Cost: " << result.first << endl
             << "      Path: ";

        for (auto i = result.second.begin(); i != result.second.end(); i++) {
            if (i == result.second.begin()) cout << *i;
            else if (i + 1 == result.second.end()) cout << " -> " << *i << endl;
            else cout << " -> " << *i;
        }

        if (dataPath != "../data/small/shipping.csv") {
            if (confirmChoice(1)) {
                vector<vector<int>> optimalPaths = graph.exhaustiveTSP(result.first);

                system("clear || cls");
                cout << endl
                     << "   | BACKTRACKING ALGORITHM |" << endl << endl
                     << "   Data Load Time: " << loadTime << " us" << endl
                     << "   Algorithm Time: " << algorithmTime << " ms" << endl << endl
                     << "   Optimal Path: " << endl
                     << "      Cost: " << result.first << endl
                     << "      Path: ";

                for (auto i = result.second.begin(); i != result.second.end(); i++) {
                    if (i == result.second.begin()) cout << *i;
                    else if (i + 1 == result.second.end()) cout << " -> " << *i << endl;
                    else cout << " -> " << *i;
                }

                cout << endl << "   Found " << optimalPaths.size() - 1 << " additional optimal paths:" << endl << endl;

                for (auto pathIndex = 1; pathIndex != optimalPaths.size(); pathIndex++) {
                    cout << "      ";

                    auto path = optimalPaths[pathIndex];
                    for (auto i = path.begin(); i != path.end(); i++) {
                        if (i == path.begin()) cout << *i;
                        else cout << " -> " << *i;
                    }

                    cout << endl;
                }

                pressEnterToReturn();
            }
        } else pressEnterToReturn();

        mainMenu(false);
        return;
    }
}

// ---------------- Triangular Approach ---------------- //

void Menu::TAHMenu() {

}

// ----------------- Auxiliary Functions ---------------- //

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
            cout << endl
                 << "   -------------------------" << endl << endl
                 << "   Do you wish to see every optimal path found?" << endl << endl
                 << "     1. Yes" << endl << endl
                 << "     2. No" << endl << endl
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
