/****************************************************************************
 Yihsiang Liow
 Copyright
 ****************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include <stdio.h>

/*****************************************************************************
This is a short introduction to graphics, animation, sound, music, keyboard
control. Together with software development techniques, you can develop any
2d game. 

C/C++ does not have language features for game development. One would have to
look for 3rd party extension. The tools (functions, etc.) you are using is
developed by me on top of a 3rd party extension called SDL, an industrial
strength tool for game development. 

I've developed this only for this class. You are free to use this for any 
personal game development.

The setup of programs using this game development tool is complex if you have
never done it before. Furthermore the process has nothing to do with learning
to program or problem solving. Therefore instead of setting up a new project 
on your own, you should simply make a *copy* of this project when you need a 
new one.
*****************************************************************************/


/*****************************************************************************
MS .NET STUDIO

You can quickly find "identifiers" (i.e. names of variables, functions, etc.) 
using MS .NET Studio. Look at your "Class View" side bar. It should be close 
to your Solution Explorer. 

Using the "Class View" look for main().
*****************************************************************************/


/*****************************************************************************
An Event object that has access to user input such as "user close program",
"user presses a key", etc.

An *object* is like a variable but there are some differences. One big 
difference is that whereas an integer variable has an integer value, an object 
actually *contains* other variables and even functions! That's why you see 
things like

	event.poll()	// returns true if the user caused an event to occur

and

	event.type()	// returns the type of event caused by the user

In this function, event is an Event variable and in event there are two 
functions: poll() and type(). 

The delay() function will yield CPU time to other programs. This will give
other programs time to run. Otherwise this program will take up all the CPU,
making the computer unresponsive. You might have problems closing this program
if you don't yield some time.
*****************************************************************************/
void test_event()
{
    Surface surface(W, H);	// W = 640, H = 480 are constants. This creates
    // a drawing surface of size W-by-H

    Event event; // event is an Event object. It's used to process user
                 // events such as mouse clicks, key presses, etc.
    while (1)
    {
        // This statement basically breaks out of the while-loop if the user
        // closes the program. You can treat this as a blackbox. In more
        // details, the program breaks out of the while loop if the
        // event object detects a user event (example: mouse click) and the
        // type of the event is to close the program.
        if (event.poll() && event.type() == QUIT) break;

        delay(100); // yield 100 milliseconds to other programs
    }

    // If the program reaches this point, then the user must have closed
    // the program. At this point, the program executes "return" which
    // causes the program goes back to where it came from.
    return;
}

void fancyhelloworld()
{
    Surface surface(W, H);
    Sound sound("sounds/laser.wav");
    Music music("sounds/GameLoop.ogg");
    music.play();
    Event event;

    Font font("fonts/FreeSans.ttf", 48);
    Image image(font.render("hello world", WHITE));
    Rect rect = image.getRect();

    int r = 0;
    int g = 0;
    int b = 255;
    int dr = 1;
    int dg = 2;
    int db = 3;
    Color c = {0, 100, 200};

    int dx = 2;
    int dy = 3;

    //sound.off();
    //music.off();
    int RATE = 1000 / 60;

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        int start = getTicks();

        r += dr;
        if (r < 0)
        {
            r = 0;
            dr = - dr;
        }
        else if (r > 255)
        {
            r = 255;
            dr = -dr;
        }

        g += dg;
        if (g < 0)
        {
            g = 0;
            dg = - dg;
        }
        else if (g > 255)
        {
            g = 255;
            dg = -dg;
        }

        db += db;
        if (b < 0)
        {
            b = 0;
            db = -db;
        }
        else if (b > 255)
        {
            b = 255;
            db = -db;
        }
        Color c = {Uint8(r), Uint8(g), Uint8(b)};
        Image image(font.render("hello world", c));

        rect.x += dx;
        if (rect.x < 0)
        {
            sound.play();
            rect.x = 0;
            dx = -dx;
        }
        else if (rect.x + rect.w > W - 1)
        {
            sound.play();
            rect.x = W - 1 - rect.w;
            dx = -dx;
        }

        rect.y += dy;
        if (rect.y < 0)
        {
            sound.play();
            rect.y = 0;
            dy = -dy;
        }
        else if (rect.y + rect.h > H - 1)
        {
            sound.play();
            rect.y = H - 1 - rect.h;
            dy = -dy;
        }

        surface.lock();
        surface.fill(BLACK);
        surface.put_image(image, rect);
        surface.unlock();
        surface.flip();

        int end = getTicks();
        int dt = RATE - end + start;
        if (dt > 0) delay(dt);
    }
    return;
}


/*****************************************************************************
This function show you how to draw a pixel (basically a dot on the screen).
First you have a create a Surface object (ours is called surface). To draw a
pixel at (x,y) with color r,g,b (r, g, b intensities) you do this:

	surface.put_pixel(x, y, r, g, b);

The color intensities r, g, b ranges from 0 to 255.

Exercise: r,g,b are 255,255,255 which is white (correct?). Modify this program
to draw pixels with random color.

Another thing to note is that in the while-loop, before you draw anything, you 
have to lock the surface using surface.lock() and after you've drawn 
everything, you need to unlock and flip the surface.

One thing to note that is that on the computer screen, the x-axis grows to
the right BUT the y-axis grows *downward*.

  0123456789 ...
 +-----------------------------
0|p
1|    r
2|
3| q
4|

p has x = 0, y = 0
q has x = 1, y = 3
r has x = 4, y = 1

WARNING: 
Another thing to note is that if you have a screen of width W, the maximum x
value you can use for drawing a pixel is W - 1. Likewise if the height if H,
the maximum y value is H - 1.

Exercise. Modify the program so that it draw random pixels (x,y) where x and y
are between 0 and 200.
*****************************************************************************/
void test_pixel()
{
    Surface surface(W, H);	// Create surface of width W and height H 
                                // for drawing
    Event event;

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        int x = rand() % W;
        int y = rand() % H;
        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;

        surface.lock();
        surface.put_pixel(x, y, r, g, b);
        surface.unlock();
        //surface.update_rect(x, y, 1, 1);
        surface.flip();
		
        delay(2);
    }
    return;
}


/*****************************************************************************
This function, test_line(), shows you how to draw a line:

	surface.put_line(x0, y0, x1, y1, r, g, b);

This draws a line on the surface from (x0,y0) to (x1,y1) with color r,g,b.

Note that I've performed by computation of x0,y0,x1,y1 before I lock the 
surface. In general, the gap between locking and unlocking the surface should
be as small as possible.

Exercise. Modify the program to draw random lines with *random* color.
*****************************************************************************/
void test_line()
{
    Surface surface(W, H);
    Event event;
    
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        
        // Computation part
        int x0 = rand() % W;
        int y0 = rand() % H;
        int x1 = rand() % W;
        int y1 = rand() % H;
        
        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;
        
        // Drawing part: minimize the gap between lock and unlock
        surface.lock();
        surface.put_line(x0, y0, x1, y1, r, g, b);
        surface.unlock();
        surface.flip();
        
        delay(10);
    }
    return;
}


/*****************************************************************************
This function, test_circle(), shows you how to draw a circle:

surface.put_circle(x, y, rad, r, g, b);

This draws a circle on surface with center at (x,y), radius r, and with random
color.

Exercise. Modify the program to draw circles with radius 10.
*****************************************************************************/
void test_circle()
{
    Surface surface(W, H);
    Event event;
    
    
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        
        int x = rand() % W;
        int y = rand() % H;
        int r = rand() % 100 + 10;
        
        surface.lock();
        surface.put_circle(x, y, r, rand() % 256, rand() % 256 , rand() % 256);
        surface.unlock();
        surface.flip();
        
        delay(10);
    }
    return;
}

void test_unfilled_circle()
{
    Surface surface(W, H);
    Event event;

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        int x = rand() % W;
        int y = rand() % H;
        int r = rand() % 100 + 10;

        surface.lock();
        surface.put_unfilled_circle(x, y, r, rand() % 256, rand() % 256 , rand() % 256);
        surface.unlock();
        surface.flip();

        delay(10);
    }
    return;
}


void test_star()
{
    Surface surface(W, H);
    Event event;

    srand((unsigned int) time(NULL));
    

    StarSmall star;
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        if (star.y <= 480) { star.y += 1; }

        else { star.y = 0; }
        //StarSmall *star = new StarSmall;
        surface.lock();
        surface.fill(BLACK);
        //surface.put_circle(star->x, star->y, star->r, star->red, star->grn, star->blu);
        surface.put_circle(star.x, star.y, star.r, star.red, star.grn, star.blu);
        surface.unlock();
        surface.flip();

        delay(20);
    }

    return;
}


void test_print_stars()
{
    Surface surface(W, H);
    Event event;

    srand((unsigned int) time(NULL));

    StarSmall * starSmall[15];
    StarMedium * starMedium[10];
    
    // init star object arrays

    for (int i = 0; i < 15; ++i)
    {
        starSmall[i] = new StarSmall;
    }

    for (int i = 0; i < 10; ++i)
    {
        starMedium[i] = new StarMedium;
    }

    // loop to iterate through star arrays

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->move();
        }

        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->move();
        }
        
        surface.lock();
        surface.fill(BLACK);
        for (int i = 0; i < 15; ++i)
        {
            surface.put_circle(starSmall[i]->x, starSmall[i]->y, starSmall[i]->r, starSmall[i]->red,
                               starSmall[i]->grn, starSmall[i]->blu);
            //starSmall[i]->draw(i);
        }
        for (int i = 0; i < 10; ++i)
        {
            surface.put_circle(starMedium[i]->x, starMedium[i]->y, starMedium[i]->r, starMedium[i]->red,
                               starMedium[i]->grn, starMedium[i]->blu);
            //starMedium[i]->draw(i);
        }
        surface.unlock();
        surface.flip();
        
        delay(20);
    }
}


