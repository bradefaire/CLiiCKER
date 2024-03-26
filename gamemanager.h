#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "upgrade.h"
#include "tab.h"
#include "item.h"

class GameManager
{
private:
    Upgrade** upgrades_;
    Item** items_;
    Player * pplayer_;

public:
    GameManager();
    void BuyItem(const int);//Item index
    void BuyUpgrade(const int);//Upgrade index
    void BuyTab();
};

#endif // GAMEMANAGER_H
