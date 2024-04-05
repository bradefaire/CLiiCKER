#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "upgrade.h"
#include "tab.h"
#include "item.h"
#include "vector"

/**
 * @class GameManager
 * @brief Manages game state and interactions.
 */
class GameManager {
public:
    /**
     * @brief Constructor for GameManager class.
     */
    GameManager();

    /**
     * @brief Destructor for GameManager class.
     */
    ~GameManager();

    /**
     * @brief Buys an item in the game.
     * @param itemName The name of the item to buy.
     * @return True if the item was successfully bought, false otherwise.
     */
    bool BuyItem(const QString & itemName);

    /**
     * @brief Buys an upgrade in the game.
     * @param upgradeName The name of the upgrade to buy.
     * @return True if the upgrade was successfully bought, false otherwise.
     */
    bool BuyUpgrade(const QString & upgradeName);

    /**
     * @brief Buys a new tab in the game.
     * @param newName The name of the new tab.
     * @return True if the tab was successfully bought, false otherwise.
     */
    bool BuyTab(const QString & newName);

    /**
     * @brief Handles button presses in the game.
     */
    void ButtonPressed();

    /**
     * @brief Changes the current tab in the game.
     * @param tabIndex The index of the tab to change to.
     */
    void ChangeTab(const int tabIndex);

    /**
     * @brief Saves the current game state to a file.
     * @param filename The name of the file to save the game to.
     */
    void SaveGame(const QString & filename);

    /**
     * @brief Loads a game state from a file.
     * @param filename The name of the file to load the game from.
     */
    void LoadGame(const QString & filename);

    /**
     * @brief Starts a new game.
     * @param unused An unused parameter.
     */
    void NewGame(const QString &);

    /**
     * @brief Gets the current score of the game.
     * @return The current score.
     */
    int getScore();

public slots:
    /**
     * @brief Updates the game state based on elapsed time.
     * @param deltaTime The time elapsed since the last update.
     */
    void Update(const int deltaTime);

private:
    std::vector<Upgrade *> upgrades_; /**< Vector of pointers to upgrades. */
    std::vector<Item *> items_; /**< Vector of pointers to items. */
    Player * pplayer_; /**< Pointer to the player object. */
    int accumulatedScore_; /**< Accumulated score in the game. */
};
#endif // GAMEMANAGER_H
