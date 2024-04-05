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
    std::function<int(const int)> priceFunction_;

public:
    int Price(const int) const;
    bool isUnlocked() const;
    QString & getDescription();
    QString & getName();
    int getBonus() const;

    void Unlock();

    void operator=(const Upgrade &);

    Upgrade(const QString &, const QString &, const int, const std::function<int(const int)>);
    ~Upgrade() = default;
};

#endif // UPGRADE_H
