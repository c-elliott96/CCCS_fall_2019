/****************************************************************************
 By Christian Elliott
 Library created by Dr. Liow, CCCS 
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
#include <stdio.h>
#include <stdlib.h>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"


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
template < typename x >
std::ostream &operator<<(std::ostream &cout, std::vector < x > arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i] << ',';
        if (i % 10 == 0) cout << '\n';
    }
    return cout;
}   


int NUM_BRICKS = 50;
const int W = 640;
const int H = 480;
int SCORE = 0;
int LEVEL = 0;
// const int W = 740;
// const int H = 580;
// const int W = 940;
// const int H = 780;

// const int W = 1980;
// const int H = 1020;


/* A utility function to reverse a string  */
void reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        //swap(*(str+start), *(str+end)); 
        char t = *(str+start);
        str[start] = *(str+end);
        str[end]= t;
        start++; 
        end--; 
    } 
} 
  
// Implementation of itoa() 
char* itoa(int num, char* str, int base) 
{ 
    int i = 0; 
    bool isNegative = false; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = true; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
} 


bool ball_brick_hit(std::vector < Rect > &bricks, StarMedium & ball, const int NUM_BRICKS)
{
    for (int i = 0; i < NUM_BRICKS; ++i)
    {
        if (ball.x >= bricks[i].x &&
            ball.x <= bricks[i].x + bricks[i].w && 
            ball.y >= bricks[i].y && 
            ball.y <= bricks[i].y + bricks[i].h &&
            bricks[i].state == true)
            {
                std::cout << "collision detected\n";
                if (ball.dx < 0 && ball.dy < 0) // ball is moving up and left
                {
                    ball.dy = 1.25;
                }
                else if (ball.dx == 0 && ball.dy < 0) // if ball is moving straight up
                {
                    ball.dy = 1.25;
                }
                else if (ball.dy > 0) // ball is moving down
                {
                    ball.dy = -1.25;
                }
                else if (ball.dy < 0 && ball.dx > 0)// if ball is moving up and right
                {
                    ball.dy = 1.25;
                }
                bricks[i].state = false;
                SCORE += 10;
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
            if (ball.x <= paddle_m) // ball collides w/ left side of paddle
            {
                ball.dx = -1 * ((paddle_m - ball.x) * paddle_factor);
                ball.dy = -1.25;
            }
            if (ball.x > paddle_m)
            {
                ball.dx = 1 * (ball.x - paddle_m) * paddle_factor;
                ball.dy = -1.25;
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


void reset_life(Rect & paddle, StarMedium & ball, const std::vector < Rect > &bricks,
                bool & new_life, Event & event, 
                const int NUM_BRICKS, Surface & surface)
{
    Color c;
    c = WHITE;
    int r, g, b;
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
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

        surface.lock();
        surface.fill(BACKGROUND);
        for (int i = 0; i < NUM_BRICKS; ++i)
        {
            if (bricks[i].state == true)
            {
                surface.put_rect(bricks[i], r, g, b);
            }
        }
        surface.put_rect(paddle, r, g, b);
        ball.draw(surface);
        surface.unlock();
        surface.flip();

        delay(10);
    }
}


void move_ball(const Rect & paddle, StarMedium & ball, 
               std::vector < Rect > & bricks, bool & new_life)
{
    //const int num_bricks = 30;
    int x;
    ball_brick_hit(bricks, ball, NUM_BRICKS);
    ball_paddle_hit(paddle, ball);
    if (ball.y <= 0)
    { 
        ball.dy = 1.0;
    }
    else if (ball.y >= H)
    {
        // implement LOSE LIFE AND RESET FUNCTION and call function here
        new_life = true;
        ball.dy = -1.0;
    }
    else if (ball.x <= 0) // ball hits left wall
    {
        ball.dx *= -1.0;
    }
    else if (ball.x >= W)
    {
        ball.dx *= -1.0;
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
            paddle.x -= 4;
        }
    }
    else if (keypressed[RIGHTARROW])
    {
        // move right!
        if (paddle.x < W - paddle.w)
        {
            paddle.x += 4;
        }
    }
}


void test_bb_welcome()
{
    // const int W = 640;
    // const int H = 480;
    Surface surface(W, H);
    Event event;
    Font Welcome("fonts/NovaMono-Regular.ttf", 33);
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
    //Image * WelcomeImage = new Image(Welcome.render("Welcome to Brick Breaker Neon", 
    //                                 font));
    // Rect WelcomeRect = WelcomeImage->getRect();
    // WelcomeRect.x = 50;
    // WelcomeRect.y = 50;
    int time_count = 0;

    Font WelcomeSpace("fonts/NovaMono-Regular.ttf", 17);
    //Image * SpaceImage = new Image(WelcomeSpace.render("Please Press SPACE to Continue", font));
    // Rect WelcomeSpaceRect = SpaceImage->getRect();
    // WelcomeSpaceRect.x = W / 2 - 50;
    // WelcomeSpaceRect.y = H - 100;
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        Image WelcomeImage(Welcome.render("Welcome to Brick Breaker Neon", font));
        Rect WelcomeRect = WelcomeImage.getRect();
        WelcomeRect.x = 50;
        WelcomeRect.y = 50;

        Image SpaceImage(WelcomeSpace.render("Please Press SPACE to Continue", font));
        Rect WelcomeSpaceRect = SpaceImage.getRect();
        WelcomeSpaceRect.x = W / 2 - 50;
        WelcomeSpaceRect.y = H - 100;
        
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
        surface.fill(BACKGROUND);
        surface.put_image(WelcomeImage, WelcomeRect);
        surface.put_image(SpaceImage, WelcomeSpaceRect);
        surface.unlock();
        surface.flip();

        delay(10);
    }
}


Image render_lives(int num_lives, FontImage & livesFont)
{
    Color font = {255, 255, 255};
    char lives[10] = {'3'};
    switch (num_lives)
    {
        case 0:
            lives[0] = '0';
            break;
        case 1:
            lives[0] = '1';
            break;
        case 2:
            lives[0] = '2';
            break;
        case 3:
            lives[0] = '3';
            break;
    }
    // Image * livesImage = new Image(livesFont.render(lives, font));

    Image livesImage(livesFont.render(lives, font));
    //Rect livesRect = livesImage->getRect();
    return livesImage;
}


Image render_score(int SCORE, FontImage & scoreFont)
{
    // convert our int SCORE to a string or a char ??
    Color font {255, 255, 255};
    char score[10];
    //Image * scoreImage = new Image(scoreFont.render((itoa(SCORE, score, 10)), font));
    Image scoreImage(scoreFont.render((itoa(SCORE, score, 10)), font));
    //Rect scoreRect = scoreImage->getRect();
    return scoreImage;
}


void reset_level(std::vector < Rect > &bricks)
{
    for (int i = 0; i < NUM_BRICKS; ++i)
    {
        bricks[i].state = true;
    }
}


void init_new_bricks(std::vector < Rect > &bricks, int NUM_BRICKS)
{
    // upon advancing a level, we want to expand our Rect * array by 25
    
    // for (int i = 0; i < NUM_BRICKS; ++i)
    // {
    //     bricks[i]
    // }
}


void test_bb()
{
    // const int W = 640;
    // const int H = 480;
    Surface surface(W, H);
    Event event;
    Color c;
    c = WHITE;
    int r, g, b;
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
    int time_count = 0;
    bool new_life = false;

    //=======================================
    // create my bricks!
    //=======================================
    //const int NUM_BRICKS = 30;
    //Rect * bricks[NUM_BRICKS];
    std::vector < Rect > bricks;

    int brick_positioner = 0;

    for (int i = 0; i < NUM_BRICKS; ++i)
    {
        Rect temp(0,0,15,5);
        bricks.push_back(temp);
        if (i < NUM_BRICKS / 2 + LEVEL)
        {   
            bricks[i].x = 50 + ((i + 1) * 20);
            bricks[i].y = 50; //+ ((i + 1) * 10)
        }
        else
        {
            bricks[i].y = 75;
            bricks[i].x = 50 + ((brick_positioner + 1) * 20);
            ++brick_positioner;
        }
        
        //bricks[i].w = 15;
        //bricks[i].h = 5;
    }
    //std::cout << bricks << std::endl;

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


    FontImage livesFont("fonts/NovaMono-Regular.ttf", 20);
    livesFont.rect.x = 20;
    livesFont.rect.y = H - 50;

    FontImage scoreFont("fonts/NovaMono-Regular.ttf", 20);
    scoreFont.rect.x = W - 70;
    scoreFont.rect.y = H - 50;

    int num_lives = 3;
    //=======================================
    // main while loop
    //=======================================
    bool level_up = true;

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
            --num_lives;
            reset_life(paddle, ball, bricks, new_life, event, 
            NUM_BRICKS, surface);
        }
        move_paddle(paddle);  
        move_ball(paddle, ball, bricks, new_life);
        render_lives(num_lives, livesFont);
        surface.lock();
        surface.fill(BACKGROUND);
        for (int i = 0; i < NUM_BRICKS; ++i)
        {
            if (bricks[i].state == true)  // state == true means the brick is 'alive'
            {
                surface.put_rect(bricks[i], r, g, b);
                level_up = false;
            }
        }
        if (level_up)
            {
                std::cout << "in level up\n";
                ++LEVEL;
                NUM_BRICKS += 25;
                init_new_bricks(bricks, NUM_BRICKS);
                reset_level(bricks);
            }

        surface.put_rect(paddle, r, g, b);
        surface.put_rect(livesFont.rect, r, g, b);
        surface.put_image(render_lives(num_lives, livesFont), 
                            livesFont.rect);
        surface.put_image(render_score(SCORE, scoreFont),
                            scoreFont.rect);
        ball.draw(surface);
        surface.unlock();
        surface.flip();

        delay(10);
        level_up = true;        
    }

    // for (int i = 0; i < NUM_BRICKS; ++i)
    // {
    //     delete[] bricks[i];
    // }
    

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
