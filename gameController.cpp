#include "gameController.hpp"
#include <vector>
#include <time.h>
#include <stdlib.h>

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
    //2 - empty, already field
    //3 - ship placed, already hit field
bool gameController::hit(int i,bool isPlayerTurn)
{
    if(isPlayerTurn)
    {
        if(enemyFieldStatus[i]==0)
        {
            enemyFieldStatus[i]=2;
            return false;
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
            playerFieldStatus[i]=2;
            return false;
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
bool gameController::isGoodTarget(int i,bool isPlayerTurn)
{
    if(i>N || i<0)
    {
        return false;
    }
    else
    {
        if(isPlayerTurn)
        {
            if(enemyFieldStatus[i]==0)
            {
                return true;
            }
            else if(enemyFieldStatus[i]==1)
            {
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
                return true;
            }
            else if(playerFieldStatus[i]==1)
            {
                return true;
            }
            else
            {
                return false;
            }
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
bool gameController::placingPlayerShips(int shipNumber,int first, int direction, int length,bool isShip)
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
            if(isShip)
            {
                playerShipStatus[shipNumber].push_back(length);
                playerShipStatus[shipNumber].push_back(direction);
                for(int i=0;i<length;i++)
                {
                    playerFieldStatus[first+i]=1;
                    playerShipStatus[shipNumber].push_back(first+i);
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(direction==1 && first<N-(length-1)*10)
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
            if(isShip)
            {
                playerShipStatus[shipNumber].push_back(length);
            playerShipStatus[shipNumber].push_back(direction);
            for(int i=0;i<length;i++)
            {
                playerFieldStatus[first+i*10]=1;
                playerShipStatus[shipNumber].push_back(first+i*10);
            }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
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
            else if(direction==1 && first<N-(length-1)*10)
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
int gameController::AI()
{
    int shortestShip=6;
    for(int i=0;i<playerShipStatus.size();i++)
    {
        if(!whichSank(i,true) && playerShipStatus[i][0]<shortestShip)
        {
            shortestShip=playerShipStatus[i][0];
        }
    }
    int target;
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
    bool done=false;
    bool checkArea;
    bool randomTarget=false;
    while(!done)
    {
        checkArea=false;
        if(targets.size()==0)
        {
            target=rand()%N;
            if(isGoodTarget(target,false))
            {
                checkArea=true;
            }
        }
        else if(targets.size()==1)
        {
            randomTarget=true;
        }
        else if(targets.size()>1 && !randomTarget)
        {
            int i=0;
            while(i<targets.size() && !checkArea )
            {
                int j=0;
                while(j<targets.size() && !checkArea)
                {
                    if(targets[i]-targets[j]==10 && targets[i]/10>1)
                    {
                            if(isGoodTarget(targets[j]-10,false))
                        {
                            target=targets[j]-10;
                            checkArea=true;
                        }
                    }
                    else if(targets[i]-targets[j]==-10 && targets[i]/10<8)
                    {
                        if(isGoodTarget(targets[j]+10,false))
                        {
                            target=targets[j]+10;
                            checkArea=true;
                        }
                    }
                    else if(targets[i]-targets[j]==1 && targets[i]%10>1)
                    {
                            if(isGoodTarget(targets[j]-1,false))
                        {
                            target=targets[j]-1;
                            checkArea=true;
                        }
                    }
                    else if(targets[i]-targets[j]==-1 && targets[i]%10<8)
                    {
                        if(isGoodTarget(targets[j]+1,false))
                        {
                            target=targets[j]+1;
                            checkArea=true;
                        }
                    }
                    j++;
                }
                i++;
            }
            if(!checkArea)
            {
                randomTarget=true;
            }
        }
        if(randomTarget)
        {
            target=targets[rand()%targets.size()];
            if(target%10!=0 && isGoodTarget(target-1,false))
            {
                    target--;
                checkArea=true;
            }
            else if(target%10!=9 && isGoodTarget(target+1,false))
            {
                target++;
                checkArea=true;
            }
            else if(target/10!=0 && isGoodTarget(target-10,false))
            {
                target-=10;
                checkArea=true;
            }
            else if(target/10!=9 && isGoodTarget(target+10,false))
                {
                target+=10;
                checkArea=true;
            }
        }
        if(checkArea)
        {
            int counter=1;
            int i=1;
            bool isGoodField=true;
            while(isGoodField)
            {
                bool isTarget=false;
                for(int j=0;j<targets.size();j++)
                {
                    if(targets[j]==target+i)
                    {
                        isTarget=true;
                    }
                }
                if((isGoodTarget(target+i,false) || isTarget) && (target+i)%10!=0)
                {
                    counter++;
                    i++;
                }
                else
                {
                    isGoodField=false;
                }
            }
            i=1;
            isGoodField=true;
            while(isGoodField)
            {
                bool isTarget=false;
                for(int j=0;j<targets.size();j++)
                {
                    if(targets[j]==target-i)
                    {
                        isTarget=true;
                    }
                }
                if((isGoodTarget(target-i,false) || isTarget) && (target-i)%10!=9)
                {
                    counter++;
                    i++;
                }
                else
                {
                    isGoodField=false;
                }
            }
            if(counter>=shortestShip)
            {
                done=true;
            }
            else
            {
                counter=1;
                i=1;
                isGoodField=true;
                while(isGoodField)
                {
                    bool isTarget=false;
                    for(int j=0;j<targets.size();j++)
                    {
                        if(targets[j]==target+i*10)
                        {
                            isTarget=true;
                        }
                    }
                    if((isGoodTarget(target+i*10,false) || isTarget) && (target+i*10)/10<=9)
                    {
                        counter++;
                        i++;
                    }
                    else
                    {
                        isGoodField=false;
                    }
                }
                i=1;
                isGoodField=true;
                while(isGoodField)
                {
                    bool isTarget=false;
                    for(int j=0;j<targets.size();j++)
                    {
                        if(targets[j]==target-i*10)
                        {
                            isTarget=true;
                        }
                    }
                    if((isGoodTarget(target-i*10,false) || playerFieldStatus[target-i*10]==3) && (target-i*10)/10>=0)
                    {
                        counter++;
                        i++;
                    }
                    else
                    {
                        isGoodField=false;
                    }
                }
                if(counter>=shortestShip)
                {
                    done=true;
                }
            }
        }
    }
    return target;
}