/*****************************************************************************
This function, test_rect(), shows you how to draw a rectangle. The call

surface.put_rect(x, y, w, h, r, g, b);

draw a rectangle on surface with top-right corner (x,y), width w, height h,
and color r,g,b.

For instance the following is a rectangle with top-left corner (2,1), width 4
and height 3.

 0123456789...
 +---------------------
0| 
1| xxxx
2| xxxx
3| xxxx
4|

*****************************************************************************/
void test_rect()
{
    Surface surface(W, H);
    Event event;
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        int x = rand() % (W - 1);
        int y = rand() % (H - 1);
        int w = rand() % (W - 1 - x);
        int h = rand() % (H - 1 - y);

        surface.lock();
        surface.put_rect(x, y, w, h, rand() % 256, rand() % 256 , rand() % 256);
        surface.unlock();
        surface.flip();

        delay(10);
    }
    return;
}




/*****************************************************************************
This function, test_keyboard(), shows you how to check keyboard inputs.

When this function is running, press and release the left arrow key. The 
statement

		KeyPressed keypressed = get_keypressed();

create a KeyPressed variable.

		keypressed[LEFTARROW]

is true exactly when the left arrow key is pressed when you create the
KeyPressed variable keypressed.

Exercise. Change LEFTARROW to RIGHTARROW and run the program again.

Exercise. Try DOWNARROW, UPARROW, and SPACE.

The other keys are for instance SDLK_1 for the 1 key, SDLK_a for the a key,
SDLK_F1 for the F1 key, etc. (Google "SDL SDLK".)
*****************************************************************************/
void test_keyboard()
{
    Surface surface(W, H);
    Event event;

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        KeyPressed keypressed = get_keypressed();
        if (keypressed[LEFTARROW])
        {
            int x = rand() % W;
            int y = rand() % H;
            int rx = min(int(W - 1 - x), int(x));
            int ry = min(H - 1 - y, y);

            surface.lock();
            surface.put_circle(x, y, min(rx, ry), rand() % 256, rand() % 256 , rand() % 255);
            surface.unlock();
            surface.flip();

            delay(10);
        }
        if (keypressed[SPACE])
        {
            int x = rand() % W;
            int y = rand() % H;
            int rx = min(int(W - 1 - x), int(x));
            int ry = min(H - 1 - y, y);

            surface.lock();
            surface.put_circle(x, y, min(rx, ry), 255, 0, 0);
            surface.unlock();
            surface.flip();

            delay(10);
        }
    }
    return;
}

/*****************************************************************************
NEWS: ADDED 3/24/2013

This function, test_key_up_down(), shows you how to check keyboard events.

Note that a Keypressed variable will read the keyboard for the key pressed.
If you hold a key down event for a split second, if your game loop runs fast
enough, you would have processed this key pressed for 50 game loops. There are
times when you really only want to tell the game loop "the key is pressed"
and you want to execute something once. For instance, suppose if your game
allows the player to turn the sound on or off by pressing the S key, then
your game could potentially be turning the sound on and off about 51-100 times
even though the player press and release the S key only once.

(If you do not want to use an Event object to detect a key being pressed
and a key being released and you want to process a key, say S, being pressed
50-100 times, another way to achieve this is to insert a delay of say 1 sec
when you detect S being pressed.)

The way to get around this is to combine the reading of the key being pressed
with an Event objects a key being pressed down and then the key being
released. The Event object can tell you that *some* key is pressed and when
*some* key is released.

The following function shows you how to detect a key press event and a
key release event. The crucial thing to note is that when you press a key
down, the Event object detects *one* key down event (regardless of how long
you hold the key down). For that key that is pressed, when you release the key
is released, the Event object detects *one* key up event. 
*****************************************************************************/
void test_key_up_down()
{
    Surface surface(W, H);
    Event event;

    while (1)
    {
        int key = -1;
        if (event.poll())
        {
            if (event.type() == QUIT) break;
            else if (event.type() == KEYDOWN)
            {
                key = 1;
            }
            else if (event.type() == KEYUP)
            {
                key = 2;
            }
        }


        if (key != -1)
        {
            int x = rand() % W;
            int y = rand() % H;
            int rx = min(int(W - 1 - x), int(x));
            int ry = min(H - 1 - y, y);

            surface.lock();
            switch (key)
            {
                case 1:
                    surface.put_circle(x, y, min(rx, ry), 255, 0, 0);
                    break;
                case 2:
                    surface.put_circle(x, y, min(rx, ry), 0, 255, 0);
                    break;
            }                    
            surface.unlock();
            surface.flip();
        }
        
        delay(10);
    }
    return;
}



/*****************************************************************************
This function, test_image(), shows you how to load and "blit" an image. "Blit"
stands for "block image transfer".

The statement

	Image image("images/galaxian/GalaxianAquaAlien.gif");

creates an Image object, image, from a graphics image file.

The statement 

	Rect rect = image.getRect();

give you a Rect variable (object) with rect.x = 0, rect.y = 0 and rect.w and 
rect.h are the width and height of the image. rect is an object containing
4 variable x, y, w, h. The x in rect is called rect.x; the y in rect is called 
rect.y.

Another function in surface that is helpful is the fill() function.

	surface.fill(BLACK);

will fill the whole surface with BLACK color. This is like clearing the 
whole surface (if your background is black). If your background is red you
can paint the whole surface red like this:

	Color red = {255, 0, 0};
	surface.fill(red);

Exercise. Change the background to your favorite color.

Exercise. Make the alien bug move at twice its speed.

Exercise. Make the alien bug stop when it hits the right wall.

Exercise. Make the alien bug move backward when it hits the right wall.
Hint: Suppose this is the surface and the rect where you want to blit the 
image.

... ------------+
				|
		XXXX	|
		XXXX	|
		        |

The top-left of the rect is rect.x. The top-RIGHT of the rect is rect.x + 
rect.w.

Exercise. Make the alien bug move forward and backward between the left and 
right wall.

Exercise. Make the alien bug move in both the x and y direction within the
surface.
*****************************************************************************/
void test_image()
{
    Surface surface(W, H);
    Event event;

    Image image("images/galaxian/GalaxianAquaAlien.gif");	// loads image

    Rect rect = image.getRect();

    int speed = 5;
    int dx = speed;
    int dy = 0;
    
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        rect.x += dx;
        
        if (rect.x > 400)
        {
            dx = -1;
        }
        else if (rect.x < 0)
        {
            dx = 1;
        }

        if (rect.x + rect.w >= W)
        {
            // CASE: right side of image touches the right side of surface
            dx = -speed;
        }
        else if (rect.x <= 0)
        {
            // CASE: right side of image touches the right side of surface
            dx = speed;
        }
        
        surface.lock();
        surface.fill(BLACK);
        surface.put_image(image, rect); // blit image at rect on surface
        surface.unlock();
        surface.flip();

        delay(20);
    }
    return;
}



void test_spaceship()
{
    Surface surface(W, H);
    Event event;

    Image image("images/galaxian/GalaxianGalaxip.gif");	// loads image

    Rect rect = image.getRect();
    rect.x = 300;
    rect.y = 400;

    int speed = 5;
    int dx = speed;
    int dy = 0;
    
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        rect.x += dx;
        
        if (rect.x > 640)
        {
            dx = -5;
        }
        else if (rect.x < 0)
        {
            dx = 5;
        }

        if (rect.x + rect.w >= W)
        {
            // CASE: right side of image touches the right side of surface
            dx = -speed;
        }
        else if (rect.x <= 0)
        {
            // CASE: right side of image touches the right side of surface
            dx = speed;
        }
        
        surface.lock();
        surface.fill(BLACK);
        surface.put_image(image, rect); // blit image at rect on surface
        surface.unlock();
        surface.flip();

        delay(20);
    }
    return;
}


/*****************************************************************************
This function shows you how to play sound and music.
*****************************************************************************/
void test_sound()
{
    Surface surface(W, H);
    Sound sound("sounds/laser.wav");		// create sound object from file
    Music music("sounds/GameLoop.ogg");		// create music object from file
    music.play();							// loop over music
    Event event;

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        if (rand() < 100) sound.play();		// play sound randomly
        delay(10);
    }
}


/*****************************************************************************
This function, helloworld(), shows you how to create an image from a font
file.

The statement

	Font font("fonts/FreeSans.ttf", 48);

creates a font object. 

The statement following statement creates an image using the font object.

	Color c = {0, 0, 255}; // color with red = 0, green = 0, blue = 255
	Image image(font.render("hello world", c));

You can of course change the string to whatever you need. The color variable
c can also be changed.

Exercise. Print a different message using a different font file, a different
color and a different size.
*****************************************************************************/
void helloworld()
{
    Surface surface(W, H);
    Event event;

    Font font("fonts/FreeMonoBold.ttf", 24);
    Color c = {0, 0, 255};
    Image image(font.render("frodo lives", c));
    Rect rect = image.getRect();

    // Initially rect has x = 0, y = 0
    // Let's move it.
    rect.x = 10;
    rect.y = 10;

    surface.lock();
    surface.put_image(image, rect);
    surface.unlock();
    surface.flip();

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        delay(100);
    }
    return;
}


