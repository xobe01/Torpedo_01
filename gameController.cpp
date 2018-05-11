#include "gameController.hpp"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

gameController::gameController(int N_):N(N_)
{
    vector <vector<int>>ships(4);
    vector<int>vec(N,0);
    enemyFieldStatus=vec;
    playerFieldStatus=vec;
    enemyShipStatus=ships;
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
void gameController::placingEnemyShips()
{
    srand(time(NULL));
    for(int j=0;j<4;j++)
    {
        int length=j+2;
        bool done=false;
        while(!done)
        {
            int first=rand()%N;
            int direction=rand()%2;
            //direction 0 - horizontal
            //direction 1 - vertical
            if(direction==0 && (first+length-1)%10>=length-1)
            {
                bool fieldIsEmpty=true;
                for(int i=0;i<length;i++)
                {
                    if(enemyFieldStatus[first+i]!=0)
                    {
                        fieldIsEmpty=false;
                    }
                }
                if(fieldIsEmpty)
                {
                    enemyShipStatus[j].push_back(length);
                    enemyShipStatus[j].push_back(direction);
                    for(int i=0;i<length;i++)
                    {
                        enemyFieldStatus[first+i]=1;
                        enemyShipStatus[j].push_back(first+i);
                    }
                    done=true;
                }
            }
            if(direction==1 && first<N-length*10)
            {
                bool fieldIsEmpty=true;
                for(int i=0;i<length;i++)
                {
                    if(enemyFieldStatus[first+i*10]!=0)
                    {
                        fieldIsEmpty=false;
                    }
                }
                if(fieldIsEmpty)
                {
                    enemyShipStatus[j].push_back(length);
                    enemyShipStatus[j].push_back(direction);
                    for(int i=0;i<length;i++)
                    {
                        enemyFieldStatus[first+i*10]=1;
                        enemyShipStatus[j].push_back(first+i*10);
                    }
                    done=true;
                }
            }
        }
    }
}
bool gameController::whichSank(int i)
{
    bool isSunk=true;
    for (int j=2;j<enemyShipStatus[i].size();j++)
    {
        if(enemyFieldStatus[enemyShipStatus[i][j]]==1)
        {
            isSunk=false;
        }
    }
    return isSunk;
}
vector<vector<int>> gameController::getShipNumber()
{
    //1. element - length
    //2. element - direction
    //others - coordinates
    return enemyShipStatus;
}
