#ifndef ALIENS_H
#define ALIENS_H

#include "Includes.h"

// class for alien ships
// what do they need? x, y, state

// class for each individual alien

// order from bottom to top: aqua, purple, red, yellow

class Alien
{
public: Alien()
        : x(0), y(0), alive(true), attacking(false), shooting(false),
        returning(false)
    {}

    void moveLeft(Rect & rect, int []);
    void moveRight(Rect & rect, int []);
    void attack(Rect &);
    void return_alien(Rect &, int, int, bool &, int [], int);
    
    int x, y;
    bool alive;
    bool attacking;
    bool shooting;
    bool returning;
    char type;
    int rect_num;
};


class Aqua: public Alien
{
public:
    /* Aqua() */
    /*     : x(0), y(0), dx(3), dy(0) */
    /* {} */
    /* int x; */
    /* int y; */
    /* int dx; */
    /* int dy; */


};


class Flagship: public Alien
{
public:
    /* Flagship() */
    /*     : x(0), y(0), dx(3), dy(0), alive(true) */
    /* {} */
    /* int x; */
    /* int y; */
    /* int dx; */
    /* int dy; */

    /* bool alive; */

};


class Purple: public Alien
{
public:
/*     Purple() */
/*         : x(0), y(0), dx(3), dy(0) */
/*     {} */
/*     int x; */
/*     int y; */
/*     int dx; */
/*     int dy; */
};


class Red: public Alien
{
public:
    /* Red() */
    /*     : x(0), y(0), dx(3), dy(0) */
    /* {} */
    /* int x; */
    /* int y; */
    /* int dx; */
    /* int dy; */

};

#endif


