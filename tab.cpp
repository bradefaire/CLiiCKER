#include "tab.h"

#include <stdexcept>

Tab::Tab(QString & name, int UPS, int UPC) {

    name_ = name;
    unitsPerSecond_ = UPS;
    unitsPerClick_ = UPC;

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

void Tab::AddItem(Item * pitem){
    int value;
    try {
        value = items_.at(pitem) + 1;
        pitem->AddQuantity();
        Upgrade * pupgrade = pitem->getUpgrade();
        int bonus = pitem->getBonus() + upgrades_.at(pupgrade) * pupgrade->getBonus();
        if (pitem->getType() == Item::BonusType::UNITS_PER_CLICK)
            unitsPerClick_ += bonus;
        else
            unitsPerSecond_ += bonus;
    }
    catch (std::out_of_range){
        value = 0;
        AddUpgrade(pitem->getUpgrade());
    }

    items_[pitem] = value;
}

void Tab::AddUpgrade(Upgrade * pupgrade){
    int level;
    try {
        level = upgrades_.at(pupgrade) + 1;
        for (const auto& [pitem,quantity] : items_){
            if (pitem->getUpgrade() == pupgrade){
                int bonus = pupgrade->getBonus() * quantity;
                if (pitem->getType() == Item::BonusType::UNITS_PER_CLICK)
                    unitsPerClick_ += bonus;
                else
                    unitsPerSecond_ += bonus;
            }
        }
    }
    catch (std::out_of_range){
        level = 0;
    }

    upgrades_[pupgrade] = level;
}
