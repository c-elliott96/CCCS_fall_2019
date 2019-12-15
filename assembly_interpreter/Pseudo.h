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
    //std::cout << in << '\n';
    for (int i = 0; i < in.size(); ++i)
    {
        if (in[i] == '$')
        {
            in.erase(0, 1);
        }
    }
    // std::cout << "get_registers() string in = ";
    // std::cout << '*' << in << '*' << '\n';
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


unsigned int char_to_int(std::string str)
{
    int sum_int = stoi(str);
    return unsigned(sum_int);    
}


void pseudo_add(std::vector < unsigned int > & registers, 
std::string reg_0, std::string reg_1, std::string reg_2)
{
    unsigned int reg0 = registers[get_registers(reg_0)];
    unsigned int reg1 = registers[get_registers(reg_1)];
    unsigned int reg2 = registers[get_registers(reg_2)];
    std::cout << "reg0 = " << reg0 << '\n';
    std::cout << "reg1 = " << reg1 << '\n';
    std::cout << "reg2 = " << reg2 << '\n';
    registers[get_registers(reg_0)] = reg1 + reg2;
}


void pseudo_li(std::vector < unsigned int > & registers,
std::string reg_0, std::string const_immed)
{
    //format: li $reg_0, const_immed
    unsigned int reg = get_registers(reg_0);
    unsigned int immed = char_to_int(const_immed);
    //std::cout << reg << '\n';
    registers[reg] = immed;
    //std::cout << immed << '\n';
    //std::cout << registers_map[reg];
}


void pseudo_sub(std::vector < unsigned int > & registers, 
std::string reg_0, std::string reg_1, std::string reg_2)
{
    unsigned int reg0 = registers[get_registers(reg_0)];
    unsigned int reg1 = registers[get_registers(reg_1)];
    unsigned int reg2 = registers[get_registers(reg_2)];
    std::cout << "reg0 = " << reg0 << '\n';
    std::cout << "reg1 = " << reg1 << '\n';
    std::cout << "reg2 = " << reg2 << '\n';
    registers[get_registers(reg_0)] = reg1 - reg2;
}

#endif