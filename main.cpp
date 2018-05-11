#include "graphics.hpp"
#include "window.hpp"
#include "field.hpp"
#include "gameController.hpp"
#include <vector>
#include "ship.hpp"

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
        ship* playerShip_01 = new ship(50,100,40,2,3);
        playerShips.push_back(playerShip_01);
        ship* playerShip_02 = new ship(210,100,40,2,3);
        playerShips.push_back(playerShip_02);
        ship* playerShip_03 = new ship(370,100,40,2,2);
        playerShips.push_back(playerShip_03);
        ship* playerShip_04 = new ship(50,50,40,2,4);
        playerShips.push_back(playerShip_04);
        ship* playerShip_05 = new ship(250,50,40,2,5);
        playerShips.push_back(playerShip_05);
    }
    void event_loop()
    {
        event ev;
        while(gin >> ev)
        {
            for(int i=0;i<enemyFields.size();i++)
            {
                if(ev.button==btn_left)
                {
                    if(enemyFields[i]->isSelected(ev.pos_x,ev.pos_y))
                    {
                        controller->hit(i);
                    }
                }
                enemyFields[i]->draw(controller->getEnemyValue(i));
            }
            for(int i=0;i<playerFields.size();i++)
            {
                playerFields[i]->draw(controller->getPlayerValue(i));
            }
            for(int i=0;i<playerShips.size();i++)
            {
                playerShips[i]->draw(1);
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
