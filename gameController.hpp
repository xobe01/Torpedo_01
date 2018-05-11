#ifndef GAMECONTROLLER_HPP_INCLUDED
#define GAMECONTROLLER_HPP_INCLUDED
#include <vector>

using namespace std;

class gameController
{
protected:
    vector <int> playerFieldStatus;
    vector <int> enemyFieldStatus;
    vector <int> enemyShipStatus;
public:
    gameController(int N);
    virtual bool hit(int i);
    virtual int getEnemyValue(int i);
    virtual int getPlayerValue(int i);
};

#endif // GAMECONTROLLER_HPP_INCLUDED
