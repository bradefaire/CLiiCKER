#ifndef UPGRADE_H
#define UPGRADE_H

#include <QString>

class Upgrade
{
private:
    bool unlocked_;
    QString description_;
    QString name_;
    int bonus_;
    std::function<int(void)> priceFunction_;

public:
    int Price() const;
    bool isUnlocked() const;
    QString & getDescription();
    QString & getName();
    int getBonus() const;

    void Unlock();

    void operator=(const Upgrade &);

    Upgrade(const QString &, const QString &, const int, const std::function<int(void)>);
};

#endif // UPGRADE_H
