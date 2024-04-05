#include "tab.h"

#include <stdexcept>

Tab::Tab(const QString & name, const int UPS, const int UPC) {

    name_ = name;
    unitsPerSecond_ = UPS;
    unitsPerClick_ = UPC;

}

Tab::Tab(const QString & name, std::vector<Item *> items, const int UPC){
    name_ = name;
    unitsPerSecond_ = 0;
    unitsPerClick_ = UPC;
    for (Item * pitem : items){
        this->AddItem(pitem,0);
    }
}

QString & Tab::getName(){
    return name_;
}

int Tab::getUPS(){
    return unitsPerSecond_;
}

int Tab::getUPC(){
    return unitsPerClick_;
}

int Tab::AddItem(Item * pitem, const int amount){
    int addedUPS = 0;
    int quantity;
    try {
        quantity = items_.at(pitem) + amount;
    }
    catch (std::out_of_range){
        quantity = amount;
        AddUpgrade(pitem->getUpgrade(),0);
    }
    Upgrade * pupgrade = pitem->getUpgrade();
    int bonus = (pitem->getBonus() + upgrades_.at(pupgrade) * pupgrade->getBonus()) * amount;
    if (pitem->getType() == Item::BonusType::UNITS_PER_CLICK){
        unitsPerClick_ += bonus;
    }
    else{
        unitsPerSecond_ += bonus;
        addedUPS = bonus;
    }

    items_[pitem] = quantity;
    return addedUPS;
}

int Tab::AddUpgrade(Upgrade * pupgrade, const int amount){
    int addedUPS = 0;
    int level;
    try {
        level = upgrades_.at(pupgrade) + amount;
    }
    catch (std::out_of_range){
        level = amount;
    }
    for (const auto& [pitem,quantity] : items_){
        if (pitem->getUpgrade() == pupgrade){
            int bonus = pupgrade->getBonus() * amount;
            if (pitem->getType() == Item::BonusType::UNITS_PER_CLICK){
                unitsPerClick_ += bonus;
            }
            else{
                unitsPerSecond_ += bonus;
                addedUPS = bonus;
            }
        }
    }

    upgrades_[pupgrade] = level;

    return addedUPS;
}

Upgrade * Tab::getUpgrade(const QString & itemName){
    for (auto const& kv : items_){
        if ((kv.first)->getName() == itemName){
            return kv.first->getUpgrade();
        }
    }
    throw new std::out_of_range("non-existing upgrade");
}

Item * Tab::getItem(const QString & itemName){
    for (auto const& kv : items_){
        if ((kv.first)->getName() == itemName){
            return kv.first;
        }
    }
    throw new std::out_of_range("non-existing item");
}

int Tab::getUpgradeLevel(Upgrade * pupgrade){
    return upgrades_.at(pupgrade);
}

int Tab::getItemQuantity(Item * pitem){
    return items_.at(pitem);
}

std::map<Item *,int> Tab::getItems(){
    return items_;
}

std::map<Upgrade *,int> Tab::getUpgrades(){
    return upgrades_;
}