/*****************************************************************************
To draw a filled polygon, call:

	surface.put_polygon(x, y, n, r, g, b);

where x and y are arrays of int describing the vertices (corners) of the 
polygon and n is the number of corners. The integer values r, g, b is the 
color to use. For instance to draw a red polygon with corners (10, 100), 
(20, 100), (15, 150), (10, 100), you do this:

int x[] = {10, 20, 15, 10};
int y[] = {100, 100, 150, 100};
surface.put_polygon(x, y, 4, 255, 0, 0);

Note that the polygon is filled. To draw the outline of the polygon, you 
should call

int x[] = {10, 20, 15, 10};
int y[] = {100, 100, 150, 100};
surface.put_polygon(x, y, 4, 255, 0, 0, false);

I.e. the last argument specifies whether the polygon should be filled.
*****************************************************************************/
void move(int & x, int & dx, int max)
{
    x += dx;
    if (x < 0)
    {
        x = 0;
        dx = -dx;
    }
    else if (x > max)
    {
        x = max;
        dx = -dx;
    }
}
void test_polygon(bool fill)
{
    Surface surface(640, 480);
    Event event;

    const int n = 500;

    int x[n], dx[n] = {3};
    int y[n], dy[n] = {5};
    int r = rand() % 256; 
    int g = rand() % 256;
    int b = rand() % 256;
    int dr = rand() % 3 + 1;
    int dg = rand() % 3 + 1;
    int db = rand() % 3 + 1;

    for (int i = 0; i < n; i++)
    {
        x[i] = rand() % 640;
        y[i] = rand() % 480;
    }

    for (int i = 1; i < n; i++)
    {
        dx[i] = dx[0];
        dy[i] = dy[0];
    }

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        for (int i = 0; i < n; ++i)
        {
            move(x[i], dx[i], 639);
            move(y[i], dy[i], 479);
        }
        move(r, dr, 255);
        move(g, dg, 255);
        move(b, db, 255);

        surface.lock();
        surface.fill(BLACK);
        surface.put_polygon(x, y, n, r, g, b, fill);
        surface.unlock();
        surface.flip();

        delay(10);
    }
}


/******************************************************************************
  You can read the x,y position of the mouse at any time.
  You can read the state of the mouse buttons at any time.
  - mouse_x(): the x-coordinate of the mouse cursor
  - mouse_y(): the y-coordinate of the mouse cursor
  - mouse_left(): true iff the left mouse button is down
  - mouse_middle(): true iff the middle mouse button is down
  - mouse_right(): true if the right mouse button is down

  Instead of read the x,y, and button states in every single game loop,
  sometimes you can to read them only when the mouse is moved or when the
  button is pressed and released, i.e., when there's a mouse motion
  or mouse button event.
  - event.type() == MOUSEMOTION is true when the mouse is moved
  - event.type() == MOUSEBUTTON is true when a mouse button is pressed or
    released.
 *****************************************************************************/
void test_mouse()
{
    const int FONTSIZE = 24;
    Surface surface(640, 480);
    Event event;
    Font font("fonts/FreeSans.ttf", FONTSIZE);
	
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        std::stringstream out1;
        out1 << "x:" << mouse_x() << " y:" << mouse_y();
        Image image1(font.render(out1.str().c_str(), WHITE));
        Rect rect1 = image1.getRect();

        std::stringstream out2;
        out2 << "leftbutton:" << mouse_left()
             << " middlebutton:" << mouse_middle()
             << " rightbutton:" << mouse_right();
        Image image2(font.render(out2.str().c_str(), WHITE));
        Rect rect2 = image2.getRect();
        rect2.y = FONTSIZE + 5;
        
        surface.lock();
        surface.fill(BLACK);
        surface.put_image(image1, rect1);
        surface.put_image(image2, rect2);
        surface.unlock();
        surface.flip();

        delay(10);
    }
}


/******************************************************************************
  Instead of read the x,y, and button states in every single game loop,
  sometimes you can to read them only when the mouse is moved or when the
  button is pressed or released, i.e., when there's a mouse motion
  or mouse button event. Here's how to check for mouse motion event or mouse
  button pressed/released event:
  - event.type() == MOUSEMOTION is true when the mouse is moved
  - event.type() == MOUSEBUTTONDOWN is true when a mouse button is pressed
  - event.type() == MOUSEBUTTONUP is true when a mouse button is released
  Once the above is true, you execute:

  mouse.update(event);

  and after that you can read the mouse cursor position and the states of the
  mouse buttons when the mouse motion or mouse button press/release occurs
  using these:
  - mouse.x() -  x-coordinate of the mouse cursor
  - mouse.y() - y-coordinate of the mouse cursor
  - mouse.left() - true iff the left mouse button is pressed
  - mouse.middle() - true iff the middle mouse button is pressed
  - mouse.right() - true iff the right mouse button is pressed
 *****************************************************************************/
void test_mouse_event()
{
    const int FONTSIZE = 24;
    Surface surface(640, 480);
    Event event;
    Font font("fonts/FreeSans.ttf", FONTSIZE);
    Mouse mouse;
	
    while (1)
    {
        std::stringstream out;
        if (event.poll())
        { 
            if (event.type() == QUIT) break;
            else if (event.type() == MOUSEMOTION)
            {
                mouse.update(event);
                out << "mouse moved";
            }
            else if (event.type() == MOUSEBUTTONDOWN)
            {
                mouse.update(event);
                out << "mouse button pressed";
            }
            else if (event.type() == MOUSEBUTTONUP)
            {
                mouse.update(event);
                out << "mouse button released";
            }
            out << " ... x,y = " << mouse.x() << ',' << mouse.y()
                << " ... buttons = "
                << mouse.left() << ','
                << mouse.middle() << ','
                << mouse.right();
        }

        if (out.str() != "")
        {
            std::cout << out.str() << std::endl;
            
            Color c = {Uint8(rand() % 50 + 200),
                       Uint8(rand() % 50 + 200),
                       Uint8(rand() % 50 + 200)};
            Image image(font.render(out.str().c_str(), c));
            Rect rect = image.getRect();
            
            surface.lock();
            surface.fill(BLACK);
            surface.put_image(image, rect);
            surface.unlock();
            surface.flip();
        }
        delay(10);
    }
}


/******************************************************************************
 This is an example on using the mouse to perform drag-n-drop.
 *****************************************************************************/
void test_drag_n_drop()
{
    const int FONTSIZE = 24;
    Surface surface(640, 480);
    Event event;
    Font font("fonts/FreeSans.ttf", FONTSIZE);
    Mouse mouse;

    int x = 100, y = 100, w = 100, h = 100;
    bool move = false; // true iff the square is moving with the mouse

    std::stringstream out;
    out << "drag-n-drop sim: click on mouse to pick up/put down";
    Color c = {255, 255, 255};
    Image helpimage(font.render(out.str().c_str(), c));
    Rect helprect = helpimage.getRect();
    
    while (1)
    {
        std::stringstream out;
        if (event.poll())
        { 
            if (event.type() == QUIT) break;
            else if (event.type() == MOUSEMOTION)
            {
                mouse.update(event);
                if (move)
                {
                    x = mouse.x();
                    y = mouse.y();
                }
            }
            else if (event.type() == MOUSEBUTTONDOWN)
            {
                // do nothing ... pick up and put down
                // happens only when the button is released
            }
            else if (event.type() == MOUSEBUTTONUP)
            {
                mouse.update(event);
                int mousex = mouse.x();
                int mousey = mouse.y();
                if (x <= mousex && mousex <= x + w
                    && y <= mousey && mousey <= y + h)
                {
                    move = !move;
                }
            }
        }

        surface.lock();
        surface.fill(BLACK);
        if (move)
        {            
            surface.put_rect(x, y, w, h, 100, 100, 100);
        }
        else
        {
            surface.put_rect(x, y, w, h, 255, 255, 255);
        }
        surface.put_image(helpimage, helprect);
        surface.unlock();
        surface.flip();

        delay(10);
    }
}


/******************************************************************************
 This is tested only with Logictech gamepad.
 *****************************************************************************/
void test_gamepad()
{
    const int FONTSIZE = 24;
    Surface surface(640, 480);
    Event event;
    Font font("fonts/FreeSans.ttf", FONTSIZE);
    Mouse mouse;

    std::cout << "num joysticks: " << num_joysticks() << std::endl;

    Joystick js;

    std::cout << "num axes: " << js.num_axes() << std::endl;
    std::cout << "num buttons: " << js.num_buttons() << std::endl;
    
    while (1)
    {
        std::stringstream out;
        if (event.poll())
        {
            if (event.type() == QUIT)
            {
                break;
            }
            else if (event.type() == JOYSTICKAXISMOTION)
            {
                js.update(event);
                out << "axis, value: "
                    << js.axis()
                    << ", "
                    << js.axis_value();
            }
            else if (event.type() == JOYSTICKBUTTONDOWN)
            {
                js.update(event);
                out << "button down: " << js.button();
            }
            else if (event.type() == JOYSTICKBUTTONUP)
            {
                js.update(event);
                out << "button up: " << js.button();
            }
            else if(event.type() == JOYSTICKHATMOTION)
            {
                js.update(event);
                out << "hat up,down,left,right: "
                    << js.hat_up() << ','
                    << js.hat_down() << ','
                    << js.hat_left() << ','
                    << js.hat_right();                 
            }
        }

        if (out.str() != "")
        {
            std::cout << out.str() << std::endl;
            
            Color c = {Uint8(rand() % 50 + 200),
                       Uint8(rand() % 50 + 200),
                       Uint8(rand() % 50 + 200)};
            Image image(font.render(out.str().c_str(), c));
            Rect rect = image.getRect();
            
            surface.lock();
            surface.fill(BLACK);
            surface.put_image(image, rect);
            surface.unlock();
            surface.flip();
        }
        delay(10);
    }
}


