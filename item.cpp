#include "item.h"

Item::Item(const QString & name, const QString & description, const int bonus, const BonusType type,const std::function<int(const int)> priceFunction, Upgrade * pupgrade) {
    name_ = name;
    description_ = description;
    bonus_ = bonus;
    type_ = type;
    priceFunction_ = priceFunction;

    pupgrade_ = pupgrade;

    quantity_ = 0;
    unlocked_ = false;
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

int Item::getQuantity() const{
    return quantity_;
}

Item::BonusType Item::getType() const {
    return type_;
}

bool Item::isUnlocked() const {
    return unlocked_;
}

int Item::Price(const int quantity) const {
    return priceFunction_(quantity);
}

void Item::Unlock() {
    unlocked_ = true;
}

void Item::AddQuantity(int quantity){
    if (quantity < 0){
        throw "Unvalid Argument : quantity should be positive";
    }
    quantity_ += quantity;
}

void Item::RemoveQuantity(int quantity){
    if (quantity < 0){
        throw "Unvalid Argument : quantity should be positive";
    }
    if (quantity > quantity_){
        throw "Unvalid Argument : removed quantity should be less than available quantity";
    }
    quantity_ -= quantity;
}

Upgrade * Item::getUpgrade(){
    return pupgrade_;
}
