#ifndef STARS_H
#define STARS_H

#include <cstdlib>
#include "Includes.h"

class StarTiny
{
public:
    StarTiny()
        : x(rand() % 640), y(rand() % 480), r(1), red(255), grn(255), blu(255)
    {}

    void move();
    void draw(Surface &);

    int x;
    int y;
    int r;

    int red;
    int grn;
    int blu;
};

class StarSmall
{
public:
    StarSmall()
        : x(rand() % 640), y(rand() % 480), r(1), red(255), grn(255), blu(255)
    {}

    ~StarSmall(){}

    void move();
    void draw(Surface &);
    
    int x;
    int y;
    int r;

    int red;
    int grn;
    int blu;
};


class StarMedium
{
public:
    StarMedium()
        : x(rand() % 640), y(rand() % 480), r(3), red(255), grn(255), 
        blu(220), dx(0.0), dy(-1.0)
    {}

    ~StarMedium(){}

    void move();
    void draw(Surface &);
    
    double x;
    double y;
    int r;
    char direction;
    double dx;
    double dy;

    int red;
    int grn;
    int blu;
};

#endif

