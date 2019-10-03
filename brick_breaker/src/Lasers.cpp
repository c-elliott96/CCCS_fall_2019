#include "Lasers.h"
#include <iostream>
#include "Includes.h"

void UserLaser::draw(Surface & surface)
{
    surface.put_rect(this->x, this->y, this->w, this->h,
                     255, 0, 0);
}


void UserLaser::move(Rect & laserRect)
{
    if (y <= 480)
    {
        y -= 4;
    }

    laserRect.x = x;
    laserRect.y = y;
}

void TestLaser::draw(Surface & surface)
{
    surface.put_rect(this->x, this->y, this->w, this->h,
                     255, 0, 0);
}


void TestLaser::move()
{
    if (y <= 480)
    {
        y -= 4;
    }
}


// Rect& Rect::operator=(const TestLaser& laser)
// {
//     x = laser.x;
//     y = laser.y;
//     w = laser.w;

//     return *this;
// }
