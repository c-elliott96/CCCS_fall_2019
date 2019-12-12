#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <functional>
#include "Functions.h"


class tok
{
public:
    std::string token;
    bool is_command;
    bool is_register;
    bool is_constant;
    // might need to add a "is_data" or similar member later
    void determine_type();
    tok()
    {
        is_command = false;
        is_register = false;
        is_constant = false;
    }
};


void tok::determine_type()
{
    std::string::iterator it = token.begin();
    
}


#endif
