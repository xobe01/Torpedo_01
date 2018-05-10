#include "graphics.hpp"
#include "window.hpp"
#include "field.hpp"
#include "gameController.hpp"
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
            for(widget* wid : widgets)
            {
                wid->action(ev);
                wid->draw();
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
