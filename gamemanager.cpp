#include "gamemanager.h"

#include <QJsonDocument>

GameManager::GameManager() {

    upgrades_ = std::vector<Upgrade *>();
    items_ = std::vector<Item *>();

    Upgrade * pupgrade0 = new Upgrade(QString("U1"),QString("Increase UPC by 1"),1,[](const int currentLevel) { return currentLevel;});
    Item * pitem0 = new Item(QString("I1"),QString("Increase the UPC by 1"),1,Item::BonusType::UNITS_PER_CLICK,[](int quantity) { return 2*quantity;},pupgrade0);

    upgrades_.push_back(pupgrade0);
    items_.push_back(pitem0);

    Tab * tab1 = new Tab("Hello World",items_,upgrades_);

    pplayer_ = new Player();

    pplayer_->addListWindow(tab1);

}

bool GameManager::BuyItem(const QString & itemName){
    Tab * currentWindow = pplayer_->getCurrentWindow();
    Item * pitem = currentWindow->getItem(itemName);
    int price = pitem->Price(currentWindow->getItemQuantity(pitem));
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

void GameManager::ButtonPressed(){
    pplayer_->addScore(pplayer_->getCurrentWindow()->getUPC());
}

void GameManager::Update(const int deltaTime){
    pplayer_->addScore(pplayer_->getCurrentWindow()->getUPS() * deltaTime);
}

void GameManager::ChangeTab(const int tabIndex){
    pplayer_->setCurrentWindowIndex(tabIndex);
}

void GameManager::SaveGame(){
    // QJsonObject mainObject;
    // mainObject.insert("score",QJsonValue(pplayer_->getScore()));
    // QJsonArray tabsArray;
    // for (Tab * ptab : pplayer_->getWindows()){
    //     QJsonObject tabOcject;
    //     QJsonObject itemsObject;
    //     QJsonObject upgradesObject;
    //     for (const auto& [pitem,quantity] : ptab->getItems() ){
    //         itemsObject.insert(pitem->getName(),quantity);
    //     }
    //     for (const auto& [pupgrade,level] : ptab->getUpgrades() ){
    //         upgradesObject.insert(pupgrade->getName(),level);
    //     }
    //     tabOcject.insert("items",itemsObject);
    //     tabOcject.insert("upgrades",upgradesObject);
    //     tabsArray.append(ptab->getName(),tabObject);
    // }
    // mainObject.insert("tabs",tabsArray);
}

void GameManager::LoadGame(){
    return;
}

void GameManager::NewGame(){
    return;
}
