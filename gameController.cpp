#include "gameController.hpp"
#include <vector>

using namespace std;

gameController::gameController(vector<int>playerFieldStatus_,vector<int>enemyFieldStatus_):playerFieldStatus(playerFieldStatus_),enemyFieldStatus(enemyFieldStatus_)
{
}
    //0 - empty, untouched field
    //1 - ship placed, untouched field
    //2 - empty, already hit field
    //3 - ship placed, already hit field
bool gameController::hit(int i)
{
     if(enemyFieldStatus[i]==0)
        {
            enemyFieldStatus[i]=2;
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
