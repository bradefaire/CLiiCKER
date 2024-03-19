#ifndef ITEM_H
#define ITEM_H

#include <QString>

#include "upgrade.h"

class Item
{
enum BonusType {UNITS_PER_CLICK, UNITS_PER_SECOND};

private:
    QString name_;
    QString description_;
    bool unlocked_;
    int bonus_;
    BonusType type_;
    int quantity_;
    std::function<int(void)> priceFunction_;
    std::list<Upgrade &> upgrades_;

public:
    QString & getName();
    QString & getDescription();
    bool isUnlocked() const;
    int getBonus() const;
    BonusType getType() const;
    int getQuantity() const;
    int Price() const;

    void Unlock();
    void AddQuantity(int = 1);
    void RemoveQuantity(int = 1);
    void AddUpgrade(Upgrade & upgrade);

    Item(const QString &, const QString &, const int, const BonusType,const std::function<int(void)>);
};

#endif // ITEM_H
