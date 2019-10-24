/*****************************************************************************
 Yihsiang Liow
 Copyright
 ****************************************************************************/

/*****************************************************************************

This header file contains the header files for all the SDL related 
simplification layer.

This header file also contains some useful inline functions derived from SDL.

*****************************************************************************/
#ifndef INCLUDES_H
#define INCLUDES_H

#include "SDL.h"
#include "Surface.h"
#include "SingletonSurface.h"
#include "Event.h"
#include "Image.h"
#include "Rect.h"
#include "Color.h"
#include "Sound.h"
#include "Font.h"
#include "FontImage.h"
#include "Stars.h"
#include "Usership.h"
#include "Aliens.h"
#include "Lasers.h"


inline int getTicks()
{
	return SDL_GetTicks();
}

inline void delay(int t)
{
	SDL_Delay(t);
}

typedef Uint8* KeyPressed;

inline KeyPressed get_keypressed()
{
	return SDL_GetKeyState( NULL );
}

#endif
