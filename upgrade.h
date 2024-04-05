#ifndef UPGRADE_H
#define UPGRADE_H

#include <QString>

class Upgrade
{
private:
    QString description_;
    QString name_;
    int bonus_;
    std::function<int(const int)> priceFunction_;

public:
    int Price(const int) const;
    QString & getDescription();
    QString & getName();
    int getBonus() const;

    Upgrade(const QString &, const QString &, const int, const std::function<int(const int)>);
    ~Upgrade() = default;
};

#endif // UPGRADE_H
