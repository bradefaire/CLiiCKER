#ifndef TAB_H
#define TAB_H

#include <QString>
#include <map>

#include "item.h"
#include "upgrade.h"
#include "vector"

/**
 * @class Tab
 * @brief Represents a tab in the game.
 */
class Tab {
private:
    QString name_; /**< Name of the tab. */
    int unitsPerSecond_; /**< Units per second of the tab. */
    int unitsPerClick_; /**< Units per click of the tab. */

    std::map<Item *, int> items_; /**< Map of items and their quantities in the tab. */
    std::map<Upgrade *, int> upgrades_; /**< Map of upgrades and their levels in the tab. */

public:
    /**
     * @brief Gets the name of the tab.
     * @return The name of the tab.
     */
    QString & getName();

    /**
     * @brief Gets the units per second of the tab.
     * @return The units per second of the tab.
     */
    int getUPS();

    /**
     * @brief Gets the units per click of the tab.
     * @return The units per click of the tab.
     */
    int getUPC();

    /**
     * @brief Gets the upgrade with the specified name.
     * @param itemName The name of the upgrade.
     * @return Pointer to the upgrade with the specified name.
     */
    Upgrade * getUpgrade(const QString & itemName);

    /**
     * @brief Gets the item with the specified name.
     * @param itemName The name of the item.
     * @return Pointer to the item with the specified name.
     */
    Item * getItem(const QString & itemName);

    /**
     * @brief Gets the level of the specified upgrade.
     * @param pupgrade Pointer to the upgrade.
     * @return The level of the upgrade.
     */
    int getUpgradeLevel(Upgrade * pupgrade);

    /**
     * @brief Gets the quantity of the specified item.
     * @param pitem Pointer to the item.
     * @return The quantity of the item.
     */
    int getItemQuantity(Item * pitem);

    /**
     * @brief Gets the map of items and their quantities in the tab.
     * @return The map of items and their quantities.
     */
    std::map<Item *, int> getItems();

    /**
     * @brief Gets the map of upgrades and their levels in the tab.
     * @return The map of upgrades and their levels.
     */
    std::map<Upgrade *, int> getUpgrades();

    /**
     * @brief Adds an item to the tab.
     * @param pitem Pointer to the item to add.
     * @param amount The quantity of the item to add.
     * @return The amount of units per second gained.
     */
    int AddItem(Item * pitem, const int amount = 1);

    /**
     * @brief Adds an upgrade to the tab.
     * @param pupgrade Pointer to the upgrade to add.
     * @param amount The quantity of the upgrade to add.
     * @return The amount of units per second gained.
     */
    int AddUpgrade(Upgrade * pupgrade, const int amount = 1);

    /**
     * @brief Constructor for the Tab class.
     * @param name The name of the tab.
     * @param UPS The units per second of the tab.
     * @param UPC The units per click of the tab.
     */
    Tab(const QString & name, const int UPS, const int UPC);

    /**
     * @brief Constructor for the Tab class with initial items.
     * @param name The name of the tab.
     * @param items Vector of pointers to initial items in the tab.
     */
    Tab(const QString & name, std::vector<Item *> items,const int UPC=1);

    /**
     * @brief Destructor for the Tab class.
     */
    ~Tab() = default;
};

#endif // TAB_H
