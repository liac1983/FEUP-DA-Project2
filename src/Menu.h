#ifndef MENU_H
#define MENU_H

#include "Graph.h"

/**
 * @brief Class representing the menu for interacting with the graph.
 */
class Menu {
public:

    /* Constructor */
    Menu();

    /* Set Up */
    /**
     * @brief Displays the Setup Menu where the user can choose the size of the data set to work with.
     */
    void setUpMenu();
    /**
     * @brief Displays the Small Graph Menu where the user can choose the graph to work with.
     */
    void setUpSmall();
    /**
     * @brief Displays the Large Graph Menu where the user can choose the graph to work with.
     */
    void setUpMedium();
    /**
     * @brief Displays the Extra Large Graph Menu where the user can choose the graph to work with.
     */
    void setUpLarge();

    /* Main Menu */
    /**
     * @brief Manages the user input for the Main Menu.
     * @param isLoading Flag indicating if the menu is being loaded for the first time.
     */
    void mainMenu(bool isLoading);
    /**
     * @brief Displays the Main Menu.
     * @param isLoading Flag indicating if the menu is being loaded for the first time.
     */
    static void mainMenuOptions(bool isLoading);

    /* Backtracking */

    /**
     * @brief Loads the graph with the contents from a file, calls the TSP function and displays the results.
     */
    void BTMenu();

    /* Triangular Approximation */
    /**
     * @brief Loads the graph with the contents from a file, calls the Triangular Approximation Heuristic function and displays the results.
     */
    void TAHMenu();

    /* Auxiliary Functions */
    /**
     * @brief Confirms the user's choice based on the provided flag.
     * @param flag The flag indicating the type of confirmation.
     * @return True if the user confirms, false otherwise.
     */
    static bool confirmChoice(int flag);
    /**
     * @brief Prompts the user to press Enter to return.
     */
    static void pressEnterToReturn();

private:

    Graph graph; /**< Main Graph. */
    int graphSize; /**< Size of the graph. */
    std::string dataPath; /**< Path to the data file. */

};

#endif //MENU_H
