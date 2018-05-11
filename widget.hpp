#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED
#include "graphics.hpp"

class widget {
protected:
    int x, y, side,frame;

public:
    widget(int x_, int y_, int side_,int frame_);
    virtual bool isSelected(int xMouse, int yMouse);
    virtual void draw(int i)=0;
    virtual void action(genv::event ev)=0;
};
#endif // WIDGET_HPP_INCLUDED
