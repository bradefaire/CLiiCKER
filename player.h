#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <vector>

#include "stats.h"
#include "tab.h"

class Player
{
public:
    Player();
    Player(QString name);
    Player(QString name, //Value
           int score,
           int unitPerSecond,
           int nbWindow ,
           std::vector<Tab *> ListWindow);
private:
    QString name;
    int score;
    int unitPerSecond;
    int nbWindow;
    std::vector<Tab *> listWindow;
    int currentWindowIndex;
    Stats statPlayer;
public :
    void addScore(const int score);
    void removeScore(const int score);
    int getScore();
    void addUnitsPerSecond(const int score);
    int getWindowPrice(int nbWindow);
    int addListWindow(Tab * tab);
    Tab * getCurrentWindow();
    void setCurrentWindowIndex(const int newIndex);
    int getNbWindow();

};


#endif // PLAYER_H
