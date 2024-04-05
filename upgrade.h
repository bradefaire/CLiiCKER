#ifndef UPGRADE_H
#define UPGRADE_H

#include <QString>

/**
 * @class Upgrade
 * @brief Represents an upgrade in the game.
 */
class Upgrade {
private:
    QString description_; /**< Description of the upgrade. */
    QString name_; /**< Name of the upgrade. */
    int bonus_; /**< Bonus provided by the upgrade. */
    std::function<int(const int)> priceFunction_; /**< Function to calculate the price of the upgrade. */

public:
    /**
     * @brief Calculates the price of the upgrade.
     * @param currentLevel The current level of the upgrade.
     * @return The price of the upgrade.
     */
    int Price(const int) const;

    /**
     * @brief Gets the description of the upgrade.
     * @return The description of the upgrade.
     */
    QString & getDescription();

    /**
     * @brief Gets the name of the upgrade.
     * @return The name of the upgrade.
     */
    QString & getName();

    /**
     * @brief Gets the bonus provided by the upgrade.
     * @return The bonus provided by the upgrade.
     */
    int getBonus() const;

    /**
     * @brief Unlocks the upgrade.
     */
    void Unlock();

    /**
     * @brief Assignment operator for the Upgrade class.
     * @param other The Upgrade object to copy from.
     */
    void operator=(const Upgrade & other);

    /**
     * @brief Constructor for the Upgrade class.
     * @param name The name of the upgrade.
     * @param description The description of the upgrade.
     * @param bonus The bonus provided by the upgrade.
     * @param priceFunction The function to calculate the price of the upgrade.
     */
    Upgrade(const QString &, const QString &, const int, const std::function<int(const int)>);

    /**
     * @brief Destructor for the Upgrade class.
     */
    ~Upgrade() = default;
};

#endif // UPGRADE_H
