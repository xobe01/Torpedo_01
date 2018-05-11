#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include "graphics.hpp"
#include "widget.hpp"
#include <functional>

using namespace genv;

class button : public widget
{
public:

    button(int x_, int y_, int side_,int frame_);
    virtual void draw(int i)=0;
    virtual void action(event ev);
};

#endif // BUTTON_HPP_INCLUDED
