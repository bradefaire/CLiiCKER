#include "item.h"

Item::Item(const QString & name, const QString & description, const int bonus, const BonusType type,const std::function<int(const int)> priceFunction, Upgrade * pupgrade) {
    name_ = name;
    description_ = description;
    bonus_ = bonus;
    type_ = type;
    priceFunction_ = priceFunction;

    pupgrade_ = pupgrade;
}

Item::~Item(){
    delete pupgrade_;
}

int Item::getBonus() const{
    return bonus_;
}

QString & Item::getName(){
    return name_;
}

QString & Item::getDescription(){
    return description_;
}

Item::BonusType Item::getType() const {
    return type_;
}

int Item::Price(const int quantity) const {
    return priceFunction_(quantity);
}

Upgrade * Item::getUpgrade(){
    return pupgrade_;
}
