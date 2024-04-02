#include "gamemanager.h"

GameManager::GameManager() {

    upgrades_ = std::vector<Upgrade *>();
    items_ = std::vector<Item *>();

    Upgrade * pupgrade0 = new Upgrade(QString("U1"),QString("Increase UPC by 1"),1,[](const int currentLevel) { return currentLevel;});
    Item * pitem0 = new Item(QString("I1"),QString("Increase the UPC by 1"),1,Item::BonusType::UNITS_PER_CLICK,[](int quantity) { return 2*quantity;},pupgrade0);

    upgrades_.push_back(pupgrade0);
    items_.push_back(pitem0);

    pplayer_ = new Player();

}

bool GameManager::BuyItem(const QString & itemName){
    Item * pitem = pplayer_->getCurrentWindow()->getItem(itemName);
    int price = pitem->Price();
    if (price > pplayer_->getScore()){
        return false;
    }
    int addedUPS = pplayer_->getCurrentWindow()->AddItem(pitem);
    pplayer_->removeScore(price);
    pplayer_->addUnitsPerSecond(addedUPS);
    return true;
}

bool GameManager::BuyUpgrade(const QString & upgradeName){
    Tab * currentWindow = pplayer_->getCurrentWindow();
    Upgrade * pupgrade = currentWindow->getUpgrade(upgradeName);
    int price = pupgrade->Price(currentWindow->getUpgradeLevel(pupgrade));
    if (price > pplayer_->getScore()){
        return false;
    }
    int addedUPS = currentWindow->AddUpgrade(pupgrade);
    pplayer_->removeScore(price);
    pplayer_->addUnitsPerSecond(addedUPS);
    return true;
}

bool GameManager::BuyTab(const QString & newName){
    int price = pplayer_->getWindowPrice(pplayer_->getNbWindow());
    if (price > pplayer_->getScore()){
        return false;
    }
    pplayer_->removeScore(price);
    pplayer_->setCurrentWindowIndex(pplayer_->getNbWindow());
    pplayer_->addListWindow(new Tab(newName,items_,upgrades_));
    return true;
}
