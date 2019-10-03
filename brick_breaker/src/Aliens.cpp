#include "Aliens.h"
#include <iostream>
#include "Includes.h"
#include <cmath>


void Alien::moveLeft(Rect & rect, int x_values[])
{
    if (!this->attacking && !this->returning)
    {
        x -= 2;
        rect.x -= 2;
    }

    else
    {
        //std::cout << type << ' ' << rect_num << ' ' << attacking << '\n';
    }

    // for (int i = 0; i < 36; ++i)
    // {
    //     x_values[i] -= 2;
    // }
}


void Alien::moveRight(Rect & rect, int x_values[])
{
    if (!this->attacking && !this->returning)
    {
        x += 2;
        rect.x += 2;
    }

    else
    {
        //std::cout << type << ' ' << rect_num << '\n';
    }

    // for (int i = 0; i < 36; ++i)
    // {
    //     x_values[i] += 2;
    // }
}


void Alien::attack(Rect & rect)
{
    //attacking = true;
    y += 2;
    rect.y = y;
    // add in sine curve movement
}


void Alien::return_alien(Rect & rect, int old_y, int old_x, bool & at_home,
                         int x_values[], int j)
{
    if (y != old_y)
    {
        y += 1;
        rect.y += 1;
    }

    if (x > x_values[j])
    {
        if (type == 'r' || type == 'f')
        {
            x -= 3;
            rect.x -= 3;
        }
        else
        {
            x -= 2;
            rect.x -= 2;
        }
        // if (type == 'r' || type == 'f')
        // {
        //     x -= 3;
        // }
    }

    if (x < x_values[j])
    {
        if (type == 'r' || type == 'f')
        {
            x += 3;
            rect.x += 3;
        }
        else
        {
            x += 2;
            rect.x += 2;
        }
        // if (type == 'r' || type == 'f')
        // {
        //     x += 3;
        // }
    }


    

    if (y == old_y + 1 || y == old_y - 1 || y == old_y && x == x_values[j])
    {
        at_home = true;
        returning = false;
        attacking = false;
    }
}
