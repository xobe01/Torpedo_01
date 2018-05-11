#ifndef SHIP_HPP_INCLUDED
#define SHIP_HPP_INCLUDED

#include "widget.hpp"

class ship : public widget
{
protected:
    int direction;
    int length;
public:
    ship(int x_,int y_, int side_,int frame_,int length_);
    virtual void draw(int visible);
    virtual void action(genv::event ev);
};

#endif // SHIP_HPP_INCLUDED
