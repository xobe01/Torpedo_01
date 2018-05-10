#ifndef WIDGET_KIJELZO_HPP_INCLUDED
#define WIDGET_KIJELZO_HPP_INCLUDED

#include "graphics.hpp"

class widget_kijelzo {
protected:
    int x, y, hossz, vastagsag,keret;
    bool aktivitas;
    std::string szoveg;
public:
    widget_kijelzo(int x_, int y_, int hossz_, int vastagsag_,int keret_);
    virtual bool kivalasztva(int eger_x, int eger_y);
    virtual void rajzol() = 0;
    virtual void aktival() =0;
    virtual void deaktival() = 0 ;
    virtual void csokkent()=0;
    virtual void novel()=0;
    virtual void mukodtet(genv::event ev)=0;
    virtual bool get_aktivitas();
    virtual std::string get_szoveg();
    virtual void add(std::string extra)=0;
    virtual void elvesz()=0;
    virtual void hozzaad(std::string valami)=0;

};

#endif // WIDGET_KIJELZO_HPP_INCLUDED
