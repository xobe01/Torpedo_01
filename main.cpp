#include "graphics.hpp"
#include "window.hpp"
#include "field.hpp"
#include "gameController.hpp"
#include <vector>
#include "ship.hpp"
#include <iostream>
#include <cmath>

using namespace genv;
using namespace std;

const int XX=950;
const int YY=600;

void background()
{
    gout<<move_to(0,0)<<color(0,0,0)<<box(XX,YY);
}

class myWindow : public window
{
protected:
    gameController* controller=new gameController(100);
public:
    myWindow()
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                field* f = new field(50+j*40,150+i*40,40,2);
                playerFields.push_back(f);
            }
        }
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                field* f = new field(500+j*40,150+i*40,40,2);
                enemyFields.push_back(f);
            }
        }
        ship* staticShip_01 = new ship(50,100,40,5,3,0);
        staticShips.push_back(staticShip_01);
        ship* staticShip_02 = new ship(210,100,40,5,3,0);
        staticShips.push_back(staticShip_02);
        ship* staticShip_03 = new ship(370,100,40,5,2,0);
        staticShips.push_back(staticShip_03);
        ship* staticShip_04 = new ship(50,50,40,5,4,0);
        staticShips.push_back(staticShip_04);
        ship* staticShip_05 = new ship(250,50,40,5,5,0);
        staticShips.push_back(staticShip_05);
    }
    void event_loop()
    {
        controller->placingEnemyShips();
        for(int i=0;i<controller->getShipNumber().size();i++)
        {
            ship* enemyShip = new ship(500+controller->getShipNumber()[i][2]%10*40,150+controller->getShipNumber()[i][2]/10*40,40,5,controller->getShipNumber()[i][0],controller->getShipNumber()[i][1]);
            enemyShips.push_back(enemyShip);
        }
        event ev;
        bool startGame=false;
        int direction=0;
        int length=0;
        int number=0;
        bool canPlace=false;
        int whichShip=0;
        bool playersTurn=true;
        bool endGame=false;
        while(gin >> ev && ev.keycode!=key_escape)
        {
            background();
            if(!startGame)
            {
                if(ev.button==btn_right)
                {
                    direction=abs(direction-1);
                }
                if(ev.button==btn_left)
                {
                    for(int i=0; i<playerShips.size();i++)
                    {
                        if(playerShips[i]->isSelected(ev.pos_x,ev.pos_y) && !canPlace)
                        {
                            length=playerShips[i]->getLength();
                            canPlace=true;
                            whichShip=i;
                            number--;
                            playerShips[i]=playerShips[playerShips.size()-1];
                            playerShips.pop_back();
                        }
                    }
                    for(int i=0;i<staticShips.size();i++)
                    {
                        if(staticShips[i]->isSelected(ev.pos_x,ev.pos_y) && !controller->isPlaced(i))
                        {
                            for(int j=0;j<staticShips.size();j++)
                            {
                                staticShips[j]->dontBeSelected();
                            }
                             staticShips[i]->beSelected();
                             length=staticShips[i]->getLength();
                             canPlace=true;
                             whichShip=i;
                        }
                    }
                    for(int i=0;i<playerFields.size();i++)
                    {
                        if(playerFields[i]->isSelected(ev.pos_x,ev.pos_y) && controller->placingPlayerShips(whichShip,i,direction,length,true) && canPlace)
                        {
                            ship *playerShip=new ship(50+i%10*40,150+i/10*40,40,5,length,direction);
                            playerShips.push_back(playerShip);
                            number++;
                            direction=0;
                            length=0;
                            canPlace=false;
                            controller->place(whichShip);
                        }
                    }
                }
                for(int i=0;i<playerShips.size();i++)
                {
                    playerShips[i]->draw();
                }
                if(number==5)
                {
                    startGame=true;
                }
            }
            else
            {
                if(!endGame)
                {
                    if(playersTurn)
                    {
                        if(ev.button==btn_left)
                        {
                            for(int i=0;i<enemyFields.size();i++)
                            {
                                if(enemyFields[i]->isSelected(ev.pos_x,ev.pos_y) && controller->isGoodTarget(i,true))
                                {
                                    controller->hit(i,true);
                                    playersTurn=false;
                                }
                            }
                        }
                    }
                    else
                    {
                        controller->AI();
                        playersTurn=true;
                    }
                    int playerScore=0;
                    for(int i=0;i<enemyShips.size();i++)
                    {
                        if(controller->whichSank(i,false))
                        {
                            playerScore++;
                        }
                    }
                    int enemyScore=0;
                    for(int i=0;i<playerShips.size();i++)
                    {
                        if(controller->whichSank(i,true))
                        {
                            enemyScore++;
                        }
                    }
                    if(playerScore==enemyShips.size())
                    {
                        endGame=true;
                    }
                    else if(enemyScore==playerShips.size())
                    {
                        endGame=true;
                    }
                }
            }
            for(int i=0;i<enemyFields.size();i++)
            {
                enemyFields[i]->draw();
            }
            for(int i=0;i<enemyShips.size();i++)
            {
                if(controller->whichSank(i,false))
                {
                    enemyShips[i]->draw();
                }
            }
            for(int i=0;i<enemyFields.size();i++)
            {
                enemyFields[i]->drawAction(controller->getEnemyValue()[i]);
            }
            for(int i=0;i<playerFields.size();i++)
            {
                playerFields[i]->draw();
            }
            for(int i=0;i<staticShips.size();i++)
            {
                if(!controller->isPlaced(i))
                {
                    staticShips[i]->draw();
                }
            }
            for(int i=0;i<playerShips.size();i++)
            {
                playerShips[i]->draw();
            }
            for(int i=0;i<playerFields.size();i++)
            {
                playerFields[i]->drawAction(controller->getPlayerValue()[i]);
            }
            if(canPlace)
            {
                for(int i=0;i<playerFields.size();i++)
                {
                    if(playerFields[i]->isSelected(ev.pos_x,ev.pos_y) && controller->placingPlayerShips(0,i,direction,length,false))
                    {
                        ship* visual=new ship(playerFields[i]->getX(),playerFields[i]->getY(),40,5,length,direction);
                        visual->draw();
                        delete visual;
                    }
                }
            }
            gout<<refresh;
        }
    }
};

int main()
{
    gout.open(XX,YY);
    myWindow *win=new myWindow;
    win->event_loop();
    return 0;
}
