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
        else if(enemyFieldStatus[i]==1)
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
        else if(playerFieldStatus[i]==1)
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
bool gameController::placingPlayerShips(int shipNumber,int first, int direction, int length)
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
            playerShipStatus[shipNumber].push_back(length);
            playerShipStatus[shipNumber].push_back(direction);
            for(int i=0;i<length;i++)
            {
                playerFieldStatus[first+i]=1;
                playerShipStatus[shipNumber].push_back(first+i);
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(direction==1 && first<N-length*10)
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
            playerShipStatus[shipNumber].push_back(length);
            playerShipStatus[shipNumber].push_back(direction);
            for(int i=0;i<length;i++)
            {
                playerFieldStatus[first+i*10]=1;
                playerShipStatus[shipNumber].push_back(first+i*10);
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
            else if(direction==1 && first<N-length*10)
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
    int target;
    bool hasTarget=false;
    vector <int> targets;
    for(int i=0;i<playerShipStatus.size();i++)
    {
        bool isOne=false;
        bool isThree=false;
        for(int j=2;j<playerShipStatus[i].size();j++)
        {
            if(playerFieldStatus[playerShipStatus[i][j]]==3)
            {
                isThree=true;
            }
            else if(playerFieldStatus[playerShipStatus[i][j]]==1)
            {
                isOne=true;
            }
        }
        if(isThree && isOne)
        {
            for(int j=2;j<playerShipStatus[i].size();j++)
            {
                if(playerFieldStatus[playerShipStatus[i][j]]==3)
                {
                    targets.push_back(playerShipStatus[i][j]);
                }
            }
        }
    }
    if(targets.size()!=0)
    {
        hasTarget=true;
    }
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
            target=targets[rand()%targets.size()];
            //0 - Left
            //1 - Right
            //2 - Up
            //3 - Down
            int i=0;
            while(i!=4)
            {
                int direction=rand()%4;
                if(direction==0 && target%10!=0 && hit(target-1,false))
                {
                    done=true;
                    i=4;
                }
                else if(direction==1 && target%10!=9 && hit(target+1,false))
                {
                    done=true;
                    i=4;
                }
                else if(direction==2 && target/10!=0 && hit(target-10,false))
                {
                    done=true;
                    i=4;
                }
                else if(direction==3 && target/10!=9 && hit(target+10,false))
                {
                    done=true;
                    i=4;
                }
                else
                {
                    i++;
                }
            }
        }
    }
    /*for(int i=0;i<10;i++)
    {
        for (int j=0;j<10;j++)
        {
            cout<<playerFieldStatus[i*10+j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;*/
    for(int i=0;i<playerShipStatus.size();i++)
    {
        for(int j=0;j<playerShipStatus[i].size();j++)
        {
            cout<<playerShipStatus[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=0;i<enemyShipStatus.size();i++)
    {
        for(int j=0;j<enemyShipStatus[i].size();j++)
        {
            cout<<enemyShipStatus[i][j]<<" ";
        }
        cout<<endl;
    }
    /*cout<<endl;
    for(int i=0;i<targets.size();i++)
    {
        cout<<targets[i]<<" ";
    }
    cout<<endl;*/
}
