#include "graphics.hpp"
#include "window.hpp"
#include <vector>

using namespace genv;
using namespace std;

const int XX=1000;
const int YY=600;
const int Square=400;

void background()
{
    gout<<move_to(90,180)<<color(0,150,255)<<box(Square,Square);
    gout<<move_to(510,180)<<color(0,150,255)<<box(Square,Square);
}
class gameController
{
protected:
    vector<int>playerFieldStatus();
    vector<int>enemyFieldStatus();
public:
    gameController()
    {
        playerFieldStatus=new vector<int>();
        enemyFieldStatus()=new vector<int>();
    }
    //0 - empty, untouched field
    //1 - ship placed, untouched field
    //2 - empty, already hit field
    //3 - ship placed, already hit field
    bool hit(int i)
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
};
class myWindow : public window
{
public:
    myWindow()
    {

    }
    void event_loop()
    {
        event ev;
        while(gin >> ev)
        {
            background();
            for(widget_kijelzo* kij : kijelzok)
            {
                kij->mukodtet(ev);
                kij->rajzol();
            }
            for(widget_szabalyzo* szab : szabalyzok)
            {
                szab->szabalyoz(ev,*szab->get_kotve());
                szab->rajzol();
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
