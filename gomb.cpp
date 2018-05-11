#include "widget_szabalyzo.hpp"
#include "gomb.hpp"
#include "graphics.hpp"
#include "widget_kijelzo.hpp"

using namespace genv;
using namespace std;

gomb::gomb(int x_, int y_, int hossz_, int vastagsag_,int keret_, widget_kijelzo *kotve_):widget_szabalyzo(x_,y_,hossz_,vastagsag_,keret_,kotve_)
{
}
void gomb::rajzol()
{
}
void gomb::szabalyoz(event ev,widget_kijelzo &kij)
{
}
