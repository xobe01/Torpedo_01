#include "ship.hpp"
#include "graphics.hpp"
#include "widget.hpp"

using namespace genv;
using namespace std;

ship::ship(int x_, int y_, int side_, int frame_,int length_,int direction_):widget(x_,y_,side_, frame_),length(length_),direction(direction_)
{
}
void ship::draw(int visible)
{
    if(visible==1)
    {
        if(direction==0)
        {
            gout<<move_to(x,y)<<color(100,100,100)<<box(side*length,side)<<move_to(x+frame,y+frame)<<color(200,200,200)<<box(side*length-2*frame,side-2*frame);
        }
        else
        {
            gout<<move_to(x,y)<<color(100,100,100)<<box(side,side*length)<<move_to(x+frame,y+frame)<<color(200,200,200)<<box(side-2*frame,side*length-2*frame);
        }
    }
}
void ship::action(event ev)
{
}
