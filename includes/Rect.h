
/*****************************************************************************
 Yihsiang Liow
 Copyright
 *****************************************************************************/
#ifndef RECT_H
#define RECT_H

#include <iostream>

class Rect
{
public:
	Rect(int x0 = 0, int y0 = 0, int w0 = 0, int h0 = 0)
		: x(x0), y(y0), w(w0), h(h0)
	{}
    Rect( const SDL_Rect & r)
		: x(r.x), y(r.y), w(r.w), h(r.h)
	{}
	SDL_Rect getSDL_Rect()
	{
		SDL_Rect r = {Sint16(x), Sint16(y), Uint16(w), Uint16(h)};
		return r;
	}
	int x, y, w, h;

    bool collidesWithLaser(Rect & alien)
    {
        if ((x <= alien.x + alien.w && x >= alien.x - alien.w) &&
            (y <= alien.y + alien.h && y >= alien.y - alien.h))
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    bool collidesWithAlien(Rect & alien)
    {
        if (x <= alien.x + alien.w &&
            x + w >= alien.x - alien.w &&
            y <= alien.y + alien.h &&
            y + h >= alien.y - alien.h)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    
        // need another collision for two ships (i.e. alien and usership)
};

inline std::ostream & operator<<(std::ostream & cout, const Rect & r)
{
	cout << "(" << r.x << "," << r.y << "," << r.w << "," << r.h << ")";
	return cout;
}



/* Rect& Rect::operator=(const TestLaser& laser) */
/* { */
/*     x = laser.x; */
/*     y = laser.y; */
/*     w = laser.w; */

/*     return *this; */
/* } */

#endif
