#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED
#include <vector>
#include "widget.hpp"

using namespace std;

class window
{
protected:
    vector <widget*> widgets;
public:
    window();
};

#endif // WINDOW_HPP_INCLUDED
