#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "upgrade.h"
#include "tab.h"
#include "item.h"
#include "vector"

class GameManager
{
public:
    std::vector<Upgrade *> upgrades_;
    std::vector<Item *> items_;
    Player * pplayer_;
    int accumulatedScore_;

public slots:
    void Update(const int deltaTime);

public:
    GameManager();
    bool BuyItem(const QString & itemName);
    bool BuyUpgrade(const QString & upgradeName);
    bool BuyTab(const QString & newName);
    void ButtonPressed();
    void ChangeTab(const int tabIndex);

    void SaveGame(const QString & filename);
    void LoadGame(const QString & filename);
    void NewGame(const QString &);
    int getScore();
};

#endif // GAMEMANAGER_H
