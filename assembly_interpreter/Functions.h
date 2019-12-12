#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <functional>

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


void create_registers(std::map < unsigned int, unsigned int > & map)
{
  for (unsigned int i = 0; i < 32; ++i)
    {
        map.insert(std::pair< unsigned int , unsigned int > (i , 0));
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


/* ============ HASHES FOR ALL POSSIBLE EXPECTED COMMANDS =================
{
  add	    297    597
  addi	  402    1017    
  addiu   519    1602
  addu    414    1065
  and     307    617
  andi    412    1037
  beq     312    639
  bgez    424    1095
  bgezal	629    2228
  bgtz	  439    1140
  blez	  429    1105
  bltz	  444    1150    slti AND noop conflict
  bltzal	649    2283
  bne	    309    621
  div	    323    664    
  divu	  440    1132
  j	      106    106
  jal	    311    624
  jr	    220    334
  lb	    206    304
  lui	    330    657    ori conflicts
  lw	    227    346
  mfhi	  420    1045
  mflo	  430    1081
  mult	  450    1131
  multu	  567    1716
  noop	  444    1113    slti AND bltz conflict
  or	    225    339
  ori	    330    654    lui conflicts
  sb	    213    311
  sll	    331    655
  sllv	  449    1127
  slt	    339    679
  slti	  444    1099    bltz AND noop conflict
  sltiu	  561    1684
  sltu	  456    1147
  sra	    326    634
  srl	    337    667
  srlv	  455    1139
  sub	    330    643     ori AND lui conflict
  subu	  447    1111
  sw	    234    353
  syscall	763    2987
  xor	    345    684
  xori	  450    1104
}*/


unsigned int alt_hash (std::string str)
{
  std::vector< unsigned int > ints;
  std::string::iterator it;
  int i = 1;
  for (it = str.begin(); it != str.end(); ++it)
    {
      unsigned int x = i * (unsigned(int(*it)));
      ints.push_back(x);
      ++i;
    }
  unsigned int sum = 0;
  for (int j = 0; j < ints.size(); ++j)
    {
      sum += ints[j];
    }
  //std::cout << sum << '\n';
  return sum;
}


void do_action(std::string & command, std::map < unsigned int, std::string > map, 
               std::map < unsigned int, unsigned int > reg_map)
{
  // here, we use str_to_int to convert input string to unsigned int vector
  std::vector < unsigned int > uint_command = str_to_uint(command);

  // now, we pass unsigned int vector into interpret to look for whitespace 
  // (and return first "word") of the command string. returned as unsigned int substring.
  std::vector < unsigned int > uint_command_token = interpret(uint_command);

  // convert uint_command_token back into string .... to then be hashed
  std::string tok_str = ascii_to_uint(uint_command_token);
  // hash tok_str to see if hash exists in map
  unsigned int tok = alt_hash(tok_str);

  bool command_exists = false;
  std::map < unsigned int, std::string > :: iterator it = map.begin();
  while (it != map.end())
  {
    if (it->first == tok)
    {
      command_exists = true;
      break;
    }
    else
    ++it;
  }

  if (command_exists)
  {
    // determine what kind of command it is, then run function for that command
    std::cout << "command exists!\n";
  }
  else
  {
    std::cout << "Invalid input - try checking your syntax\n";
    return;
  }
}


std::map < unsigned int, std::string > map_commands()
{
  std::list < std::string > list;
  std::string a = "add";
  list.push_back(a); 

  // create strings to hash
  {
    a.clear();
    a = "addi";
    list.push_back(a);
    a.clear();
    a = "addiu";
    list.push_back(a);
    a.clear();
    a = "addu";
    list.push_back(a);
    a.clear();

    a = "and";
    list.push_back(a);
    a.clear();
    a = "andi";
    list.push_back(a);
    a.clear();
    a = "beq";
    list.push_back(a);
    a.clear();

    a = "bgez";
    list.push_back(a);
    a.clear();
    a = "bgezal";
    list.push_back(a);
    a.clear();
    a = "bgtz";
    list.push_back(a);
    a.clear();

    a = "blez";
    list.push_back(a);
    a.clear();
    a = "bltz";
    list.push_back(a);
    a.clear();
    a = "bltzal";
    list.push_back(a);
    a.clear();

    a = "bne";
    list.push_back(a);
    a.clear();
    a = "div";
    list.push_back(a);
    a.clear();
    a = "divu";
    list.push_back(a);
    a.clear();

    a = "j";
    list.push_back(a);
    a.clear();
    a = "jal";
    list.push_back(a);
    a.clear();
    a = "jr";
    list.push_back(a);
    a.clear();

    a = "lb";
    list.push_back(a);
    a.clear();
    a = "lui";
    list.push_back(a);
    a.clear();
    a = "lw";
    list.push_back(a);
    a.clear();

    a = "mfhi";
    list.push_back(a);
    a.clear();
    a = "mflo";
    list.push_back(a);
    a.clear();
    a = "mult";
    list.push_back(a);
    a.clear();

    a = "multu";
    list.push_back(a);
    a.clear();
    a = "noop";
    list.push_back(a);
    a.clear();
    a = "or";
    list.push_back(a);
    a.clear();

    a = "ori";
    list.push_back(a);
    a.clear();
    a = "sb";
    list.push_back(a);
    a.clear();
    a = "sll";
    list.push_back(a);
    a.clear();

    a = "sllv";
    list.push_back(a);
    a.clear();
    a = "slt";
    list.push_back(a);
    a.clear();
    a = "slti";
    list.push_back(a);
    a.clear();

    a = "sltiu";
    list.push_back(a);
    a.clear();
    a = "sltu";
    list.push_back(a);
    a.clear();
    a = "sra";
    list.push_back(a);
    a.clear();

    a = "srl";
    list.push_back(a);
    a.clear();
    a = "srlv";
    list.push_back(a);
    a.clear();
    a = "sub";
    list.push_back(a);
    a.clear();

    a = "subu";
    list.push_back(a);
    a.clear();
    a = "sw";
    list.push_back(a);
    a.clear();
    a = "syscall";
    list.push_back(a);
    a.clear();

    a = "xor";
    list.push_back(a);
    a.clear();
    a = "xori";
    list.push_back(a);
    a.clear();
  }

  std::vector < unsigned int > uints;
  std::list < std::string > ::iterator it;
  for (it = list.begin(); it != list.end(); ++it)
  {
    // std::cout << "hashing ";
    // std::cout << *(it) << " ... ";
    uints.push_back(alt_hash((*it)));
  }

  // push key (hash) and string (command) into map
  std::map < unsigned int, std::string > map;
  int i = 0;
  for (it = list.begin(); it != list.end(); ++it)
  {
    map.insert ( std::pair < unsigned int, std::string > ( uints[i], *(it) ) );
    ++i;
  }
  return map;
}


void print_map_commands(std::map < unsigned int, std::string> map)
{
  // print map:
  std::map < unsigned int, std::string > ::iterator it2 = map.begin();
  int j = 0;
  for (it2 = map.begin(); it2 != map.end(); ++it2)
  {
    std::cout << j << ". ";
    std::cout << it2->first << " => " << it2->second << '\n';
    ++j;
  }
}


void print_map_registers(std::map < unsigned int, unsigned int > map)
{
  // print map:
  std::map < unsigned int, unsigned int > ::iterator it2 = map.begin();
  int j = 0;
  for (it2 = map.begin(); it2 != map.end(); ++it2)
  {
    std::cout << j << ". ";
    std::cout << it2->first << " => " << it2->second << '\n';
    ++j;
  }
}

#endif