void test_welcome()
{
    Surface surface(W, H);
    Event event;
    StarSmall * starSmall[15];
    StarMedium * starMedium[10];
    StarTiny * starTiny[25];

    // Music music("sounds/GameLoop.ogg");
    // music.play();
    
    srand((unsigned int) time(NULL));
    
    // init heap star objects
    for (int i = 0; i < 25; ++i)
    {
        if (i < 10)
        {
            starSmall[i] = new StarSmall;
            starMedium[i] = new StarMedium;
            starTiny[i] = new StarTiny;
        }
        else if (i < 15)
        {
            starSmall[i] = new StarSmall;
            starTiny[i] = new StarTiny;
        }
        else
        {
            starTiny[i] = new StarTiny;
        }
    }

    int time = 0;

    // title stuff
    bool appearTitle = false;
    Font titleFont("fonts/FreeMonoBold.ttf", 32);
    Color cTitle = {255, 255, 255};
    Image titleImage(titleFont.render("Welcome to GALAXIAN", cTitle));
    Rect titleRect = titleImage.getRect();
    titleRect.x = (W / 2) - 165;
    titleRect.y = 5;

    Font cpFont("fonts/FreeSerif.ttf", 25);
    Color cCp = {255, 255, 255};
    Image cpImage(cpFont.render("by Christian Elliott", cCp));
    Rect cpRect = cpImage.getRect();
    cpRect.x = (W / 2) - 100;
    cpRect.y = 55;

    Font spaceFont("fonts/FreeMonoBold.ttf", 30);
    Color cSpace = {255, 255, 255};
    Image spaceImage(spaceFont.render("PRESS SPACE TO CONTINUE", cSpace));
    Rect spaceRect = spaceImage.getRect();
    spaceRect.x = 125;
    spaceRect.y = 225;

    Font fontBlue("fonts/FreeSerif.ttf", 30);
    Color cBlue = {255, 255, 255};
    Image blueImage(fontBlue.render("30", cBlue));
    Rect blueRect = blueImage.getRect();
    blueRect.x = 150;
    blueRect.y = 400;

    Font fontPurple("fonts/FreeSerif.ttf", 30);
    Color cPurple = {255, 255, 255};
    Image purpleImage(fontPurple.render("40", cPurple));
    Rect purpleRect = purpleImage.getRect();
    purpleRect.x = 250;
    purpleRect.y = 400;

    Font fontRed("fonts/FreeSerif.ttf", 30);
    Color cRed = {255, 255, 255};
    Image redImage(fontRed.render("50", cRed));
    Rect redRect = redImage.getRect();
    redRect.x = 350;
    redRect.y = 400;

    Font fontFlag("fonts/FreeSerif.ttf", 30);
    Color cFlag = {255, 255, 255};
    Image flagImage(fontFlag.render("60", cFlag));
    Rect flagRect = flagImage.getRect();
    flagRect.x = 450;
    flagRect.y = 400;
    
    // alien stuff================================================
    // Usership usership;
    // Image UsershipImage("images/galaxian/GalaxianGalaxip.gif");
    // Rect UsershipRect = UsershipImage.getRect();
    // UsershipRect.x = 300;
    // UsershipRect.y = 400;

    // order: Blue, Purple, Red, Flagship
    // 30, 40, 50, 60
    
    Aqua aqua;
    Image AquaImage("images/galaxian/GalaxianAquaAlien.gif");
    Rect AquaRect = AquaImage.getRect();
    AquaRect.x = 641; // 150
    AquaRect.y = 350;
    
    Purple purple;
    Image PurpleImage("images/galaxian/GalaxianPurpleAlien.gif");
    Rect PurpleRect = PurpleImage.getRect();
    PurpleRect.x = 641; // 250
    PurpleRect.y = 350;

    Red red;
    Image RedImage("images/galaxian/GalaxianRedAlien.gif");
    Rect RedRect = RedImage.getRect();
    RedRect.x = 641; // 350
    RedRect.y = 350;

    Flagship flagship;
    Image FlagshipImage("images/galaxian/GalaxianFlagship.gif");
    Rect FlagshipRect = FlagshipImage.getRect();
    FlagshipRect.x = 641; // 450
    FlagshipRect.y = 350;
    
    bool blu_at_home = false;
    bool purple_at_home = false;
    bool red_at_home = false;
    bool flagship_at_home = false;
    bool all_ships_home = false;

    bool show_space = false;
    bool space_pressed = false;
    while (1)
    {
        if (space_pressed) { break; }
        if (time > H / 3) appearTitle = true;

        if (event.poll() && event.type() == QUIT) break;

        if (show_space)
        {

            KeyPressed keypressed = get_keypressed();
            if (keypressed[SPACE])
            {
                space_pressed = true;
                break;
            }
        }

        //=================================================
        // move stars
        //=================================================
        
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->move();
        }
        
        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->move();
        }

        for (int i = 0; i < 25; ++i)
        {
            starTiny[i]->move();
        }

        //================================================
        // move in the aliens
        //================================================

        if (!blu_at_home && appearTitle)
        {
            AquaRect.x -= 2;
            if (!blu_at_home && AquaRect.x == 151)
            {
                blu_at_home = true;
            }
        }

        else if (blu_at_home && !purple_at_home)
        {
            PurpleRect.x -= 2;
            if (!purple_at_home && PurpleRect.x == 251)
            {
                purple_at_home = true;
            }
        }

        else if (blu_at_home && purple_at_home && !red_at_home)
        {
            RedRect.x -= 2;
            if (!red_at_home && RedRect.x == 351)
            {
                red_at_home = true;
            }
        }

        else if (blu_at_home && purple_at_home && red_at_home
            && !flagship_at_home)
        {
            FlagshipRect.x -= 2;
            if (red_at_home && FlagshipRect.x == 451)
            {
                flagship_at_home = true;
                all_ships_home = true;
                show_space = true;
            }
        }
        
        //=================================================
        // draw objects
        //=================================================
        
        surface.lock();
        surface.fill(BLACK);
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->draw(surface);
        }
        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->draw(surface);
        }
        for (int i = 0; i < 25; ++i)
        {
            starTiny[i]->draw(surface);
        }
        
        if (appearTitle)
        {
            surface.put_image(titleImage, titleRect);
            surface.put_image(cpImage, cpRect);
            if (flagship_at_home)
            {
                surface.put_image(spaceImage, spaceRect);
            }
            // Alien objs
            surface.put_image(AquaImage, AquaRect);
            surface.put_image(FlagshipImage, FlagshipRect);
            surface.put_image(PurpleImage, PurpleRect);
            surface.put_image(RedImage, RedRect);
            // text objs --> wait for aliens to arrive
            if (blu_at_home)
            {
                surface.put_image(blueImage, blueRect);
            }
            if (purple_at_home)
            {
                surface.put_image(purpleImage, purpleRect);
            }
            if (red_at_home)
            {
                surface.put_image(redImage, redRect);
            }
            if (flagship_at_home)
            {
                surface.put_image(flagImage, flagRect);
            }
        }
        surface.unlock();
        surface.flip();
        
        delay(20);

        //=================================================
        ++time;
    }
}


void test_laser()
{
    Surface surface(W, H);
    Event event;
    StarSmall * starSmall[15];
    StarMedium * starMedium[10];
    StarTiny * starTiny[25];

    Music music("sounds/GameLoop.ogg");
    music.play();
    
    srand((unsigned int) time(NULL));
    
    // init heap star objects
    for (int i = 0; i < 25; ++i)
    {
        if (i < 10)
        {
            starSmall[i] = new StarSmall;
            starMedium[i] = new StarMedium;
            starTiny[i] = new StarTiny;
        }
        else if (i < 15)
        {
            starSmall[i] = new StarSmall;
            starTiny[i] = new StarTiny;
        }
        else
        {
            starTiny[i] = new StarTiny;
        }
    }

    Usership usership;
    Image UsershipImage("images/galaxian/GalaxianGalaxip.gif");
    Rect UsershipRect = UsershipImage.getRect();
    UsershipRect.x = 300;
    UsershipRect.y = 400;

    Flagship flagship;
    Image FlagshipImage("images/galaxian/GalaxianFlagship.gif");
    Rect FlagshipRect = FlagshipImage.getRect();
    FlagshipRect.x = 100;
    FlagshipRect.y = 100;

    UserLaser laser;
    Rect LaserRect;
    laser.x = UsershipRect.x + 15;
    laser.y = UsershipRect.y - 5;
    LaserRect.w = laser.w;
    LaserRect.h = laser.h;

    //Music laserSound("sounds/laser.wav");
    
    while (1) // main while loop
    {
        if (event.poll() && event.type() == QUIT) break;

        LaserRect.x = laser.x;
        LaserRect.y = laser.y;

        //====================================================
        // listen for space bar
        //====================================================
                                                      
        KeyPressed keypressed = get_keypressed();
        if (keypressed[SPACE])
        {
            laser.shooting = true;
            //laserSound.play();
        }
        if (laser.shooting && laser.y > 0)
        {
            laser.move(LaserRect);
        }
        
        else if (laser.shooting && laser.y < 0)
        {
            laser.y = UsershipRect.y - 5;
            laser.x = UsershipRect.x + 15;
            LaserRect.x = laser.x;
            LaserRect.y = laser.y;
            laser.shooting = false;
        }


        //===================================================
        // listen for arrow keys
        //===================================================

        if (keypressed[LEFTARROW] && !laser.shooting)
        {
            if (UsershipRect.x >= 0)
            {
                UsershipRect.x -= 4;
            }
            laser.x = UsershipRect.x + 15;
            laser.y = UsershipRect.y - 5;
        }
        else if (keypressed[RIGHTARROW] && !laser.shooting)
        {
            if (UsershipRect.x + UsershipRect.w < W)
            {
                UsershipRect.x += 4;
            }
            laser.x = UsershipRect.x + 15;
            laser.y = UsershipRect.y - 5;
        }

        if (keypressed[LEFTARROW] && laser.shooting)
        {
            if (UsershipRect.x > 0)
            {
                UsershipRect.x -= 4;
            }
        }
        else if (keypressed[RIGHTARROW] && laser.shooting)
        {
            if (UsershipRect.x + UsershipRect.w < W)
            {
                UsershipRect.x += 4;
            }
        }

        //=================================================
        // star for loops
        //=================================================        
        
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->move();
        }
        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->move();
        }
        for (int i = 0; i < 25; ++i)
        {
            starTiny[i]->move();
        }

        //================================================
        // collision detection for laser and aliens
        //================================================

        if (LaserRect.collidesWithLaser(FlagshipRect))
        {
            flagship.alive = false;
        }

        //================================================
        // surface stuff
        //================================================
        
        surface.lock();
        surface.fill(BLACK);
        
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->draw(surface);
        }
        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->draw(surface);
        }
        for (int i = 0; i < 25; ++i)
        {
            starTiny[i]->draw(surface);
        }
        
        surface.put_image(UsershipImage, UsershipRect);
        // surface.put_rect(LaserRect.x, LaserRect.y, LaserRect.w, LaserRect.h,
        //                  255, 255, 0);
        
        if (flagship.alive)
        {
            surface.put_image(FlagshipImage, FlagshipRect);
        }
        
        laser.draw(surface);
        
        surface.unlock();
        surface.flip();
        delay(20);
    }
}


