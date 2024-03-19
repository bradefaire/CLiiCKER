#include "upgrade.h"

Upgrade::Upgrade(const QString & name, const QString & description, const int bonus, const std::function<int(void)> priceFunction){

    unlocked_ = false;
    description_ = description;
    name_ = name;
    bonus_ = bonus;
    priceFunction_ = priceFunction;

    level_ = 0;

}

bool Upgrade::isUnlocked() const {
    return unlocked_;
}

QString & Upgrade::getDescription(){
    return description_;
}

QString & Upgrade::getName(){
    return name_;
}

int Upgrade::getBonus() const {
    return bonus_;
}

int Upgrade::getLevel() const {
    return level_;
}

void Upgrade::Unlock(){
    unlocked_ = true;
}

int Upgrade::Price() const {
    return priceFunction_();
}

void Upgrade::AddLevel(int levelAmount) {
    if (levelAmount < 0){
        throw "Unvalid Argument, levelAmount should be positive";
    }
    level_ += levelAmount;
}

void Upgrade::operator=(const Upgrade & original){
    this = new Upgrade(original.getName(),original.getDescription(),original.getBonus(),original.Price);
}
