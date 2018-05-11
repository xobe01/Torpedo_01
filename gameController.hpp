#ifndef GAMECONTROLLER_HPP_INCLUDED
#define GAMECONTROLLER_HPP_INCLUDED
#include <vector>

using namespace std;

class gameController
{
protected:
    vector <int> playerFieldStatus;
    vector <int> enemyFieldStatus;
    vector <vector<int>> enemyShipStatus;
    int N;
public:
    gameController(int N_);
    virtual bool hit(int i);
    virtual int getEnemyValue(int i);
    virtual int getPlayerValue(int i);
    virtual void placingEnemyShips();
    virtual bool whichSank(int i);
    virtual vector<vector<int>> getShipNumber();
};

#endif // GAMECONTROLLER_HPP_INCLUDED
