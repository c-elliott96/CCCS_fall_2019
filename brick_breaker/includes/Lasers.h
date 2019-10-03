#ifndef LASERS_H
#define LASERS_H

#include "Includes.h"

// class AlienLaser
// {
// public:
//     AlienLaser()
//         : 
//     void get_laser();
//     void draw_laser();
// };


class UserLaser
{
public:
    UserLaser()
        : x(0), y(0), w(3), h(8), r(255), g(0), b(0), shooting(false),
        alive(true)
    {}
    
    /* void get_laser(); */
    void draw(Surface &);
    void move(Rect &);

    bool shooting;
    bool alive;
    int x, y, w, h, r, g, b;
};

class TestLaser
{
public:
    TestLaser()
        : x(0), y(0), w(3), h(8), r(255), g(0), b(0), shooting(false)
    {}


    void draw(Surface &);
    void move();
    bool shooting;
    int x, y, w, h, r, g, b;
};

#endif

