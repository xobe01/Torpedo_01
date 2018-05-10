#ifndef GAMECONTROLLER_HPP_INCLUDED
#define GAMECONTROLLER_HPP_INCLUDED
#include <vector>

using namespace std;

class gameController
{
protected:
    vector<int>playerFieldStatus;
    vector<int>enemyFieldStatus;
public:
    gameController(vector<int>playerFieldStatus_,vector<int>enemyFieldStatus_);
    virtual bool hit(int i);
};

#endif // GAMECONTROLLER_HPP_INCLUDED
