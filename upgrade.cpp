#include "upgrade.h"

Upgrade::Upgrade(const QString & name, const QString & description, const int bonus, const std::function<int(const int)> priceFunction){

    unlocked_ = false;
    description_ = description;
    name_ = name;
    bonus_ = bonus;
    priceFunction_ = priceFunction;
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

void Upgrade::Unlock(){
    unlocked_ = true;
}

int Upgrade::Price(const int currentLevel) const {
    return priceFunction_(currentLevel);
}
