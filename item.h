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
    int bonus_;
    BonusType type_;
    std::function<int(const int)> priceFunction_;
    Upgrade * pupgrade_;

public:
    QString & getName();
    QString & getDescription();
    int getBonus() const;
    BonusType getType() const;
    int Price(const int quantity) const;

    Upgrade * getUpgrade();

    Item(const QString &, const QString &, const int, const BonusType,const std::function<int(const int)>,Upgrade * pupgrade);
    ~Item();
};

#endif // ITEM_H
