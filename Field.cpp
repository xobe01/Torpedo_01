#include "field.hpp"
#include "button.hpp"
#include "graphics.hpp"
#include "widget.hpp"
#include <cmath>

using namespace genv;
using namespace std;

field::field(int x_, int y_, int side_, int frame_):button(x_,y_,side_, frame_)
{
}
void field::draw(int enemyValue)
{
    if(enemyValue==0 || enemyValue==1)
    {
        gout<<move_to(x,y)<<color(255,255,255)<<box(side,side)<<move_to(x+frame,y+frame)<<color(0,150,255)<<box(side-2*frame,side-2*frame);
    }
    if(enemyValue==2)
    {
        gout<<move_to(x,y)<<color(255,255,255)<<box(side,side)<<move_to(x+frame,y+frame)<<color(0,150,255)<<box(side-2*frame,side-2*frame);
        gout<<move_to(x+frame,y+frame)<<color(255,0,255)<<line_to(x+side-1-frame,y+side-1-frame)<<move_to(x+side-1-frame,y+frame)<<line_to(x+frame,y+side-1-frame);
        gout<<move_to(x+1+frame,y+frame)<<color(255,0,255)<<line_to(x+side-1-frame,y+side-1-1-frame)<<move_to(x-1+side-1-frame,y+frame)<<line_to(x+frame,y+side-1-1-frame);
        gout<<move_to(x+frame,y+1+frame)<<color(255,0,255)<<line_to(x+side-1-1-frame,y+side-1-frame)<<move_to(x+side-1-frame,y+1+frame)<<line_to(x+1+frame,y+side-1-frame);
    }
    if(enemyValue==3)
    {
        gout<<move_to(x,y)<<color(255,255,255)<<box(side,side)<<move_to(x+frame,y+frame)<<color(0,150,255)<<box(side-2*frame,side-2*frame);
        float xCenter=x+side/2;
        float yCenter=y+side/2;
        float R = side/2-5;
        float r = side/2-10;
        float r_2=side/2-15;
        for(int i=0;i<side;i++)
        {
            for(int j=0;j<side;j++)
            {
                float d = sqrt(pow(xCenter-(x+j),2)+pow(yCenter-(y+i),2));
                if(d<=R && d>=r || d<=r_2)
                {
                    gout<<move_to(x+j,y+i)<<color(255,0,0)<<dot;
                }
                else
                {
                    //gout<<move_to(x+j,y+i)<<color(255,0,0)<<dot;
                }
            }
        }
    }
}
void field::action(event ev)
{
}
