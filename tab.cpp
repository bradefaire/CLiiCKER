#include "tab.h"

#include <stdexcept>

Tab::Tab(const QString & name, int UPS, int UPC) {

    name_ = name;
    unitsPerSecond_ = UPS;
    unitsPerClick_ = UPC;

}

Tab::Tab(const QString & name, std::vector<Item *> items, std::vector<Upgrade *> upgrades){
    Tab(name,0,0);
    for (Item * pitem : items){
        this->AddItem(pitem);
    }
    for (Upgrade * pupgrade : upgrades){
        this->AddUpgrade(pupgrade);
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

int Tab::AddItem(Item * pitem){
    int addedUPS = 0;
    int value;
    try {
        value = items_.at(pitem) + 1;
        pitem->AddQuantity();
        Upgrade * pupgrade = pitem->getUpgrade();
        int bonus = pitem->getBonus() + upgrades_.at(pupgrade) * pupgrade->getBonus();
        if (pitem->getType() == Item::BonusType::UNITS_PER_CLICK){
            unitsPerClick_ += bonus;
        }
        else{
            unitsPerSecond_ += bonus;
            addedUPS = bonus;
        }
    }
    catch (std::out_of_range){
        value = 0;
        AddUpgrade(pitem->getUpgrade());
    }

    items_[pitem] = value;
    return addedUPS;
}

int Tab::AddUpgrade(Upgrade * pupgrade){
    int addedUPS = 0;
    int level;
    try {
        level = upgrades_.at(pupgrade) + 1;
        for (const auto& [pitem,quantity] : items_){
            if (pitem->getUpgrade() == pupgrade){
                int bonus = pupgrade->getBonus() * quantity;
                if (pitem->getType() == Item::BonusType::UNITS_PER_CLICK){
                    unitsPerClick_ += bonus;
                }
                else{
                    unitsPerSecond_ += bonus;
                    addedUPS = bonus;
                }
            }
        }
    }
    catch (std::out_of_range){
        level = 0;
    }

    upgrades_[pupgrade] = level;
    return addedUPS;
}

Upgrade * Tab::getUpgrade(const QString & upgradeName){
    for (auto const& kv : upgrades_){
        if ((kv.first)->getName() == upgradeName){
            return kv.first;
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
