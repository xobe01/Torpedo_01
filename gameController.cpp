#include "gameController.hpp"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

gameController::gameController(int N_):N(N_)
{
    vector <vector<int>>ships(5);
    vector<int>fields(N,0);
    vector<bool>place(5,false);
    enemyFieldStatus=fields;
    playerFieldStatus=fields;
    enemyShipStatus=ships;
    playerShipStatus=ships;
    placed=place;
}
    //0 - empty, untouched field
    //1 - ship placed, untouched field
    //2 - empty, already hit field
    //3 - ship placed, already hit field
bool gameController::hit(int i,bool isPlayerTurn)
{
    if(isPlayerTurn)
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
    else
    {
        if(playerFieldStatus[i]==0)
        {
            playerFieldStatus[i]=2 ;
            return true;
        }
        if(playerFieldStatus[i]==1)
        {
            playerFieldStatus[i]=3;
            return true;
        }
        else
        {
            return false;
        }
    }
}
vector <int> gameController::getEnemyValue()
{
    return enemyFieldStatus;
}
vector <int> gameController::getPlayerValue()
{
    return playerFieldStatus;
}
bool gameController::placingPlayerShips(int i,int first, int direction, int length)
{
    //direction 0 - horizontal
    //direction 1 - vertical
    if(direction==0 && (first+length-1)%10>=length-1)
    {
        bool fieldIsEmpty=true;
        for(int i=0;i<length;i++)
        {
            if(playerFieldStatus[first+i]!=0)
            {
                fieldIsEmpty=false;
            }
        }
        if(fieldIsEmpty)
        {
            playerShipStatus[i].push_back(length);
            playerShipStatus[i].push_back(direction);
            for(int i=0;i<length;i++)
            {
                playerFieldStatus[first+i]=1;
                playerShipStatus[i].push_back(first+i);
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    if(direction==1 && first<N-length*10)
    {
        bool fieldIsEmpty=true;
        for(int i=0;i<length;i++)
        {
            if(playerFieldStatus[first+i*10]!=0)
            {
                fieldIsEmpty=false;
            }
        }
        if(fieldIsEmpty)
        {
            playerShipStatus[i].push_back(length);
            playerShipStatus[i].push_back(direction);
            for(int i=0;i<length;i++)
            {
                playerFieldStatus[first+i*10]=1;
                playerShipStatus[i].push_back(first+i*10);
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}
void gameController::placingEnemyShips()
{
    srand(time(NULL));
    for(int j=0;j<5;j++)
    {
        int length=j+2;
        if(j>1)
        {
            length--;
        }
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
bool gameController::whichSank(int i, bool isPlayer)
{
    if(isPlayer)
    {
        bool isSunk=true;
        for (int j=2;j<playerShipStatus[i].size();j++)
        {
            if(playerFieldStatus[playerShipStatus[i][j]]==1)
            {
                isSunk=false;
            }
        }
        return isSunk;
    }
    else
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
}
vector<vector<int>> gameController::getShipNumber()
{
    //1. element - length
    //2. element - direction
    //others - coordinates
    return enemyShipStatus;
}
void gameController::place(int i)
{
    placed[i]=true;
}
bool gameController::isPlaced(int i)
{
    return placed[i];
}
void gameController::AI()
{
    bool hasTarget=false;
    for(int i=0;i<playerShipStatus.size();i++)
    {
        bool isOne=false;
        bool isZero=false;
        for(int j=2;j<playerShipStatus[i].size();j++)
        {
            if(playerShipStatus[i][j]==0)
            {
                isZero=true;
            }
            if(playerShipStatus[i][j]==1)
            {
                isOne=true;
            }
        }
        if(isZero && isOne)
        {
            hasTarget=true;
            break;
        }
    }
    int target;
    bool done=false;
    while(!done)
    {
        if(!hasTarget)
        {
            target=rand()%N;
            if(hit(target,false))
            {
                done=true;
            }
        }
        else
        {
            target=rand()%N;
            if(hit(target,false))
            {
                done=true;
            }
        }
    }
}
