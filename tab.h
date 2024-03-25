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

    void AddItem(Item * pitem);
    void AddUpgrade(Upgrade * pupgrade);

    Tab(QString & name, int UPS, int UPC);
};

#endif // TAB_H
