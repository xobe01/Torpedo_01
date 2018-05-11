#ifndef GOMB_HPP_INCLUDED
#define GOMB_HPP_INCLUDED

#include "widget_szabalyzo.hpp"
#include "widget_kijelzo.hpp"

using namespace genv;

class gomb : public widget_szabalyzo
{
public:

    gomb(int x_, int y_, int hossz_, int vastagsag_,int keret_, widget_kijelzo *kotve_);
    virtual void rajzol();
    virtual void szabalyoz(event ev, widget_kijelzo &kij);
};

#endif // GOMB_HPP_INCLUDED
