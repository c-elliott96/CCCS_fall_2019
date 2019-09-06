// File: a01q02.cpp
// Name: Christian Elliott

#include <iostream>


void draw_rising_hills(int n)
{
    int n_counter = n;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n_counter * (n_counter - 1); ++j)
        {
            std::cout << ' ';
        }
        std::cout << '*' << '\n';
        
        if (i > 2)
        {
            for (int j = 1; j <= i; ++j)
            {
                std::cout << 
            }
        }
        --n_counter;
    }
}


int main()
{
    int n;
    std::cin >> n;

    draw_rising_hills(n);
    return 0;
}