int test_lasers_and_aliens() // possible main function currently
{
    Surface surface(W, H);
    Event event;
    StarSmall * starSmall[15];
    StarMedium * starMedium[10];
    StarTiny * starTiny[25];

    Music music("sounds/GameLoop.ogg");
    music.play();
    
    srand((unsigned int) time(NULL));
    
    // init heap star objects =============================
    for (int i = 0; i < 25; ++i)
    {
        if (i < 10)
        {
            starSmall[i] = new StarSmall;
            starMedium[i] = new StarMedium;
            starTiny[i] = new StarTiny;
        }
        else if (i < 15)
        {
            starSmall[i] = new StarSmall;
            starTiny[i] = new StarTiny;
        }
        else
        {
            starTiny[i] = new StarTiny;
        }
    }
    // end init star objs ======================================


    // init Alien objs and alien Rects ==========================
    const int NUM_AQUAS = 24;
    Aqua * aqua[NUM_AQUAS];
    Rect * aquaRect[NUM_AQUAS];
    Image * aquaImage[NUM_AQUAS];
    for (int i = 0; i < NUM_AQUAS; ++i)
    {
        aqua[i] = new Aqua;
        aquaImage[i] = new Image("images/galaxian/GalaxianAquaAlien.gif");
        aquaRect[i] = new Rect(aquaImage[i]->getRect());
        
        if (i == 0 || i == 8 || i == 16)
        {
            aquaRect[i]->x = 200;
        }

        else
        {
            aquaRect[i]->x = aquaRect[i - 1]->x + 40;
        }

        if (i < 8 && i >= 0)
        {
            aquaRect[i]->y = 140;
        }

        else if (i < 16 && i >= 8)
        {
            aquaRect[i]->y = 170;
        }

        else
        {
            aquaRect[i]->y = 200;
        }

        aqua[i]->y = aquaRect[i]->y;
        aqua[i]->x = aquaRect[i]->x;

        aqua[i]->type = 'a';
    }

    const int NUM_PURPLE = 6;
    Purple * purple[NUM_PURPLE];
    Rect * purpleRect[NUM_PURPLE];
    Image * purpleImage[NUM_PURPLE];
    for (int i = 0; i < NUM_PURPLE; ++i)
    {
        purple[i] = new Purple;
        purpleImage[i] = new Image("images/galaxian/GalaxianPurpleAlien.gif");
        purpleRect[i] = new Rect(purpleImage[i]->getRect());

        purpleRect[0]->x = 240;

        if (i > 0)
        {
            purpleRect[i]->x = purpleRect[i - 1]->x + 40;
        }

        purpleRect[i]->y = 110;
        purple[i]->x = purpleRect[i]->x;
        purple[i]->y = purpleRect[i]->y;

        purple[i]->type = 'p';
    }


    const int NUM_RED = 4;
    Red * red[NUM_RED];
    Rect * redRect[NUM_RED];
    Image * redImage[NUM_RED];

    for (int i = 0; i < NUM_RED; ++i)
    {
        red[i] = new Red;
        redImage[i] = new Image("images/galaxian/GalaxianRedAlien.gif");
        redRect[i] = new Rect(redImage[i]->getRect());

        redRect[0]->x = 280;
        if (i > 0)
        {
            redRect[i]->x = redRect[i - 1]->x + 40;
        }

        redRect[i]->y = 80;
        red[i]->x = redRect[i]->x;
        red[i]->y = redRect[i]->y;

        red[i]->type = 'r';
    }


    const int NUM_FLAG = 2;
    Flagship * flag[NUM_FLAG];
    Rect * flagRect[NUM_FLAG];
    Image * flagImage[NUM_FLAG];

    for (int i = 0; i < NUM_FLAG; ++i)
    {
        flag[i] = new Flagship;
        flagImage[i] = new Image("images/galaxian/GalaxianFlagship.gif");
        flagRect[i] = new Rect(flagImage[i]->getRect());

        flagRect[0]->x = 320;
        if (i > 0)
        {
            flagRect[i]->x = flagRect[i - 1]->x + 40;
        }

        flagRect[i]->y = 50;
        flag[i]->x = flagRect[i]->x;
        flag[i]->y = flagRect[i]->y;

        flag[i]->type = 'f';
    }

    Usership usership;
    Image usershipImage("images/galaxian/GalaxianGalaxip.gif");
    Rect usershipRect = usershipImage.getRect();
    usershipRect.x = 300;
    usershipRect.y = 400;

    Usership u0;
    Image u0Image("images/galaxian/GalaxianGalaxip.gif");
    Rect u0Rect = u0Image.getRect();
    u0Rect.x = W - 637;
    u0Rect.y = H - 35;

    Usership u1;
    Image u1Image("images/galaxian/GalaxianGalaxip.gif");
    Rect u1Rect = u0Image.getRect();
    u1Rect.x = (W - 637) + 40;
    u1Rect.y = H - 35;

    // UserLaser laser;
    // Rect LaserRect;
    // laser.x = usershipRect.x + 15;
    // laser.y = usershipRect.y - 5;
    // LaserRect.w = laser.w;
    // LaserRect.h = laser.h;

    const int NUM_USER_LASER = 5;
    UserLaser * userLaser[NUM_USER_LASER];
    Rect * userLaserRect[NUM_USER_LASER];
    for (int i = 0; i < NUM_USER_LASER; ++i)
    {
        userLaser[i] = new UserLaser;
        userLaserRect[i] = new Rect;
        userLaser[i]->x = usership.x + 15;
        userLaser[i]->y = usership.y - 5;

        userLaserRect[i]->w = userLaser[i]->w;
        userLaserRect[i]->h = userLaser[i]->h;
    }

    const int NUM_EXPLOSION = 7;
    Image * explosion[NUM_EXPLOSION];
    Rect * explosionRect[NUM_EXPLOSION];
    for (int i = 0; i < NUM_EXPLOSION; ++i)
    {
        explosion[0] = new Image("images/galaxian/explosion/explosion_1.png");
        explosion[1] = new Image("images/galaxian/explosion/explosion_2.png");
        explosion[2] = new Image("images/galaxian/explosion/explosion_3.png");
        explosion[3] = new Image("images/galaxian/explosion/explosion_4.png");
        explosion[4] = new Image("images/galaxian/explosion/explosion_5.png");
        explosion[5] = new Image("images/galaxian/explosion/explosion_6.png");
        explosion[6] = new Image("images/galaxian/explosion/explosion_7.png");
        explosionRect[i] = new Rect;
    }


    // _+_+_+_+_+_+_+_+_+_+_+_+_++_+_+_ fix score object here!!!!!!!!!!!!!!!!!!!!!!!!!

    int score = 0;
    const char base_string[] = "";
    char out_string [100];
    sprintf(out_string, "%s%d", base_string, score);
    //printf("out_string = "%s"n", out_string);
    
    Font scoreFont("fonts/FreeSerif.ttf", 30);
    Color cScore = {255, 255, 255};
    Image scoreImage(scoreFont.render(out_string, cScore));
    Rect scoreRect = scoreImage.getRect();
    scoreRect.x = (W - 637) + 80;
    scoreRect.y = H - 45;
    
    // end alien objs and rects init ============================

    // create array for ALL aliens ==============================

    int i_purple = 0;
    int i_red = 0;
    int i_flag = 0;

    const int NUM_ALIEN = NUM_AQUAS + NUM_PURPLE + NUM_RED + NUM_FLAG;
    Alien * alien[NUM_ALIEN];
    
    Rect * alienRect[NUM_ALIEN];
    for (int i = 0; i < NUM_ALIEN; ++i)
    {
        if (i < NUM_AQUAS)
        {
            alien[i] = aqua[i];
            alien[i]->rect_num = i;
            alienRect[i] = aquaRect[i];
        }

        if (i >= NUM_AQUAS && i < NUM_AQUAS + NUM_PURPLE)
        {
            alien[i] = purple[i_purple];
            alien[i]->rect_num = i_purple;
            alienRect[i] = purpleRect[i_purple];
            ++i_purple;
        }

        if (i >= NUM_AQUAS + NUM_PURPLE && i <
            NUM_AQUAS + NUM_PURPLE + NUM_RED)
        {
            alien[i] = red[i_red];
            alien[i]->rect_num = i_red;
            alienRect[i] = redRect[i_red];
            ++i_red;
        }

        if (i >= NUM_AQUAS + NUM_PURPLE + NUM_RED &&
            i < NUM_ALIEN)
        {
            alien[i] = flag[i_flag];
            alien[i]->rect_num = i_flag;
            alienRect[i] = flagRect[i_flag];
            ++i_flag;
        }
    }
    
    bool moving = true;
    int attacking = 0;
    int old_x;
    int old_y;
    int attacking_alien;
    bool alien_attacking = false;
    bool alien_returning = false;
    bool at_home = true;
    bool show_explosion = false;
    bool flagship_attacking = false;
    int escort_count = 0;
    int escort[2] = {0, 0};
    int num_lives = 3;
    bool game_over = false;
    bool all_aliens_dead = false;
    // int score = 0;
    

    int x_values[NUM_ALIEN];

    for (int i = 0; i < NUM_ALIEN; ++i)
    {
        x_values[i] = alienRect[i]->x;
    }

    int user_laser_delay = 75;
    int usership_delay = 75;

    while(1)
    {
        if (event.poll() && event.type() == QUIT) break;

        for (int i = 0; i < NUM_ALIEN; ++i)
        {
            if (alien[i]->alive == true)
            {
                all_aliens_dead = false;
                break;
            }
            if (i == NUM_ALIEN - 1 && alien[i]->alive == false)
            {
                all_aliens_dead = true;
            }
        }

        if (all_aliens_dead)
        {
            i_purple = 0;
            i_red = 0;
            i_flag = 0;
            for (int i = 0; i < NUM_AQUAS; ++i)
            {
                if (i == 0 || i == 8 || i == 16)
                {
                    aquaRect[i]->x = 200;
                }

                else
                {
                    aquaRect[i]->x = aquaRect[i - 1]->x + 40;
                }

                if (i < 8 && i >= 0)
                {
                    aquaRect[i]->y = 140;
                }

                else if (i < 16 && i >= 8)
                {
                    aquaRect[i]->y = 170;
                }

                else
                {
                    aquaRect[i]->y = 200;
                }

                aqua[i]->y = aquaRect[i]->y;
                aqua[i]->x = aquaRect[i]->x;

                aqua[i]->alive = true;
            }

            for (int i = 0; i < NUM_PURPLE; ++i)
            {
                purple[i] = new Purple;
                purpleImage[i] = new Image("images/galaxian/GalaxianPurpleAlien.gif");
                purpleRect[i] = new Rect(purpleImage[i]->getRect());

                purpleRect[0]->x = 240;

                if (i > 0)
                {
                    purpleRect[i]->x = purpleRect[i - 1]->x + 40;
                }

                purpleRect[i]->y = 110;
                purple[i]->x = purpleRect[i]->x;
                purple[i]->y = purpleRect[i]->y;

                purple[i]->alive = true;
            }

            for (int i = 0; i < NUM_RED; ++i)
            {
                red[i] = new Red;
                redImage[i] = new Image("images/galaxian/GalaxianRedAlien.gif");
                redRect[i] = new Rect(redImage[i]->getRect());

                redRect[0]->x = 280;
                if (i > 0)
                {
                    redRect[i]->x = redRect[i - 1]->x + 40;
                }

                redRect[i]->y = 80;
                red[i]->x = redRect[i]->x;
                red[i]->y = redRect[i]->y;

                red[i]->alive = true;
            }

            for (int i = 0; i < NUM_FLAG; ++i)
            {
                flag[i] = new Flagship;
                flagImage[i] = new Image("images/galaxian/GalaxianFlagship.gif");
                flagRect[i] = new Rect(flagImage[i]->getRect());

                flagRect[0]->x = 320;
                if (i > 0)
                {
                    flagRect[i]->x = flagRect[i - 1]->x + 40;
                }

                flagRect[i]->y = 50;
                flag[i]->x = flagRect[i]->x;
                flag[i]->y = flagRect[i]->y;

                flag[i]->alive = true;
            }

            for (int i = 0; i < NUM_ALIEN; ++i)
            {
                if (i < NUM_AQUAS)
                {
                    alien[i] = aqua[i];
                    alien[i]->rect_num = i;
                    alienRect[i] = aquaRect[i];
                }

                if (i >= NUM_AQUAS && i < NUM_AQUAS + NUM_PURPLE)
                {
                    alien[i] = purple[i_purple];
                    alien[i]->rect_num = i_purple;
                    alienRect[i] = purpleRect[i_purple];
                    ++i_purple;
                }

                if (i >= NUM_AQUAS + NUM_PURPLE && i <
                    NUM_AQUAS + NUM_PURPLE + NUM_RED)
                {
                    alien[i] = red[i_red];
                    alien[i]->rect_num = i_red;
                    alienRect[i] = redRect[i_red];
                    ++i_red;
                }

                if (i >= NUM_AQUAS + NUM_PURPLE + NUM_RED &&
                    i < NUM_ALIEN)
                {
                    alien[i] = flag[i_flag];
                    alien[i]->rect_num = i_flag;
                    alienRect[i] = flagRect[i_flag];
                    ++i_flag;
                }
            }

            for (int i = 0; i < NUM_ALIEN; ++i)
            {
                x_values[i] = alienRect[i]->x;
            }

            all_aliens_dead = false;
        }

        // stars ========================================
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->move();
        }
        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->move();
        }
        for (int i = 0; i < 25; ++i)
        {
            starTiny[i]->move();
        }
        // end stars ===================================

        KeyPressed keypressed = get_keypressed();

        if (keypressed[LEFTARROW] // && laser.shooting
            )
        {
            if (usershipRect.x > 0)
            {
                usershipRect.x -= 4;
            }
        }
        else if (keypressed[RIGHTARROW] // && laser.shooting
            )
        {
            if (usershipRect.x + usershipRect.w < W)
            {
                usershipRect.x += 4;
            }
        }
        
        if (keypressed[SPACE] && user_laser_delay >= 50)
        {
            for (int i = 0; i < NUM_USER_LASER; ++i)
            {
                if (userLaser[i]->shooting == false)
                {
                    userLaser[i]->shooting = true;
                    user_laser_delay = 0;
                    userLaser[i]->alive = true;
                    break;
                }
            }
        }

        else if (((keypressed[SPACE] && keypressed[LEFTARROW]) ||
                  ((keypressed[SPACE] && keypressed[RIGHTARROW]))) && user_laser_delay >= 50)
        {
            for (int i = 0; i < NUM_USER_LASER; ++i)
            {
                if (userLaser[i]->shooting == false)
                {
                    userLaser[i]->shooting = true;
                    user_laser_delay = 0;
                    userLaser[i]->alive = true;
                    break;
                }
            }
        }

        if (user_laser_delay != 50)
        {
            ++user_laser_delay;
        }

        for (int i = 0; i < NUM_USER_LASER; ++i)
        {
            if (userLaser[i]->shooting && userLaser[i]->y > 0)
            {
                userLaser[i]->move(*userLaserRect[i]);
            }
        }

        for (int i = 0; i < NUM_USER_LASER; ++i)
        {
            if (userLaser[i]->shooting && userLaser[i]->y < 0)
            {
                userLaser[i]->y = usershipRect.y - 5;
                userLaser[i]->x = usershipRect.x + 15;
                userLaserRect[i]->x = userLaser[i]->x;
                userLaserRect[i]->y = userLaser[i]->y;
                userLaser[i]->shooting = false;
            }

            if (userLaser[i]->shooting == false)
            {
                userLaser[i]->y = usershipRect.y - 5;
                userLaser[i]->x = usershipRect.x + 15;
                userLaserRect[i]->x = userLaser[i]->x;
                userLaserRect[i]->y = userLaser[i]->y;
            }
        }
        
        // else if (laser.shooting && laser.y < 0)
        // {
        //     laser.y = UsershipRect.y - 5;
        //     laser.x = UsershipRect.x + 15;
        //     LaserRect.x = laser.x;
        //     LaserRect.y = laser.y;
        //     laser.shooting = false;
        // }


        //===================================================
        // listen for arrow keys
        //===================================================

        // if (keypressed[LEFTARROW] // && !laser.shooting
        //     )
        // {
        //     if (usershipRect.x >= 0)
        //     {
        //         usershipRect.x -= 4;
        //     }
        //     // laser.x = usershipRect.x + 15;
        //     // laser.y = usershipRect.y - 5;
        // }
        // else if (keypressed[RIGHTARROW] // && !laser.shooting
        //     )
        // {
        //     if (usershipRect.x + usershipRect.w < W)
        //     {
        //         usershipRect.x += 4;
        //     }
        //     // laser.x = usershipRect.x + 15;
        //     // laser.y = usershipRect.y - 5;
        // }

        

        //===================================================
        // MOVE FLEET 
        // ==================================================
        
        if (moving == true)
        {
            for (int i = 0; i < NUM_AQUAS; ++i)
            {
                aqua[i]->moveLeft((*aquaRect[i]), x_values);
                if (i < NUM_PURPLE)
                {
                    purple[i]->moveLeft((*purpleRect[i]), x_values);
                }
                if (i < NUM_RED)
                {
                    red[i]->moveLeft((*redRect[i]), x_values);
                }
                if (i < NUM_FLAG)
                {
                    flag[i]->moveLeft((*flagRect[i]), x_values);
                }
            }

            for (int i = 0; i < NUM_ALIEN; ++i)
            {
                x_values[i] -= 2;
            }
        }

        else if (moving == false)
        {
            for (int i = 0; i < NUM_AQUAS; ++i)
            {
                aqua[i]->moveRight((*aquaRect[i]), x_values);
                if (i < NUM_PURPLE)
                {
                    purple[i]->moveRight((*purpleRect[i]), x_values);
                }
                if (i < NUM_RED)
                {
                    red[i]->moveRight((*redRect[i]), x_values);
                }
                if (i < NUM_FLAG)
                {
                    flag[i]->moveRight((*flagRect[i]), x_values);
                }
            }
            
            for (int i = 0; i < NUM_ALIEN; ++i)
            {
                x_values[i] += 2;
            }
        }

        // if ((aquaRect[7]->x) + 32 >= 640)
        // {
        //     moving = true;
        // }
        if (x_values[7] + 32 >= 640)
        {
            moving = true;
        }

        // else if ((aquaRect[0]->x) <= 0)
        // {
        //     moving = false;
        // }

        else if (x_values[0] <= 0)
        {
            moving = false;
        }


        // ATTACK PART ====================================================


        if (!alien_attacking && !alien_returning)
        {
            attacking = rand() % 100;
        }

        if (attacking == 0 && !alien_attacking)
        {
            alien_attacking = true;
            attacking_alien = rand() % (NUM_ALIEN);
            
            while (alien[attacking_alien]->alive == false)
            {
                attacking_alien = rand() % (NUM_ALIEN - 1);
            }
            alien[attacking_alien]->attacking = true;
            old_y = alienRect[attacking_alien]->y;
            old_x = alienRect[attacking_alien]->x;
            at_home = false;
        }

        // escort_count = 0;
        // if (flagship_attacking)
        // {
        //     for (int i = 30; i < 34; ++i)
        //     {
        //         if (red[i]->alive && escort_count < 2)
        //         {
        //             red[i]->attacking = true;
        //             escort[escort_count] = i;
        //             ++escort_count;
        //         }
        //     }
        // }

        if (alien_attacking && !alien_returning)
        {
            for (int i = 0; i < NUM_ALIEN; ++i)
            {
                if (alien[i]->attacking)
                {
                    alien[i]->attack(*alienRect[attacking_alien]);
                    // if (flagship_attacking)
                    // {
                    //     alien[escort[0]]->attack(*alienRect[escort[0]]);
                    //     alien[escort[1]]->attack(*alienRect[escort[1]]);
                    // }
                }
            }
        }

        if (alien_attacking && alienRect[attacking_alien]->y >= H && !alien_returning)
        {
            alien_returning = true;
            alienRect[attacking_alien]->y = 0;
            alien[attacking_alien]->y = 0;
            alien[attacking_alien]->attacking = false;
        }

        if (alien_returning)
        {
            alien[attacking_alien]->attacking = false;
            alien[attacking_alien]->return_alien(*alienRect[attacking_alien], old_y, old_x, at_home,
                                                 x_values, attacking_alien);
            alien[attacking_alien]->returning = true;
            if (at_home)
            {
                alien[attacking_alien]->returning = false;
            }
        }

        if (at_home)
        {
            alien_attacking = false;
            alien_returning = false;
        }

        // END ATTACK PARK ===============================================

        // BEGIN COLLISION CHECK =========================================

        for (int i = 0; i < NUM_ALIEN; ++i)
        {
            for (int j = 0; j < NUM_USER_LASER; ++j)
            {
                if (alien[i]->alive)
                {
                    if (userLaserRect[j]->collidesWithLaser(*alienRect[i]) && userLaser[j]->shooting)
                    {
                        alien[i]->alive = false;
                        if (i >= 0 && i < 24)
                        {
                            score += 30;
                        }

                        else if (i >= 24 && i < 30)
                        {
                            score += 40;
                        }

                        else if (i >= 30 && i < 34)
                        {
                            score += 50;
                        }

                        else if (i >= 34 && i < 36)
                        {
                            score += 60;
                        }
                        userLaser[j]->alive = false;
                        userLaser[j]->shooting = false;
                        userLaser[j]->x = usership.x + 15;
                        userLaser[j]->y = usership.y - 5;
                        userLaserRect[j]->x = userLaser[j]->x;
                        userLaserRect[j]->y = userLaser[j]->y;
                        for (int k = 0; k < NUM_EXPLOSION; ++k)
                        {
                            std::cout << i << '\n';
                            explosionRect[k]->x = alien[i]->x;
                            explosionRect[k]->y = alien[i]->y;
                            explosionRect[k]->w = 32;
                            explosionRect[k]->h = 32;
                        }
                        show_explosion = true;
                    }
                }
            }
        }

        for (int i = 0; i < NUM_ALIEN; ++i)
        {
            if (usershipRect.collidesWithAlien(*alienRect[i]))
            {
                std::cout << "collision" << '\n';
                usership_delay = 0;
                usership.alive = false;
                // alien[i]->alive = false;
                --num_lives;
                // for (int j = 0; j < NUM_EXPLOSION; ++j)
                // {
                //     explosionRect[j]->x = usership.x;
                //     explosionRect[j]->y = usership.y;
                //     explosionRect[j]->w = 32;
                //     explosionRect[j]->h = 32;
                // }
                // show_explosion = true;
                break;
            }
            if (usership.alive == false)
            {
                break;
            }
        }

        // if alien is dead, get its rect away
        for (int i = 0; i < NUM_ALIEN; ++i)
        {
            if (alien[i]->alive == false && !show_explosion)
            {
                alienRect[i]->x = 1000;
                alienRect[i]->y = 1000;
            }
        }
        
        // surface =======================================================
        surface.lock();
        surface.fill(BLACK);

        sprintf(out_string, "%s%d", base_string, score);
        Image * scorePtr = new Image(scoreFont.render(out_string, cScore));
        surface.put_image(*scorePtr, scoreRect);

        delete scorePtr;
        
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->draw(surface);
        }
        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->draw(surface);
        }
        for (int i = 0; i < 25; ++i)
        {
            starTiny[i]->draw(surface);
        }

        for (int i = 0; i < NUM_AQUAS; ++i)
        {
            // dereference image and rect pointers
            if (aqua[i]->alive)
            {
                surface.put_image((*aquaImage[i]), (*aquaRect[i]));
            }
        }

        for (int i = 0; i < NUM_PURPLE; ++i)
        {
            if (purple[i]->alive)
            {
                surface.put_image((*purpleImage[i]), (*purpleRect[i]));
            }
        }

        for (int i = 0; i < NUM_RED; ++i)
        {
            if (red[i]->alive)
            {
                surface.put_image((*redImage[i]), (*redRect[i]));
            }
        }

        for (int i = 0; i < NUM_FLAG; ++i)
        {
            if (flag[i]->alive)
            {
                surface.put_image((*flagImage[i]), (*flagRect[i]));
            }
        }

        if (usership.alive && usership_delay >= 50)
        {
            surface.put_image(usershipImage, usershipRect);
        }

        ++usership_delay;
        if (usership_delay >= 50)
        {
            usership.alive = true;
        }
        
        for (int i = 0; i < NUM_USER_LASER; ++i)
        {
            if (userLaser[i]->alive && userLaser[i]->shooting)
            {
                userLaser[i]->draw(surface);
            }
        }

        int explosion_count = 10;

        if (show_explosion)
        {
            for (int i = 0; i < NUM_EXPLOSION; )
            {
                surface.put_image(*explosion[i], *explosionRect[i]);
                if (explosion_count % 10 == 0)
                {
                    ++i;
                }
                if (i == NUM_EXPLOSION - 1 && explosion_count % 10 == 0)
                {
                    show_explosion = false;
                }
            }
            ++explosion_count;
        }

        if (!show_explosion)
        {
            explosion_count = 10;
        }

        if (num_lives == 3)
        {
            surface.put_image(u0Image, u0Rect);
            surface.put_image(u1Image, u1Rect);
        }

        else if (num_lives == 2)
        {
            surface.put_image(u0Image, u0Rect);
        }

        else if (num_lives == 1)
        {
            // don't put any ships
        }

        else // num_lives == 0; game over.
        {
            game_over = true;
        }

        surface.unlock();
        surface.flip();
        delay(20);

        if (game_over)
        {
            break;
        }
        // end surface ===================================
    }

    if (flagship_attacking && at_home)
    {
        flagship_attacking = false;
        escort_count = 0;
    }

    return score;
}


