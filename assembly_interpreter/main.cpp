// Author: Christian Elliott
// Date: 12.2019
// CISS-360 final

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <functional>
#include <iomanip>
#include "Interpreter.h"
#include "Functions.h"


int main()
{
  std::list < std::string > instructions;
  std::list < std::vector < unsigned int > > instructions_uint;

  // creates and itializes command map - format: unsigned int hash, string command
  std::map < unsigned int, std::string > map = map_commands();
  std::map < unsigned int, std::string > ::iterator it = map.begin();
  // while (it != map.end())
  // {
  //   std::cout << it->first << ' ' << it->second << '\n';
  //   ++it;
  // }
  // creates and itializes registers map
  //std::map < unsigned int, unsigned int > map_registers;
  std::vector < unsigned int > registers;
  create_registers_1(registers);
  std::vector < unsigned int > data;

  print_map_registers_1(registers);
  print_data(data);

  while(1)
  {
    std::cout << "Enter a PCSPIM / MIPS command: ";

    std::string input = get_input(); // get command input
    std::vector< unsigned int> uints = str_to_uint(input); // convert string into a uint vec
    tokenize_do(uints, map, registers);
    std::string str;		
    str = ascii_to_uint(uints); // turn uints back into chars (not sure if this is necessary

    // =========== SAVES INSTRUCTIONS ========== 
    instructions.push_back(input); // store instructions (in a doubly linked list)
    instructions_uint.push_back(uints); // also a doubly linked list - of uint vectors!
    // if (!instructions.empty())	  // this block prints instructions - for debugging
    // 	{
    // 	  std::list < std::string > ::iterator it;
    // 	  int i = 0;
    // 	  for (it = instructions.begin(); it != instructions.end(); ++it)
    // 	    {
    // 	      std::cout << *it << ' ';
    // 	      ++i;
    // 	    }
    // 	  std::cout << '\n';
    // 	}
    // ============ END ===============================

    // tokenize() parses unsigned int vector
    //tokenize(uints);
    
    print_map_registers_1(registers);
    //print_instructions_uint(instructions_uint);
    //interpret(uints);
    //std::cout << "Hashed command: " << hash(uints) << '\n';
  }
}
