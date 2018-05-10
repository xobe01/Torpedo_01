#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

using namespace genv;

class Field : public gomb
{
public:

    gomb(int x_, int y_, int hossz_, int vastagsag_,int keret_, widget_kijelzo *kotve_);
    virtual void rajzol();
    virtual void szabalyoz(event ev, widget_kijelzo &kij);
};

#endif // FIELD_HPP_INCLUDED
