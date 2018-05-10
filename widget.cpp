#include "widget.hpp"
#include "graphics.hpp"
#include "graphics.hpp"

using namespace genv;

widget::widget(int x_, int y_, int xSize_, int ySize_,int frame_) : x(x_), y(y_), xSize(xSize_), ySize(ySize_), frame(frame_)
{
}
bool widget::isSelected(int xMouse, int yMouse)
{
    return xMouse>x && xMouse<x+xSize && yMouse>y && yMouse<y+ySize;
}