bool game_over(int score)
{
    Surface surface(W, H);
    Event event;
    StarSmall * starSmall[15];
    StarMedium * starMedium[10];
    StarTiny * starTiny[25];

    // Music music("sounds/GameLoop.ogg");
    // music.play();
    
    srand((unsigned int) time(NULL));
    
    // init heap star objects
    for (int i = 0; i < 25; ++i)
    {
        if (i < 10)
        {
            starSmall[i] = new StarSmall;
            starMedium[i] = new StarMedium;
            starTiny[i] = new StarTiny;
        }
        else if (i < 15)
        {
            starSmall[i] = new StarSmall;
            starTiny[i] = new StarTiny;
        }
        else
        {
            starTiny[i] = new StarTiny;
        }
    }

    Font spaceFont("fonts/FreeMonoBold.ttf", 30);
    Color cSpace = {255, 255, 255};
    Image spaceImage(spaceFont.render("GAME OVER", cSpace));
    Rect spaceRect = spaceImage.getRect();
    spaceRect.x = 125;
    spaceRect.y = 225;

    const char base_string[] = "SCORE: ";
    char out_string [100];
    sprintf(out_string, "%s%d", base_string, score);
    //printf("out_string = "%s"n", out_string);

    Font scoreFont("fonts/FreeSerif.ttf", 30);
    Color cScore = {255, 255, 255};
    Image scoreImage(scoreFont.render(out_string, cScore));
    Rect scoreRect = scoreImage.getRect();
    scoreRect.x = 250;
    scoreRect.y = 275;

    bool space_pressed = false;

    while (1)
    {
        if (space_pressed) { break; }

        if (event.poll() && event.type() == QUIT)
        {
            break;
        }
        KeyPressed keypressed = get_keypressed();
        if (keypressed[SPACE])
        {
            space_pressed = true;
            break;
        }

        sprintf(out_string, "%s%d", base_string, score);
        Image * scorePtr = new Image(scoreFont.render(out_string, cScore));
        surface.put_image(*scorePtr, scoreRect);

        delete scorePtr;

        //=================================================
        // move stars
        //=================================================
        
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->move();
        }
        
        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->move();
        }

        for (int i = 0; i < 25; ++i)
        {
            starTiny[i]->move();
        }

        surface.lock();
        surface.fill(BLACK);
        for (int i = 0; i < 15; ++i)
        {
            starSmall[i]->draw(surface);
        }
        for (int i = 0; i < 10; ++i)
        {
            starMedium[i]->draw(surface);
        }
        for (int i = 0; i < 25; ++i)
        {
            starTiny[i]->draw(surface);
        }
        surface.put_image(spaceImage, spaceRect);
        surface.unlock();
        surface.flip();
        delay(20);
    }

    return true;
}


