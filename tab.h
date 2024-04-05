#ifndef TAB_H
#define TAB_H

#include <QString>
#include <map>

#include "item.h"
#include "upgrade.h"
#include "vector"

class Tab
{
private:
    QString name_;
    int unitsPerSecond_;
    int unitsPerClick_;

    std::map<Item *,int> items_;// the item, and their quantity in this tab
    std::map<Upgrade *, int> upgrades_;// the different upgrades and their level in this tab

public:
    QString & getName();
    int getUPS();
    int getUPC();
    Upgrade * getUpgrade(const QString & itemName);
    Item * getItem(const QString & upgradeName);
    int getUpgradeLevel(Upgrade * pupgrade);
    int getItemQuantity(Item * pitem);
    std::map<Item *,int> getItems();
    std::map<Upgrade *,int> getUpgrades();

    int AddItem(Item * pitem, const int amount=1);//return the amount of UPS gained
    int AddUpgrade(Upgrade * pupgrade, const int amount=1);//return the amount of UPS gained

    Tab(const QString & name, const int UPS, const int UPC);
    Tab(const QString & name, std::vector<Item *> items,const int UPC=1);
    ~Tab() = default;
};

#endif // TAB_H
