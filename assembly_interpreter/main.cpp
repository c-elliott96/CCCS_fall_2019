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
#include "Interpreter.h"


// use for taking in std::string input
std::string get_input(std::string &S)
{
  std::getline(std::cin, S);
  return S;
}


// use if I don't want to initialize input string outside of function
std::string get_input()
{
  std::string output;
  std::getline(std::cin, output);
  return output;
}


// convert string into a uint vector and return uint vector
std::vector< unsigned int > str_to_uint(std::string & S)
{
  std::vector< unsigned int > ints;
  std::string::iterator it;
  int i = 0;
  for (it = S.begin(); it != S.end(); ++it)
    {
      unsigned int x = unsigned(int(*it));
      ints.push_back(x);
      ++i;
    }
  return ints;  
}


// convert uint vector back to char (in std::string)
std::string ascii_to_uint(const std::vector< unsigned int > & x)
{
  std::string ret;
  for (int i = 0; i < x.size(); ++i)
    {
      ret.push_back(char(x[i]));
    }
  return ret;
}


// finds first substring ... not sure if needed 
void tokenize(const std::vector < unsigned int > & x)
{
  std::string substring;
  int i = 0;
  while (i < x.size() && x[i] != 32)
    {
      substring.push_back(char(x[i]));
      ++i;
    }
}


unsigned int hash(const unsigned int x)
{
  std::hash < unsigned int > y;
  //std::cout << "Hashed uint: ";
  // std::cout << y(x) << '\n';
  unsigned int ret = y(x);
  return ret;
}


unsigned int hash(const std::vector < unsigned int > x)
{
  std::hash < unsigned int > y;

  unsigned int sum = 0;
  for (int i = 0; i < x.size(); ++i)
    {
      sum += x[i];
    }
  //std::cout << "Hashed uint: ";
  // std::cout << y(x) << '\n';
  unsigned int ret = y(sum);
  return ret;
}


// this function produces the substring that occurs before first space in command
std::vector < unsigned int > interpret(std::vector < unsigned int > x)
{
  std::vector < unsigned int > substring;
  int i = 0;
  while (i < x.size() && x[i] != 32)
    {
      substring.push_back(x[i]);
      ++i;
    }
  
  return substring;
}


void create_registers(std::map < int, unsigned int > & map)
{
  for (int i = 0; i < 32; ++i)
    {
        map.insert(std::pair< int , unsigned int > (i , 0));
    }
}


void print_registers(std::map < int, unsigned int > map)
{
  std::map < int, unsigned int > :: iterator it = map.begin();
  std::cout << "Registers: " << '\n';
  while (it != map.end())
    {
      std::cout << '\t' << it->first << '\t' << it->second << '\n';
      ++it;
    }
}


void print_instructions_uint(std::list < std::vector < unsigned int > > instructions)
{
  std::list < std::vector < unsigned int > > :: iterator it;
  it = instructions.begin();
  int i = 0;
  while(it != instructions.end())
    {
      std::cout << "Instruction # " << i << '\n';
      for (auto j = 0; j < it->size(); ++j)
	{
	  std::cout << it->at(j) << ' ';
	}
      std::cout << '\n';
      ++it;
      ++i;
    }
}


void print_hashes()
{
  std::list < std::vector < unsigned int > > master;
  std::list < std::string > master_list;
  while(1)
    {
      std::string input = get_input();
      if (input == "-1")
	{
	  break;
	}
      master.push_back(str_to_uint(input));
      master_list.push_back(input);
    }
  std::list < std::string > :: iterator it;
  std::list < std::vector <unsigned int > > :: iterator it2;
  it = master_list.begin();
  it2 = master.begin();

  int i = 0;
  while(it != master_list.end())
    {
      std::cout << *(it) << '\t';
      std::cout << hash(*(it2)) << '\n';
      ++i;
      ++it;
      ++it2;
    }
}


/* ============ HASHES FOR ALL POSSIBLE EXPECTED COMMANDS =================
add	297
addi	402
addiu   519
addu	414
and	307
andi	412
beq	312
bgez	424
bgezal	629
bgtz	439
blez	429
bltz	444
bltzal	649
bne	309
div	323
divu	440
j	106
jal	311
jr	220
lb	206
lui	330
lw	227
mfhi	420
mflo	430
mult	450
multu	567
noop	444
or	225
ori	330
sb	213
sll	331
sllv	449
slt	339
slti	444
sltiu	561
sltu	456
sra	326
srl	337
srlv	455
sub	330
subu	447
sw	234
syscall	763
xor	345
xori	450
*/

		  
// void do_action(std::vector < unsigned int > command)
// {
//   std::vector < unsigned int > pseudo;
//   pseudo.push_back(interpret(command));
//   unsigned int x = hash(pseudo);
//   switch (x)
//     {
//       //
//     }
// }


int main()
{
  std::list < std::string > instructions;
  std::list < std::vector < unsigned int > > instructions_uint;

  print_hashes();
  return 0;
  
  while(1)
    {
      std::cout << "Give me a string: ";

      std::string input = get_input(); // get command input
      std::vector< unsigned int> uints = str_to_uint(input); // convert string into a uint vec

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
      std::map < int , unsigned int > map;
      create_registers(map);
      //print_registers(map);
      //print_instructions_uint(instructions_uint);
      interpret(uints);
      std::cout << "Hashed command: " << hash(uints) << '\n';
    }
}
