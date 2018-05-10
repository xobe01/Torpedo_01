#include "widget_szabalyzo.hpp"
#include "widget_kijelzo.hpp"
#include "graphics.hpp"
using namespace genv;

widget_szabalyzo::widget_szabalyzo(int x_, int y_, int hossz_, int vastagsag_,int keret_, widget_kijelzo *kotve_) : x(x_), y(y_), hossz(hossz_), vastagsag(vastagsag_), keret(keret_), kotve(kotve_)
{
}
bool widget_szabalyzo::kivalasztva(int eger_x, int eger_y)
{
    return eger_x>x && eger_x<x+hossz && eger_y>y && eger_y<y+vastagsag;
}
widget_kijelzo *widget_szabalyzo::get_kotve()
{
    return kotve;
}