bool ball_brick_hit(Rect * bricks[], StarMedium & ball, const int NUM_BRICKS)
{
    for (int i = 0; i < NUM_BRICKS; ++i)
    {
        if (ball.x >= bricks[i]->x &&
            ball.x <= bricks[i]->x + bricks[i]->w && 
            ball.y >= bricks[i]->y && 
            ball.y <= bricks[i]->y + bricks[i]->h &&
            bricks[i]->state == true)
            {
                std::cout << "collision detected\n";
                if (ball.dx < 0 && ball.dy < 0) // ball is moving up and left
                {
                    //ball.dx = -1;
                    ball.dy = 1;
                }
                else if (ball.dx == 0 && ball.dy < 0) // if ball is moving straight up
                {
                    //ball.dx = 0;
                    ball.dy = 1;
                }
                else if (ball.dy > 0) // ball is moving down
                {
                    ball.dy = -1;
                }
                else if (ball.dy < 0 && ball.dx > 0)// if ball is moving up and right
                {
                    //ball.dx = 1;
                    ball.dy = 1;
                }
                bricks[i]->state = false;
                return true;
            }
    }
    return false;
}


bool ball_paddle_hit(const Rect & paddle, StarMedium & ball)
{
    float paddle_m = paddle.x + (paddle.w / 2);
    const double paddle_factor = 0.058;
    if (ball.x >= paddle.x &&
        ball.x <= paddle.x + paddle.w && 
        ball.y >= paddle.y && 
        ball.y <= paddle.y + paddle.h)
        {
            std::cout << "collision detected\n";
            if (ball.x < paddle_m) // ball collides w/ left side of paddle
            {
                ball.dx = -1 * ((paddle_m - ball.x) * paddle_factor);
                ball.dy = -1;
            }
            if (ball.x > paddle_m)
            {
                ball.dx = 1 * (ball.x - paddle_m) * paddle_factor;
                ball.dy = -1;
            }
            std::cout << ball.dx << ' ' << ball.dy << '\n';
            return true;
        }
    return false;
}


