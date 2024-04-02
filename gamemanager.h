#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "upgrade.h"
#include "tab.h"
#include "item.h"
#include "vector"

class GameManager
{
private:
    std::vector<Upgrade *> upgrades_;
    std::vector<Item *> items_;
    Player * pplayer_;

public:
    GameManager();
    bool BuyItem(const QString & itemName);
    bool BuyUpgrade(const QString & upgradeName);
    bool BuyTab(const QString & newName);
    void ButtonPressed();
    void Update(const int deltaTime);
    void ChangeTab(const int tabIndex);

    void SaveGame();
    void LoadGame();
    void NewGame();
};

#endif // GAMEMANAGER_H
