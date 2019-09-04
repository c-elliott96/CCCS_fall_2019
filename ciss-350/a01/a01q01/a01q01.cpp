// Name: Christian Elliott
// File: a01q01.cpp 

#include <iostream>


void draw_spiral(int n)
{
    int total_lines = 5 * n - (n - 1);
    int even_counter = 0;
    int odd_counter = 0;
    int num_pipes = 0; 
    int dashes = 6 * n + 2;
    bool dashes_reset = false;
    bool spaces_reset = false;
    bool pipes_reset = false;
    int spaces = dashes - 4;
    int pipes_count = 0;

    for (int i = 0; i < total_lines; ++i) // OUTER FOR LOOP
    {
        // std::cout << i << ' ';
        
        // ****************************
        // i is EVEN (0, 2, 4, 6, 8 ...)
        // ****************************

        if (i % 2 == 0)
        {
            if (i <= total_lines / 2) // if TOP HALF OF EVEN
            {
                for (int j = 0; j < num_pipes; ++j) // print pipes
                {
                    std::cout << "|  ";
                }

                std::cout << '+';
                for (int j = 0; j < dashes; ++j)
                {
                    std::cout << '-';
                }
                std::cout << '+';

                for (int j = 0; j < num_pipes; ++j) // print pipes
                {
                    std::cout << "  |";
                }

                if (dashes == 2) // RESET DASHES TO 5
                {
                    dashes = 5;
                    dashes_reset = true;
                }

                dashes -= 6;
                ++num_pipes;
            }
            else // BOTTOM HALF OF EVEN
            {
                for (int j = 0; j < num_pipes; ++j) // print pipes
                {
                    std::cout << "|  ";
                }

                std::cout << '+';
                for (int j = 0; j < dashes; ++j)
                {
                    std::cout << '-';
                }
                std::cout << '+';

                for (int j = 0; j < num_pipes - 1; ++j) // print pipes
                {
                    std::cout << "  |";
                }
            }
        }
        // *****************************
        // END BLOCK OF EVEN i
        // *****************************


        // *****************************
        // START ODD BLOCK
        // *****************************
        else 
        {
            if (i <= total_lines / 2) // if top half of odd
            {
                for (int j = 0; j < num_pipes; ++j)
                {
                    std::cout << "|  ";
                }

                for (int j = 0; j < spaces; ++j)
                {
                    std::cout << ' ';
                }

                for (int j = 0; j < num_pipes; ++j)
                {
                    std::cout << "  |";
                }
                spaces -= 6;
            }

            else // bottom half of odd iterations
            {
                if (!spaces_reset)
                {
                    spaces_reset = true;
                    spaces = 1;
                }

                for (int j = 0; j < num_pipes; ++j)
                {
                    std::cout << "|  ";
                }

                if (num_pipes == n + 1)
                {
                    pipes_reset = true;
                }

                /* if (num_pipes > n + 1)
                {
                    pipes_reset = true;
                } */

                if (pipes_reset)
                {
                    --num_pipes;
                }

                for (int j = 0; j < spaces; ++j)
                {
                    std::cout << ' ';
                }

                for (int j = 0; j < num_pipes; ++j)
                {
                    std::cout << "  |";
                }
                
                if (dashes_reset)
                {
                    dashes += 6;
                    spaces += 6;
                }   
            }
        }

        // *************************
        // END ODD BLOCK
        // *************************

        /* std::cout << "    Spaces: " << spaces;
        std::cout << "    Dashes: " << dashes;
        std::cout << "    Pipes: " << num_pipes;
        std::cout << "    Dashes Reset? " << dashes_reset; */
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