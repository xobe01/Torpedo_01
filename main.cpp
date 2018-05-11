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
        ship* staticShip_01 = new ship(50,100,40,2,3,0);
        staticShips.push_back(staticShip_01);
        ship* staticShip_02 = new ship(210,100,40,2,3,0);
        staticShips.push_back(staticShip_02);
        ship* staticShip_03 = new ship(370,100,40,2,2,0);
        staticShips.push_back(staticShip_03);
        ship* staticShip_04 = new ship(50,50,40,2,4,0);
        staticShips.push_back(staticShip_04);
        ship* staticShip_05 = new ship(250,50,40,2,5,0);
        staticShips.push_back(staticShip_05);
    }
    void event_loop()
    {
        controller->placingEnemyShips();
        for(int i=0;i<controller->getShipNumber().size();i++)
        {
            ship* enemyShip = new ship(500+controller->getShipNumber()[i][2]%10*40,150+controller->getShipNumber()[i][2]/10*40,40,2,controller->getShipNumber()[i][0],controller->getShipNumber()[i][1]);
            enemyShips.push_back(enemyShip);
        }
        event ev;
        bool startGame=false;
        int direction=0;
        int length=0;
        int number=0;
        bool canPlace=false;
        int whichShip=0;
        while(gin >> ev)
        {
            if(!startGame)
            {
                if(ev.button==btn_right)
                {
                    direction=abs(direction-1);
                }
                if(ev.button==btn_left)
                {
                    for(int i=0;i<staticShips.size();i++)
                    {
                        if(staticShips[i]->isSelected(ev.pos_x,ev.pos_y) && !controller->isPlaced(i))
                        {
                             length=staticShips[i]->getLength();
                             canPlace=true;
                             whichShip=i;
                        }
                    }
                    for(int i=0;i<playerFields.size();i++)
                    {
                        if(playerFields[i]->isSelected(ev.pos_x,ev.pos_y) && controller->placingPlayerShips(number,i,direction,length) && canPlace)
                        {
                            ship *staticShip=new ship(50+i%10*40,150+i/10*40,40,2,length,direction);
                            playerShips.push_back(staticShip);
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
                    playerShips[i]->draw(true);
                }
                if(number==5)
                {
                    startGame=true;
                }
            }
            else
            {
                for(int i=0;i<enemyShips.size();i++)
                {
                    enemyShips[i]->draw(controller->whichSank(i));
                }
                for(int i=0;i<enemyFields.size();i++)
                {
                    if(ev.button==btn_left && enemyFields[i]->isSelected(ev.pos_x,ev.pos_y))
                    {
                        controller->hit(i);
                    }
                }
            }
            for(int i=0;i<enemyFields.size();i++)
            {
                enemyFields[i]->draw(controller->getEnemyValue(i));
            }
            for(int i=0;i<playerFields.size();i++)
            {
                playerFields[i]->draw(controller->getPlayerValue(i));
            }
            for(int i=0;i<staticShips.size();i++)
            {
                staticShips[i]->draw(true);
            }
            for(int i=0;i<playerShips.size();i++)
            {
                playerShips[i]->draw(true);
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
