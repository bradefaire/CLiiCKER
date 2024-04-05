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
    Player(const QString & Name);
    Player(const QString & Name,Tab * pBaseTab);
    Player(QString Name, //Value
           int _score,
           int _unitPerSecond,
           int _nbWindow ,
           std::vector<Tab *> _ListWindow);
    ~Player();
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
    int getWindowPrice();
    int addListWindow(Tab * tab);
    Tab * getCurrentWindow();
    void setCurrentWindowIndex(const int newIndex);
    int getNbWindow();
    std::vector<Tab *> getWindows();
    void setName(const QString & Name);
    QString getName();
    int getUPS();
    void AddItem(Item * pitem);
    void AddUpgrade(Upgrade * pupgrade);

};


#endif // PLAYER_H
