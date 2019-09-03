// Name: Christian Elliott
// File: a01q01.cpp 

#include <iostream>


void draw_spiral(int n)
{
    int total_lines = 5 * n - (n - 1);
    int even_counter = 0;
    int odd_counter = 0;
    int num_pipes = 1; // FIX THIS PART!!!

    for (int i = 0; i < total_lines; ++i)
    {
        for (int j = 0; j < num_pipes; ++j)
        {
            std::cout << "|  ";
        }

        if (i % 2 == 0) // if i is even 
        {
            if (i == 0)
            {
                std::cout << '+';
            }

            for (int j = 0; j < 6 * n + 2 - even_counter; ++j)
            {
                std::cout << '-';
            }

            if (i == 0)
            {
                std::cout << '+';
            }
            
            if (i < (total_lines / 2)) // if top half
            {
                even_counter += 4;
                if (i % 2 != 0)
                {
                    ++num_pipes;
                }
            }
            else 
            {
                even_counter -= 4;
                if (i % 2 != 0)
                {
                    --num_pipes;
                }
            }
        }

        else // if i is odd
        {
            std::cout << '|';
            for (int j = 0; j < 6 * n + 2; ++j)
            {
                std::cout << ' ';
            }
            std::cout << '|';
        }
        for (int j = 0; j < num_pipes; ++j)
        {
            std::cout << "  |";
        }
        std::cout << '\n';
    }
}


int main()
{
    int n; 
    std::cin >> n;
    draw_spiral(n);

    return 0;
}