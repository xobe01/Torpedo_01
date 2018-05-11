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
    vector <vector<int>> playerShipStatus;
    vector <bool> placed;
    int N;
public:
    gameController(int N_);
    virtual bool hit(int i);
    virtual int getEnemyValue(int i);
    virtual int getPlayerValue(int i);
    virtual void placingEnemyShips();
    virtual bool placingPlayerShips(int i,int first, int direction, int length);
    virtual bool whichSank(int i);
    virtual vector<vector<int>> getShipNumber();
    virtual void place(int i);
    virtual bool isPlaced(int i);
    virtual void AI();
};

#endif // GAMECONTROLLER_HPP_INCLUDED
