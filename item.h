#ifndef ITEM_H
#define ITEM_H

#include <QString>

#include "upgrade.h"

/**
 * @class Item
 * @brief Represents items in the game.
 */
class Item {
public:
    /**
     * @brief Enum defining bonus types for items.
     */
    enum BonusType {
        UNITS_PER_CLICK, /**< Units per click bonus type. */
        UNITS_PER_SECOND /**< Units per second bonus type. */
    };

private:
    QString name_; /**< Name of the item. */
    QString description_; /**< Description of the item. */
    int bonus_; /**< Bonus provided by the item. */
    BonusType type_; /**< Type of bonus provided by the item. */
    std::function<int(const int)> priceFunction_; /**< Function to calculate the price of the item. */
    Upgrade * pupgrade_; /**< Pointer to the associated upgrade. */

public:
    /**
     * @brief Gets the name of the item.
     * @return The name of the item.
     */
    QString & getName();

    /**
     * @brief Gets the description of the item.
     * @return The description of the item.
     */
    QString & getDescription();

    /**
     * @brief Gets the bonus provided by the item.
     * @return The bonus provided by the item.
     */
    int getBonus() const;

    /**
     * @brief Gets the type of bonus provided by the item.
     * @return The type of bonus provided by the item.
     */
    BonusType getType() const;
    /*
     * @brief Calculates the price of the item.
     * @param quantity The quantity of the item.
     * @return The price of the item.
     */
    int Price(const int quantity) const;

    /**
     * @brief Gets the associated upgrade.
     * @return Pointer to the associated upgrade.
     */
    Upgrade * getUpgrade();

    /**
     * @brief Constructor for the Item class.
     * @param name The name of the item.
     * @param description The description of the item.
     * @param bonus The bonus provided by the item.
     * @param type The type of bonus provided by the item.
     * @param priceFunction The function to calculate the price of the item.
     * @param pupgrade Pointer to the associated upgrade.
     */
    Item(const QString & name, const QString & description, const int bonus, const BonusType type, const std::function<int(const int)> priceFunction, Upgrade * pupgrade);

    /**
     * @brief Destructor for the Item class.
     */
    ~Item();
};

#endif // ITEM_H