void ball_home(StarMedium & ball)
{
    ball.x = (W / 2) + (69 / 2);
    ball.y = H - 101;
    ball.direction = 'n';
}


void move_ball(const Rect & paddle, StarMedium & ball, 
               Rect * bricks[])
{
    const int num_bricks = 30;
    int x;
    ball_brick_hit(bricks, ball, num_bricks);
    ball_paddle_hit(paddle, ball);
    if (ball.y <= 0)
    { 
        ball.dy = 1;
    }
    else if (ball.y >= H)
    {
        // implement LOSE LIFE AND RESET FUNCTION and call function here
    }
    else if (ball.x <= 0) // ball hits left wall
    {
        ball.dx *= -1;
    }
    else if (ball.x >= W)
    {
        ball.dx *= -1;
    }
    ball.x += ball.dx;
    ball.y += ball.dy;    
}


void move_paddle(Rect & paddle)
{
    Surface surface(W, H);
    KeyPressed keypressed = get_keypressed();
    if (keypressed[LEFTARROW])
    {
        // move left!
        if (paddle.x > 0)
        {
            paddle.x -= 3;
        }
    }
    else if (keypressed[RIGHTARROW])
    {
        // move right!
        if (paddle.x < W - paddle.w)
        {
            paddle.x += 3;
        }
    }
}


void test_bb_welcome()
{
    const int W = 640;
    const int H = 480;
    Surface surface(W, H);
    Event event;
    Font Welcome("fonts/NovaMono-Regular.ttf", 30);
    int f = rand() % 8;
    Color font = {98, 114, 64};
    switch (f) 
    {
        case 0:
            //font = {98, 114, 64};
            font.r = 98;
            font.g = 114;
            font.b = 64;
            break;
        case 1:
            //font = {139, 233, 253};
            font.r = 139;
            font.g = 233;
            font.b = 253;
            break;
        case 2:
            //font = {80, 250, 123};
            font.r = 80;
            font.g = 250;
            font.b = 123;
            break;
        case 3:
            //font = {255, 184, 108};
            font.r = 255;
            font.g = 184;
            font.b = 108;
            break;
        case 4:
            //font = {255, 121, 198};
            font.r = 255;
            font.g = 121;
            font.b = 198;
            break;
        case 5:
            //font = {189, 147, 249};
            font.r = 189;
            font.g = 147;
            font.b = 249;
            break;
        case 6:
            //font = {255, 85, 85};
            font.r = 255;
            font.g = 85;
            font.b = 85;
            break;
        case 7:
            //font = {241, 250, 140};
            font.r = 241;
            font.g = 250;
            font.b = 140;
            break;
    }
    Image * WelcomeImage = new Image(Welcome.render("Welcome to Brick Breaker Neon", 
                                     font));
    Rect WelcomeRect = WelcomeImage->getRect();
    WelcomeRect.x = 50;
    WelcomeRect.y = 50;
    int time_count = 0;

    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        Image * welcomePtr;
        if (time_count > 150)
        {
            f = rand() % 8;
            std::cout << f << '\n';
            switch (f) 
            {
                case 0:
                    //font = {98, 114, 64};
                    font.r = 98;
                    font.g = 114;
                    font.b = 64;
                    break;
                case 1:
                    //font = {139, 233, 253};
                    font.r = 139;
                    font.g = 233;
                    font.b = 253;
                    break;
                case 2:
                    //font = {80, 250, 123};
                    font.r = 80;
                    font.g = 250;
                    font.b = 123;
                    break;
                case 3:
                    //font = {255, 184, 108};
                    font.r = 255;
                    font.g = 184;
                    font.b = 108;
                    break;
                case 4:
                    //font = {255, 121, 198};
                    font.r = 255;
                    font.g = 121;
                    font.b = 198;
                    break;
                case 5:
                    //font = {189, 147, 249};
                    font.r = 189;
                    font.g = 147;
                    font.b = 249;
                    break;
                case 6:
                    //font = {255, 85, 85};
                    font.r = 255;
                    font.g = 85;
                    font.b = 85;
                    break;
                case 7:
                    //font = {241, 250, 140};
                    font.r = 241;
                    font.g = 250;
                    font.b = 140;
                    break;
            }
            //delete WelcomeImage;
            WelcomeImage = new Image(Welcome.render("Welcome to Brick Breaker Neon", 
                                     font));
            //WelcomeImage.image = Welcome.render("Welcome to Brick Breaker Neon", font);
            time_count = 0;
        }
        else
        {
            ++time_count;
        }

        surface.lock();
        surface.fill(BLACK);
        surface.put_image(*WelcomeImage, WelcomeRect);
        surface.unlock();
        surface.flip();

        delay(10);
    }
}


void test_bb()
{
    const int W = 640;
    const int H = 480;
    Surface surface(W, H);
    Event event;
    Color c;
    c = WHITE;
    int r, g, b;
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
    int time_count = 0;

    //=======================================
    // create my bricks!
    //=======================================
    const int NUM_BRICKS = 30;
    Rect * bricks[NUM_BRICKS];
    int brick_positioner = 0;
    for (int i = 0; i < NUM_BRICKS; ++i)
    {
        bricks[i] = new Rect;
        if (i < NUM_BRICKS / 2)
        {   
            bricks[i]->x = 50 + ((i + 1) * 20);
            bricks[i]->y = 50; //+ ((i + 1) * 10)
        }
        else
        {
            bricks[i]->y = 75;
            bricks[i]->x = 50 + ((brick_positioner + 1) * 20);
            ++brick_positioner;
        }
        
        bricks[i]->w = 15;
        bricks[i]->h = 5;
    }
    //=======================================
    // end init bricks
    //=======================================
    

    //==========Create Ball Obj==============
    // !! use StarMedium class
    //=======================================
    StarMedium ball;
    ball.x = (W / 2) + (69 / 2);
    ball.y = H - 101;



    //=======================================
    // create paddle obj
    //=======================================
    Rect paddle;
    paddle.x = W / 2;
    paddle.y = H - 100;
    paddle.w = 69;
    paddle.h = 15;    

    //=======================================
    // main while loop
    //=======================================
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        if (time_count > 300)
        {
            r = rand() % 256;
            g = rand() % 256;
            b = rand() % 256;
            time_count = 0;
        }
        else
        {
            ++time_count;
        }

        move_paddle(paddle);  
        move_ball(paddle, ball, bricks);
         
        
        surface.lock();
        surface.fill(BLACK);
        for (int i = 0; i < NUM_BRICKS; ++i)
        {
            if (bricks[i]->state == true)
            {
                surface.put_rect(*(bricks[i]), r, g, b);
            }
        }
        surface.put_rect(paddle, r, g, b);
        ball.draw(surface);
        surface.unlock();
        surface.flip();

        delay(10);
    }

    for (int i = 0; i < NUM_BRICKS; ++i)
    {
        delete[] bricks[i];
    }

    return;
}    


/*****************************************************************************
For our programs involving graphics and sound, the template is this:

int main(int argc, char* argv[])
{
    ... PROGRAM ...

    return 0;
}

Our main() is made up of calling various functions. This is the first time you
are actually seeing the *code* of functions. Before this, you have been 
*using* functions, i.e. *calling* the functions.

For instance the first function call is

	test_event();

When you run this program, the program will execute a function call to 
test_event(). This means that the program will look for "text_event" and 
execute the code until it sees the statement "return". Executing return
will cause the program to go back to where it came from.

After running the program, comment out the call to test_event(), uncomment
the call to test_pixel() and run the program. Etc.
*****************************************************************************/
int main(int argc, char* argv[])
{
    //freopen("CON", "w", stdout);
    //freopen("CON", "w", stderr);
    
    // Prints to console window
    std::cout << "hello world" << std::endl;
    
    //test_event();
    //test_pixel();
    //test_line();
    //test_circle();
    //test_unfilled_circle();
    //test_rect();
    //test_image();
    //helloworld();	          	// Of course we must have a hello world right?
    //test_keyboard();
    //test_key_up_down(); // NEW 2013
    //test_sound();
    //fancyhelloworld();		// eye candy
    //test_polygon(false);
    //test_polygon(true);
    
    // mouse
    //test_mouse(); // NEW 2013
    //test_mouse_event(); // NEW 2013
    //test_drag_n_drop(); // NEW 2013

    // gamepad
    //test_gamepad(); // NEW 2013

    //test_star();
    //test_print_stars();
    //test_welcome();
    //test_laser();
    // bool quit = false;
    // while (1)
    // {
    //     Event event;
    //     if (event.poll() && event.type() == QUIT) break;
    //     test_welcome();
    //     int score = (test_lasers_and_aliens());
    //     quit = (game_over(score));
    //     if (quit == true)
    //     {
    //         break;
    //     }
    // }
    //test_key_up_down();
    test_bb_welcome();
    test_bb();
    
    
    //test_spaceship();
    //test_Usership();
    
    return 0;
}
