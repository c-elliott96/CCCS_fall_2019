// File: a01q02.cpp
// Name: Christian Elliott

#include <iostream>


void draw_rising_hills(int n)
{
    int n_counter = n;
    int star_count = 1;
    int spaces = ((n - 1) * 2) - 2;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n_counter * (n_counter - 1); ++j)
        {
            std::cout << ' ';
        }

        for (int j = 1; j <= i; ++j)
        {
            for (int k = 1; k <= star_count; ++k)
            {
                std::cout << '*';
            }

            for (int k = 1; k <= spaces; ++k) // spaces after 1st star of each
                                                        //  iteration of i
            {
                std::cout << ' ';
            }

            star_count += 2;
        } 

        star_count = 1;
        if (i > 1)
        {
            spaces -= 2; 
        }
        std::cout << '\n'; 
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
