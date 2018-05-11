#include "gameController.hpp"
#include <vector>

using namespace std;

gameController::gameController(int N)
{
    vector<int>vec(N,0);
    enemyFieldStatus=vec;
    playerFieldStatus=vec;
}
    //0 - empty, untouched field
    //1 - ship placed, untouched field
    //2 - empty, already hit field
    //3 - ship placed, already hit field
bool gameController::hit(int i)
{
        if(enemyFieldStatus[i]==0)
        {
            enemyFieldStatus[i]=2 ;
            return true;
        }
        if(enemyFieldStatus[i]==1)
        {
            enemyFieldStatus[i]=3;
            return true;
        }
        else
        {
            return false;
        }
}
int gameController::getEnemyValue(int i)
{
    return enemyFieldStatus[i];
}
int gameController::getPlayerValue(int i)
{
    return playerFieldStatus[i];
}
