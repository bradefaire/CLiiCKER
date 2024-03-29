#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

#include "stats.h"

struct Window{
    int unitsPerSecond;
    Window(){
        unitsPerSecond = 2;
    }
};

class Player
{
public:
    Player(); //copy
    Player(QString name);
    Player(QString name, int score, int unitPerSecond, int nbWindow , std::vector<Window> ListWindow);//Value
private:
    QString name;
    int score;
    int unitPerSecond;
    int nbWindow;
    std::vector<Window> listWindow;
    Stats statPlayer;
public :
    void addScore(const int & score);
    void addUnitPerSecond(const int & score);
    int getWindowPrice(int nbWindow);
    int addListWindow(const Window & window);
};


#endif // PLAYER_H
