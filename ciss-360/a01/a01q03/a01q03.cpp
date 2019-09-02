// File: a01q03.cpp 
// Author: Christian Elliott

#include <iostream>

int main()
{
    int x = 0;
    std::cin >> x;

    for (int i = 0; i < x; ++i)
    {
        std::cout << i << std::endl;
    }

    /*********************************
    very simple C/C++ code below
    
    int x = 0;
    std::cin >> x;

    int i = 0;
    if (i < x) goto l1;

    l1: std::cout << i << std::endl;
        i = i + 1;

    if (!(i < x)) goto l2;

    l2: return 0;
    *********************************/

    return 0;
}