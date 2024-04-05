#include "gamemanager.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>
#include <QFile>

GameManager::GameManager() {

    accumulatedScore_ = 0;

    items_ = std::vector<Item *>();

    Upgrade * pupgrade0 = new Upgrade(QString("BetterClickUpgrade"),QString("Increase UPC by 1"),1,[](const int currentLevel) { return currentLevel + 1;});
    Item * pitem0 = new Item(QString("Better click"),QString("Increase the UPC by 1"),1,Item::BonusType::UNITS_PER_CLICK,[](int quantity) { return 2*quantity+1;},pupgrade0);

    items_.push_back(pitem0);

    Upgrade * pupgrade1 = new Upgrade(QString("AutoClickUpgrade"),QString("Increase UPS by 1"),1,[](const int currentLevel){ return currentLevel + 1;});
    Item * pitem1 = new Item(QString("AutoClick"),QString("Increase the UPS by 1"),1,Item::BonusType::UNITS_PER_SECOND,[](int quantity){return 2*quantity+1;},pupgrade1);

    items_.push_back(pitem1);

    Tab * tab1 = new Tab("Tab 1",items_);

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
    pplayer_->removeScore(price);
    pplayer_->AddItem(pitem);
    return true;
}

bool GameManager::BuyUpgrade(const QString & itemName){
    Tab * currentWindow = pplayer_->getCurrentWindow();
    Upgrade * pupgrade = currentWindow->getItem(itemName)->getUpgrade();
    int price = pupgrade->Price(currentWindow->getUpgradeLevel(pupgrade));
    if (price > pplayer_->getScore()){
        return false;
    }
    pplayer_->removeScore(price);
    pplayer_->AddUpgrade(pupgrade);
    return true;
}

bool GameManager::BuyTab(const QString & newName){
    for (Tab * ptab : pplayer_->getWindows()){
        if (ptab->getName() == newName){
            qDebug()<<("This name is already taken");
            return false;
        }
    }
    int price = pplayer_->getWindowPrice(pplayer_->getNbWindow());
    if (price > pplayer_->getScore()){
        qDebug()<<("exception : not enough money to spend");
        return false;
    }
    pplayer_->removeScore(price);
    pplayer_->setCurrentWindowIndex(pplayer_->addListWindow(new Tab(newName,items_)) - 1);
    return true;
}

void GameManager::ButtonPressed(){
    pplayer_->addScore(pplayer_->getCurrentWindow()->getUPC());
}

void GameManager::Update(const int deltaTime){
    accumulatedScore_ += pplayer_->getUPS()*deltaTime;
    pplayer_->addScore(accumulatedScore_/1000);
    accumulatedScore_ %= 1000;
}

void GameManager::ChangeTab(const int tabIndex){
    pplayer_->setCurrentWindowIndex(tabIndex);
}

void GameManager::SaveGame(const QString & filename){
    QJsonObject mainObject;
    mainObject.insert("name",QJsonValue(pplayer_->getName()));
    mainObject.insert("score",QJsonValue(pplayer_->getScore()));
    mainObject.insert("UPS",QJsonValue(pplayer_->getUPS()));
    QJsonArray tabsArray;
    for (Tab * ptab : pplayer_->getWindows()){
        QJsonObject tabObject;
        QJsonObject itemsObject;
        for (const auto& [pitem,quantity] : ptab->getItems() ){
            QJsonObject currentItemObject;
            currentItemObject.insert("quantity",quantity);
            currentItemObject.insert("upgradeLevel",ptab->getUpgradeLevel(pitem->getUpgrade()));
            itemsObject.insert(pitem->getName(),currentItemObject);
        }
        tabObject.insert("name",ptab->getName());
        tabObject.insert("items",itemsObject);
        tabsArray.append(tabObject);
    }
    mainObject.insert("tabs",tabsArray);

    QJsonDocument document;
    document.setObject(mainObject);

    QFile file(filename);
    file.open(QFile::QIODevice::WriteOnly);
    file.write(document.toJson());
    file.close();
}

void GameManager::LoadGame(const QString & filename){
    QFile file(filename);
    file.open(QFile::QIODevice::ReadOnly);
    QString data = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());

    if ((!document.isObject()) || document.isEmpty() || document.isNull()){
        throw std::invalid_argument("Unvalid loading file");
    }

    QJsonObject mainObject = document.object();

    std::vector<Tab *> tabs;

    QJsonArray tabsArray = mainObject.value("tabs").toArray();

    // c'est déguelasse il faudrait changer de la structure
    for (int i=0; i<tabsArray.size(); i++){
        QJsonObject tabObject = tabsArray[i].toObject();
        Tab * tab = new Tab(tabObject.value("name").toString(),items_);
        QJsonObject itemsObject = tabObject.value("items").toObject();
        for (const QString& itemName : itemsObject.keys() ){
            QJsonObject currentItemObject = itemsObject.value(itemName).toObject();
            Item * pitem = tab->getItem(itemName);
            tab->AddItem(pitem,currentItemObject.value("quantity").toInt());
            tab->AddUpgrade(pitem->getUpgrade(),currentItemObject.value("upgradeLevel").toInt());
        }
        tabs.push_back(tab);
    }

    pplayer_ = new Player(mainObject.value("name").toString(),mainObject.value("score").toInt(),mainObject.value("UPS").toInt(),static_cast<int>(tabs.size()),tabs);

}

void GameManager::NewGame(const QString & name){
    pplayer_ = new Player(name,new Tab("Tab 1",items_));
}

int GameManager::getScore()
{
    return pplayer_->getScore();
}
