#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <vector>

#include "stats.h"
#include "tab.h"

/**
 * @class Player
 * @brief Represents a player in the game.
 */
class Player {
public:
    /**
     * @brief Default constructor for the Player class.
     */
    Player();

    /**
     * @brief Constructor for the Player class with a specified name.
     * @param Name The name of the player.
     */
    Player(const QString & Name);

    /**
     * @brief Constructor for the Player class with a specified name and base tab.
     * @param Name The name of the player.
     * @param pBaseTab Pointer to the base tab.
     */
    Player(const QString & Name, Tab * pBaseTab);

    /**
     * @brief Constructor for the Player class with specified parameters.
     * @param Name The name of the player.
     * @param _score The initial score of the player.
     * @param _unitPerSecond The initial units per second of the player.
     * @param _nbWindow The initial number of windows of the player.
     * @param _ListWindow The list of windows owned by the player.
     */
    Player(QString Name, int _score, int _unitPerSecond, int _nbWindow, std::vector<Tab *> _ListWindow);

    /**
     * @brief Destructor for the Player class.
     */
    ~Player();

private:
    QString name; /**< Name of the player. */
    int score; /**< Score of the player. */
    int unitPerSecond; /**< Units per second of the player. */
    int nbWindow; /**< Number of windows of the player. */
    std::vector<Tab *> listWindow; /**< List of windows owned by the player. */
    int currentWindowIndex; /**< Index of the current window. */
    Stats statPlayer; /**< Stats of the player. */

public:
    /**
     * @brief Adds score to the player.
     * @param score The score to add.
     */
    void addScore(const int score);

    /**
     * @brief Removes score from the player.
     * @param score The score to remove.
     */
    void removeScore(const int score);

    /**
     * @brief Gets the score of the player.
     * @return The score of the player.
     */
    int getScore();

    /**
     * @brief Adds units per second to the player.
     * @param score The units per second to add.
     */
    void addUnitsPerSecond(const int score);

    /**
     * @brief Calculates the price of adding a window.
     * @param nbWindow The number of windows.
     * @return The price of adding a window.
     */
    int getWindowPrice(int nbWindow);

    /**
     * @brief Adds a window to the player's list of windows.
     * @param tab Pointer to the tab representing the new window.
     * @return The index of the added window.
     */
    int addListWindow(Tab * tab);

    /**
     * @brief Gets the current window.
     * @return Pointer to the current window.
     */
    Tab * getCurrentWindow();

    /**
     * @brief Sets the index of the current window.
     * @param newIndex The index of the new current window.
     */
    void setCurrentWindowIndex(const int newIndex);

    /**
     * @brief Gets the number of windows owned by the player.
     * @return The number of windows.
     */
    int getNbWindow();

    /**
     * @brief Gets the list of windows owned by the player.
     * @return The list of windows.
     */
    std::vector<Tab *> getWindows();

    /**
     * @brief Sets the name of the player.
     * @param Name The new name of the player.
     */
    void setName(const QString & Name);

    /**
     * @brief Gets the name of the player.
     * @return The name of the player.
     */
    QString getName();

    /**
     * @brief Gets the units per second of the player.
     * @return The units per second of the player.
     */
    int getUPS();

    /**
     * @brief Adds an item to the player's inventory.
     * @param pitem Pointer to the item to add.
     */
    void AddItem(Item * pitem);

    /**
     * @brief Adds an upgrade to the player's upgrades.
     * @param pupgrade Pointer to the upgrade to add.
     */
    void AddUpgrade(Upgrade * pupgrade);
};


#endif // PLAYER_H
