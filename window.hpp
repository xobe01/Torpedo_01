#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED
#include <vector>
#include "widget_kijelzo.hpp"
#include "widget_szabalyzo.hpp"

using namespace std;

class window
{
protected:
    vector <widget_szabalyzo*> szabalyzok;
    vector <widget_kijelzo*> kijelzok;
public:
    window();
};

#endif // WINDOW_HPP_INCLUDED
