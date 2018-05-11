#include "widget.hpp"
#include "graphics.hpp"
#include "graphics.hpp"

using namespace genv;

widget::widget(int x_, int y_, int side_,int frame_) : x(x_), y(y_), side(side_), frame(frame_)
{
}
bool widget::isSelected(int xMouse, int yMouse)
{
    return xMouse>x && xMouse<x+side && yMouse>y && yMouse<y+side;
}
