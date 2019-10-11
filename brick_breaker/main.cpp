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


const int NUM_BRICKS = 50;

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


void reset_life(Rect & paddle, StarMedium & ball, Rect * bricks[],
 bool & new_life, Event & event)
{
    paddle.x = W / 2;
    paddle.y = H - 100;
    ball.x = paddle.x + (paddle.w / 2);
    ball.y = paddle.y - 1;
    while(1)
    {
        if (event.poll() && event.type() == QUIT) break;
        KeyPressed keypressed = get_keypressed();
        if (keypressed[SPACE])
        {
            new_life = false;
            break;
        }
    }
}


void move_ball(const Rect & paddle, StarMedium & ball, 
               Rect * bricks[], bool & new_life)
{
    //const int num_bricks = 30;
    int x;
    ball_brick_hit(bricks, ball, NUM_BRICKS);
    ball_paddle_hit(paddle, ball);
    if (ball.y <= 0)
    { 
        ball.dy = 1;
    }
    else if (ball.y >= H)
    {
        // implement LOSE LIFE AND RESET FUNCTION and call function here
        new_life = true;
        ball.dy = -1;
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

    Font WelcomeSpace("fonts/NovaMono-Regular.ttf", 15);
    Image * SpaceImage = new Image(WelcomeSpace.render("Please Press SPACE to Continue", font));
    Rect WelcomeSpaceRect = SpaceImage->getRect();
    WelcomeSpaceRect.x = 50;
    WelcomeSpaceRect.y = 150;
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
            SpaceImage = new Image(WelcomeSpace.render("Please Press SPACE to Continue", font));;
            //WelcomeImage.image = Welcome.render("Welcome to Brick Breaker Neon", font);
            time_count = 0;
        }
        else
        {
            ++time_count;
        }

        KeyPressed keypressed = get_keypressed();
        if (keypressed[SPACE])
        {
            return;
        }

        surface.lock();
        surface.fill(BLACK);
        surface.put_image(*WelcomeImage, WelcomeRect);
        surface.put_image(*SpaceImage, WelcomeSpaceRect);
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
    bool new_life = true;

    //=======================================
    // create my bricks!
    //=======================================
    //const int NUM_BRICKS = 30;
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

        if (new_life)
        {
            reset_life(paddle, ball, bricks, new_life, event);
        }
        move_paddle(paddle);  
        move_ball(paddle, ball, bricks, new_life);
         
        
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
    // test_print_stars();
    // test_welcome();
    // test_laser();
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
