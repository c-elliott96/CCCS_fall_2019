#ifndef USERSHIP_H
#define USERSHIP_H

#include "Includes.h"

class Usership
{
public:
    Usership()
        : x(0), y(0), dx(3), dy(0), alive(true)
    {}
    int x;
    int y;
    int dx;
    int dy;

    bool alive;
};


#endif

