#include "widget_kijelzo.hpp"
#include "graphics.hpp"
using namespace genv;

widget_kijelzo::widget_kijelzo(int x_, int y_, int hossz_, int vastagsag_,int keret_) : x(x_), y(y_), hossz(hossz_), vastagsag(vastagsag_), keret(keret_)
{
    szoveg="";
}
bool widget_kijelzo::kivalasztva(int eger_x, int eger_y)
{
    return eger_x>x && eger_x<x+hossz && eger_y>y && eger_y<y+vastagsag;
}
bool widget_kijelzo::get_aktivitas()
{
    return aktivitas;
}
std::string widget_kijelzo::get_szoveg()
{
    return szoveg;
}
