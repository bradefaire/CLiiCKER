#include "player.h"

#include <stdexcept>
#include <math.h>

Player::Player() {
    score = 0;
    unitPerSecond = 0;
    nbWindow = 0;
    currentWindowIndex = 0;
    listWindow = std::vector<Tab *>();
}

Player::Player(const QString & Name) {
    name = Name;
    score = 0;
    unitPerSecond = 0;
    nbWindow = 0;
    currentWindowIndex = 0;
    listWindow = std::vector<Tab *>();
}

Player::Player(const QString & Name,Tab * pBaseTab){
    name = Name;
    score = 0;
    unitPerSecond = 0;
    nbWindow = 1;
    currentWindowIndex = 0;
    listWindow = std::vector<Tab *>();
    listWindow.push_back(pBaseTab);
}

Player::Player(QString Name, int _score, int _unitPerSecond, int _nbWindow, std::vector<Tab *> _ListWindow)
{
    name = Name;
    score = _score;
    unitPerSecond = _unitPerSecond;
    nbWindow = _nbWindow;
    listWindow = _ListWindow;
    currentWindowIndex = 0;
}

Player::~Player(){
    for (Tab * ptab : listWindow){
        delete ptab;
    }
}

void Player::addScore(const int addedScore){
    if (addedScore < 0){
        throw new std::invalid_argument("the added score should be strictly positive");
    }
    score += addedScore;
}

void Player::removeScore(const int removedScore){
    qDebug()<<score;
        qDebug()<<removedScore;
    if (score < removedScore){
        throw new std::invalid_argument("the removed score should be lower than the current one");
    }
    if (removedScore <= 0 ){
         throw new std::invalid_argument("the removed score should be strictly positive");
    }


    score -= removedScore;
    if (score < 0) score = 0;
}

int Player::getScore(){
    return score;
}

Tab * Player::getCurrentWindow(){
    return listWindow[currentWindowIndex];
}

void Player::addUnitsPerSecond(const int addedScore){
    if (addedScore < 0){
        throw new std::invalid_argument("the added score should be positive");
    }
    unitPerSecond += addedScore;
}

int Player::getWindowPrice(){
    return static_cast<int>(1000 + 100*pow(nbWindow,3));
}

int Player::getNbWindow(){
    return nbWindow;
}

int  Player::addListWindow(Tab * tab){
    listWindow.push_back(tab);
    return ++nbWindow;
}

void Player::setCurrentWindowIndex(const int newIndex){
    if (newIndex>nbWindow-1 || newIndex<0){
        throw new std::invalid_argument("the index should be in [0;nbWindow[ ");
    }
    currentWindowIndex = newIndex;
}

std::vector<Tab *> Player::getWindows(){
    return listWindow;
}

void Player::setName(const QString & Name){
    name = Name;
}

QString Player::getName(){
    return name;
}

int Player::getUPS(){
    return unitPerSecond;
}

void Player::AddItem(Item *pitem){
    unitPerSecond += getCurrentWindow()->AddItem(pitem);
}

void Player::AddUpgrade(Upgrade *pupgrade){
    unitPerSecond += getCurrentWindow()->AddUpgrade(pupgrade);
}
