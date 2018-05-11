#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include "graphics.hpp"
#include "button.hpp"

class field : public button
{
public:
    field(int x_, int y_, int side_,int frame_);
    virtual void action(event ev);
    virtual void draw(int enemyValue);
};
#endif // FIELD_HPP_INCLUDED
