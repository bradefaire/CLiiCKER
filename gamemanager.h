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
    bool BuyItem(const QString & itemName);
    bool BuyUpgrade(const QString & upgradeName);
    bool BuyTab();
};

#endif // GAMEMANAGER_H
