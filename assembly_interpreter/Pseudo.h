#ifndef PSEUDO_H
#define PSEUDO_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <functional>
#include <iomanip>

unsigned int get_registers (std::string in)
{    
    std::cout << '*' << in << '*' << '\n';
    if (in == "r0")
    {
        return 0;
    }
    else if (in == "at")
    {
        return 1;
    }
    else if (in == "v0")
    {
        return 2;
    }
    else if (in == "v1")
    {
        return 3;
    }
    else if (in == "a0")
    {
        return 4;
    }
    else if (in == "a1")
    {
        return 5;
    }
    else if (in == "a2")
    {
        return 6;
    }
    else if (in == "a3")
    {
        return 7;
    }
    else if (in == "t0")
    {
        return 8;
    }
    else if (in == "t1")
    {
        return 9;
    }
    else if (in == "t2")
    {
        return 10;
    }
    else if (in == "t3")
    {
        return 11;
    }
    else if (in == "t4")
    {
        return 12;
    }
    else if (in == "t5")
    {
        return 13;
    }
    else if (in == "t6")
    {
        return 14;
    }
    else if (in == "t7")
    {
        return 15;
    }
    else if (in == "s0")
    {
        return 16;
    }
    else if (in == "s1")
    {
        return 17;
    }
    else if (in == "s2")
    {
        return 18;
    }
    else if (in == "s3")
    {
        return 19;
    }
    else if (in == "s4")
    {
        return 20;
    }
    else if (in == "s5")
    {
        return 21;
    }
    else if (in == "s6")
    {
        return 22;
    }
    else if (in == "s7")
    {
        return 23;
    }
    else if (in == "t8")
    {
        return 24;
    }
    else if (in == "t9")
    {
        return 25;
    }
    else if (in == "k0")
    {
        return 26;
    }
    else if (in == "k1")
    {
        return 27;
    }
    else if (in == "gp")
    {
        return 28;
    }
    else if (in == "sp")
    {
        return 29;
    }
    else if (in == "s8")
    {
        return 30;
    }
    else if (in == "ra")
    {
        return 31;
    }
    else if (in == "pc")
    {
        return 32;
    }
    else if (in == "hi")
    {
        return 33;
    }
    else if (in == "lo")
    {
        return 34;
    }
    else return 9999999;
}


int char_to_int(std::string str)
{
    int sum = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        int j = (int(str[i]) - 48) * 10;
        sum += j;
    }
    std::cout << sum << '\n';
    return sum;    
}


void pseudo_add(std::map < unsigned int, unsigned int > & registers_map, 
std::vector < std::string > whole_string)
{
    unsigned int a = get_registers(whole_string[1]);
    unsigned int b = get_registers(whole_string[2]);
    unsigned int c = get_registers(whole_string[3]);

    registers_map[a] = registers_map[b] + registers_map[c];
}


void pseudo_li(std::map < unsigned int, unsigned int > & registers_map,
std::vector < std::string > whole_string)
{
    //format: li $t0, const
    unsigned int a;
    std::cout << get_registers(whole_string[1]);
    a = get_registers(whole_string[1]);
    //int b = char_to_int(whole_string[2]);
    //b = unsigned(b);
    std::cout << "Register " << a << " = ";
    //std::cout << b << '\n';
    //registers_map[a] = b;
}


#endif