#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include "graphics.hpp"
#include "widget.hpp"
#include <functional>

using namespace genv;

class button : public widget
{
protected:
    std::function<void()> functor;
public:

    button(int x_, int y_, int xSize_,int ySize_,int frame_);
    virtual void draw();
    virtual void action(event ev);
};

#endif // BUTTON_HPP_INCLUDED
