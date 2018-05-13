#include "graphics.hpp"
#include "window.hpp"
#include "field.hpp"
#include "gameController.hpp"
#include <vector>
#include "ship.hpp"
#include <cmath>
#include "staticText.hpp"
#include <time.h>

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

        staticText *text_esc=new staticText(20,20,0,0,"Press 'Esc' to exit");
        staticTexts.push_back(text_esc);
        staticText *text_your=new staticText(210,580,0,0,"Your board");
        staticTexts.push_back(text_your);
        staticText *text_enemys=new staticText(640,580,0,0,"Enemy's board");
        staticTexts.push_back(text_enemys);
        staticText *text_01=new staticText(500,35,0,0,"1. Select a ship: left click on the ship");
        staticTexts.push_back(text_01);
        staticText *text_02=new staticText(500,75,0,0,"2. Rotate the ship: right click");
        staticTexts.push_back(text_02);
        staticText *text_03=new staticText(500,115,0,0,"3. Place the ship: left click on your board");
        staticTexts.push_back(text_03);
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
        int kesleltet;
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
                    for(int i=0;i<3;i++)
                    {
                        staticTexts.pop_back();
                    }
                    staticText *text_01=new staticText(500,35,0,0,"1. Shoot: left click on the enemy's board");
                    staticTexts.push_back(text_01);
                    staticText *text_02=new staticText(500,75,0,0,"2. If your shot hits it's your turn again");
                    staticTexts.push_back(text_02);
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
                                    if(!controller->hit(i,true))
                                    {
                                        playersTurn=false;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        kesleltet=time(NULL);
                        while(time(NULL)-kesleltet<1){}
                        if(!controller->hit(controller->AI(),false))
                        {
                            playersTurn=true;
                        }
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
                        staticTexts.pop_back();
                        staticTexts.pop_back();
                        staticText *text_02=new staticText(425,75,0,0,"YOU WIN!");
                        staticTexts.push_back(text_02);
                    }
                    else if(enemyScore==playerShips.size())
                    {
                        endGame=true;
                        staticTexts.pop_back();
                        staticTexts.pop_back();
                        staticText *text_02=new staticText(425,75,0,0,"YOU LOSE :(");
                        staticTexts.push_back(text_02);
                    }
                }
            }
            for(int i=0;i<enemyFields.size();i++)
            {
                enemyFields[i]->draw();
            }
            for(int i=0;i<enemyShips.size();i++)
            {
                if(controller->whichSank(i,false) || endGame)
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
            for(int i=0;i<staticTexts.size();i++)
            {
                staticTexts[i]->draw();
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
