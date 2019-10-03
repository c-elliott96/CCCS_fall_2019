// File: a01q01.cpp 
// Author: Christian Elliott

#include <iostream>

int main()
{
    int x = 0;
    std::cin >> x;

    int y = 0;
    if (x < 0)
    {
        std::cout << "foo" << std::endl;
        y = 1;
    }
    else
    {
        std::cout << "bar" << std::endl;
        y = 2;
    }

    /***********************************
    same as above using goto and not else
    if (x < 0) goto l1;

    l1: std::cout << "foo" << std::endl;
        y = 1;

    if (!(x < 0)) goto l2;

    l2: std::cout << "bar" << std::endl;
        y = 2;
    ***********************************/

    std::cout << y << std::endl;
    return 0;
}