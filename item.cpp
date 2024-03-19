#include "item.h"

Item::Item(const QString & name, const QString & description, const int bonus, const BonusType type,const std::function<int(void)> priceFunction) {
    name_ = name;
    description_ = description;
    bonus_ = bonus;
    type_ = type;
    priceFunction_ = priceFunction;

    quantity_ = 0;
    unlocked_ = false;
    upgrades_ = new std::list<Upgrade &>();
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

int Item::Price() const {
    return priceFunction_();
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

void Item::AddUpgrade(Upgrade & upgrade){
    upgrades_.push_back(upgrade);
}
