// Name: Christian Elliott
// File: a01q04.cpp

#include <iostream>


void increment(int digits[], int len_digits, int base)
{
    
}


void print(int digits[], int len_digits)
{
    for (int i = 0; i < len_digits; ++i)
    {
        std::cout << digits[i] << ',';
    }
    std::cout << std::endl;
}


int main()
{
    int digits[4] = {0};
    for (int i = 0; i < 100; ++i)
    {
        print(digits, 4);
        increment(digits, 4, 16);
    }
 
    return 0;
}