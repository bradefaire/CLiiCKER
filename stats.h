#ifndef STATS_H
#define STATS_H

#include <QDateTime>
#include <QTime>

class Stats
{
public:
    Stats();
    Stats(int totalCicks, int totalEarned);
private:
    int totalCicks;
    int totalEarned;
    int totalSpent;
    QTime totalTime;
    QDateTime startDate;
};

#endif // STATS_H
