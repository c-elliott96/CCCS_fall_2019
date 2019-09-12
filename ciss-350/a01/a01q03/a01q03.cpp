// Name: Christian Elliott
// File: a01q03.cpp

#include <iostream>


bool is_prime(int i)
{
    for (int j = i - 1; j > 1; --j)
    {
        if (i % j == 0)
            return false;
    }

    return true;
}


int get_next_prime_after(int p)
{
    int i = p + 1;
    while (!is_prime(i))
    {
        ++i;
    }
    return i;
}


int main()
{
    int n;

    std::cin >> n;
    int p = 2;
    int power_count = 0;
    
    while (n != 1)
    {
        while (n % p != 0)
        {
            p = get_next_prime_after(p);
        }

        while (n % p == 0)
        {
            n = n / p;
            ++power_count;
        }

        std::cout << p;

        if (power_count > 1)
        {
            std::cout << '^' << power_count;
        }

        if (n != 1)
        { 
            std::cout << " * ";
        }
        power_count = 0;
    }

    std::cout << '\n';

    return 0;
}