#ifndef WIDGET_SZABALYZO_HPP_INCLUDED
#define WIDGET_SZABALYZO_HPP_INCLUDED

#include "widget_kijelzo.hpp"
#include "graphics.hpp"

class widget_szabalyzo {
protected:
    int x, y, hossz, vastagsag, keret;
    widget_kijelzo *kotve;
public:
    widget_szabalyzo(int x_, int y_, int hossz_, int vastagsag_,int keret_, widget_kijelzo *kotve_);
    virtual bool kivalasztva(int eger_x, int eger_y);
    virtual void rajzol() = 0;
    virtual void szabalyoz(genv::event ev,widget_kijelzo &kij) =0;
    virtual widget_kijelzo *get_kotve();
};

#endif // WIDGET_SZABALYZO_HPP_INCLUDED
