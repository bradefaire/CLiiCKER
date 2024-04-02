#ifndef ITEM_H
#define ITEM_H

#include <QString>

#include "upgrade.h"

class Item
{
public:
    enum BonusType{UNITS_PER_CLICK, UNITS_PER_SECOND};

private:
    QString name_;
    QString description_;
    bool unlocked_;
    int bonus_;
    BonusType type_;
    int quantity_;
    std::function<int(const int)> priceFunction_;
    Upgrade * pupgrade_;

public:
    QString & getName();
    QString & getDescription();
    bool isUnlocked() const;
    int getBonus() const;
    BonusType getType() const;
    int getQuantity() const;
    int Price(const int quantity) const;

    Upgrade * getUpgrade();

    void Unlock();
    void AddQuantity(int = 1);
    void RemoveQuantity(int = 1);

    Item(const QString &, const QString &, const int, const BonusType,const std::function<int(const int)>,Upgrade * pupgrade);
};

#endif // ITEM_H
