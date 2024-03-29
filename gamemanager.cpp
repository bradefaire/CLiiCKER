#include "gamemanager.h"

GameManager::GameManager() {

    upgrades_ = new Upgrade*[1];
    items_ = new Item*[1];

    Upgrade * pupgrade0 = new Upgrade(QString("U1"),QString("Increase UPC by 1"),1,[](const int currentLevel) { return currentLevel;});
    Item * pitem0 = new Item(QString("I1"),QString("Increase the UPC by 1"),1,Item::BonusType::UNITS_PER_CLICK,[](int quantity) { return 2*quantity;},pupgrade0);

    upgrades_[0] = pupgrade0;
    items_[0] = pitem0;

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

bool GameManager::BuyTab(){
    return false;
}
