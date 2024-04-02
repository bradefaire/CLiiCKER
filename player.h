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
    Player(QString Name);
    Player(QString Name, //Value
           int _score,
           int _unitPerSecond,
           int _nbWindow ,
           std::vector<Tab *> _ListWindow);
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
    std::vector<Tab *> getWindows();
    void setName(const QString & Name);
    QString getName();
    int getUPS();

};


#endif // PLAYER_H
