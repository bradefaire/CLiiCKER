#ifndef TAB_H
#define TAB_H

#include <QString>
#include <map>

#include "item.h"
#include "upgrade.h"

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

    int AddItem(Item * pitem);//return the amount of UPS gained
    int AddUpgrade(Upgrade * pupgrade);//return the amount of UPS gained

    Tab(QString & name, int UPS, int UPC);
};

#endif // TAB_H
