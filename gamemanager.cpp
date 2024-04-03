#include "gamemanager.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>
#include <QFile>

GameManager::GameManager() {

    upgrades_ = std::vector<Upgrade *>();
    items_ = std::vector<Item *>();

    Upgrade * pupgrade0 = new Upgrade(QString("U1"),QString("Increase UPC by 1"),1,[](const int currentLevel) { return currentLevel + 1;});
    Item * pitem0 = new Item(QString("I1"),QString("Increase the UPC by 1"),1,Item::BonusType::UNITS_PER_CLICK,[](int quantity) { return 2*quantity+1;},pupgrade0);

    upgrades_.push_back(pupgrade0);
    items_.push_back(pitem0);

    Tab * tab1 = new Tab("Tab 1",items_,upgrades_);

    pplayer_ = new Player();

    pplayer_->addListWindow(tab1);

}

bool GameManager::BuyItem(const QString & itemName){
    Tab * currentWindow = pplayer_->getCurrentWindow();
    Item * pitem = currentWindow->getItem(itemName);
    int price = pitem->Price(currentWindow->getItemQuantity(pitem));
    qDebug()<<price<< "   "<< currentWindow->getItemQuantity(pitem);
    if (price > pplayer_->getScore()){
        return false;
    }
    int addedUPS = pplayer_->getCurrentWindow()->AddItem(pitem);
    pplayer_->removeScore(price);
    pplayer_->addUnitsPerSecond(addedUPS);
    return true;
}

bool GameManager::BuyUpgrade(const QString & itemName){
    Tab * currentWindow = pplayer_->getCurrentWindow();
    Upgrade * pupgrade = currentWindow->getItem(itemName)->getUpgrade();
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
    for (Tab * ptab : pplayer_->getWindows()){
        if (ptab->getName() == newName){
            throw new std::invalid_argument("This name is already taken");
            return false;
        }
    }
    int price = pplayer_->getWindowPrice(pplayer_->getNbWindow());
    if (price > pplayer_->getScore()){
        throw std::string("exception : not enough money to spend");
        return false;
    }
    pplayer_->removeScore(price);
    pplayer_->setCurrentWindowIndex(pplayer_->addListWindow(new Tab(newName,items_,upgrades_)) - 1);
    return true;
}

void GameManager::ButtonPressed(){
    qDebug() << "UnitsPerClick : " << pplayer_->getCurrentWindow()->getUPC();
    pplayer_->addScore(pplayer_->getCurrentWindow()->getUPC());
    qDebug() << "pete moi le cul : " << pplayer_->getScore();
}

void GameManager::Update(const int deltaTime){
    pplayer_->addScore(pplayer_->getCurrentWindow()->getUPS() * deltaTime);
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
        QJsonObject upgradesObject;
        for (const auto& [pitem,quantity] : ptab->getItems() ){
            itemsObject.insert(pitem->getName(),quantity);
        }
        for (const auto& [pupgrade,level] : ptab->getUpgrades() ){
            upgradesObject.insert(pupgrade->getName(),level);
        }
        tabObject.insert("name",ptab->getName());
        tabObject.insert("items",itemsObject);
        tabObject.insert("upgrades",upgradesObject);
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
        Tab * tab = new Tab(tabObject.value("name").toString(),items_,upgrades_);
        QJsonObject itemsObject = tabObject.value("items").toObject();
        QJsonObject upgradesObject = tabObject.value("upgrades").toObject();
        for (const QString& itemName : itemsObject.keys() ){
            tab->AddItem(tab->getItem(itemName),itemsObject.value(itemName).toInt());
        }
        for (const QString& upgradeName : upgradesObject.keys() ){
            tab->AddUpgrade(tab->getUpgrade(upgradeName),upgradesObject.value(upgradeName).toInt());
        }
        tabs.push_back(tab);
    }

    pplayer_ = new Player(mainObject.value("name").toString(),mainObject.value("score").toInt(),mainObject.value("UPS").toInt(),static_cast<int>(tabs.size()),tabs);

}

void GameManager::NewGame(const QString & name){
    pplayer_ = new Player(name);
}

int GameManager::getScore()
{
    return pplayer_->getScore();
}
