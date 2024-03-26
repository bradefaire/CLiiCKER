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

void GameManager::BuyItem(const int itemIndex){
    return;
}

void GameManager::BuyUpgrade(const int upgradeIndex){
    return;
}

void GameManager::BuyTab(){
    return;
}
