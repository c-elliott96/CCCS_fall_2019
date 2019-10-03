#include "Stars.h"
#include "Surface.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


void StarTiny::move()
{
    if (y <= 480)
    {
        y += 1;
    }
    else
    {
        x = rand() % 640;
        y = 0;
    }      
}


void StarTiny::draw(Surface & surface)
{
    surface.put_circle(this->x, this->y, this->r, this->red,
                       this->grn, this->blu);
}


void StarSmall::move()
{
    if (y <= 480)
    {
        y += 2;
    }
    else
    {
        x = rand() % 640;
        y = 0;
    }    
  
    return;
}


void StarSmall::draw(Surface & surface)
{
    surface.put_circle(this->x, this->y, this->r, this->red,
                       this->grn, this->blu);
}


void StarMedium::move()
{
    if (y <= 480)
    {
        y += 4;
    }
    else
    {
        x = rand() % 640;
        y = 0;
    }
  
    return;
}


void StarMedium::draw(Surface & surface)
{
    surface.put_circle(this->x, this->y, this->r, this->red,
                       this->grn, this->blu);
}

