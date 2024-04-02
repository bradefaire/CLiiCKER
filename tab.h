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

    int AddItem(Item * pitem);//return the amount of UPS gained
    int AddUpgrade(Upgrade * pupgrade);//return the amount of UPS gained

    Tab(const QString & name, int UPS, int UPC);
    Tab(const QString & name, std::vector<Item *> items, std::vector<Upgrade *> upgrades);
};

#endif // TAB_H
