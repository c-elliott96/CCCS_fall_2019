#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <functional>
#include <iomanip>
#include "Pseudo.h"



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


void create_data(std::vector < unsigned int > & data)
{
  for (int i = 0; i < 1; ++i)
  {
    data.push_back(0);
  }
}


void init_help_commands(std::vector < std::string > & help_commands)
{
  std::string str;
  str = "\\help";
  help_commands.push_back(str);

  str = "\\data";
  help_commands.push_back(str);

  str = "\\registers";
  help_commands.push_back(str);

  str = ".data";
  help_commands.push_back(str);

  str = ".text";
  help_commands.push_back(str);
}


void print_data(const std::vector < unsigned int > & data)
{
  std::cout << "================================================================\n"
            << "DATA SEGMENT\n"
            << "================================================================\n"
            << "  addr (int)| addr (hex)| value (int)| value (hex)| value (char)\n"
            << "------------+-----------+------------+------------+-------------\n";
  if (data.empty())
  {
    std::cout << "Nothing in Data ... " << '\n';
    return;
  }
  else 
  {
    for (int i = 0; i < data.size(); ++i)
    {
      unsigned int addr = 100000 + (i * 4);
      std::cout << std::setw(12);
      std::cout << addr << '|';
      std::cout << std::setbase(16);
      std::cout << addr << '|';
      std::cout << std::setbase(10);
      std::cout << data[i] << '|';
      std::cout << std::setbase(16);
      std::cout << data[i] << '|';
      std::cout << std::setbase(10);
      std::cout << char(data[i]) << std::endl;
    } 
  }
}

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


bool help_command_exists(const std::string & command, 
const std::vector < std::string > & help)
{
  std::cout << "command syntax: " << command << '\n';
  for (int i = 0; i < help.size(); ++i)
  {
    std::cout << "help_commands[i] = " << help[i];
    if (command == help[i])
    {
      std::cout << "they match\n";
      return true;
    }
  }
  return false;
}


// finds first substring ... not sure if needed 
void tokenize_do(const std::vector < unsigned int > & x, 
std::map < unsigned int , std::string > map,
std::vector < unsigned int > & registers,
const std::vector < std::string > & help_commands)
{
  // parse string for command 
  bool is_command = false;
  bool is_dot = false;
  std::vector < unsigned int > cmd_uints;
  for (int i = 0; i < x.size(); ++i)
  {
    if (x[i] == 46)
    {
      is_dot = true;
    }

    if (x[i] != 32)
    {
      cmd_uints.push_back(x[i]);
    }

    if (x[i] == 32 && !is_dot)
    {
      is_command = true;
      break;
    } 
  }

  std::string reg_0;
  std::string reg_1;
  std::string reg_2;
  std::string const_immed;

  bool help_cmd_exists = help_command_exists(x, help_commands);
  std::cout << help_cmd_exists << '\n';
  if (help_cmd_exists)
  {
    //command_exists = true;
    std::cout << "Help command entered\n";
  }

  if (is_command)
  {
    bool reg_check = false;

    bool reg_0_done = false;
    bool reg_1_done = false;
    bool reg_2_done = false;
    bool comma = false;
    bool space = false;
    bool immediate = false;

    for (int i = 0; i < x.size(); ++i)
    {
      if (x[i] == 36) // if we hit a '$'
      {
        reg_check = true;
        //continue;
      } 

      if (x[i] == 44 && !comma)
      {
        comma = true;
      }

      if (x[i] == 36)
      {
        comma = false;
        space = false;
      }

      if (x[i] == 32 && comma)
      {
        space = true;
      }

      if (comma && space && x[i] != 32 && x[i] > 47 && x[i] < 58)
      {
        immediate = true;
        const_immed.push_back(char(x[i]));
      }

      if (reg_check && !reg_0_done && x[i] != 44 && x[i] != 32)
      {
        reg_0.push_back(char(x[i]));
      }

      if (reg_check && !reg_1_done && reg_0_done && x[i] != 44 && x[i] != 32)
      {
        reg_1.push_back(char(x[i]));
      }

      if (reg_check && !reg_2_done && reg_0_done && reg_1_done
      && x[i] != 44 && x[i] != 32)
      {
        reg_2.push_back(char(x[i]));
      }

      if (reg_check && x[i] == 44)
      {
        reg_check = false;
        if (!reg_0.empty())
        {
          reg_0_done = true;
        }

        if (reg_0_done && !reg_1.empty())
        {
          reg_1_done = true;
        }

        if (reg_0_done && reg_1_done && !reg_2.empty())
        {
          reg_2_done = true;
        }        
      }
    }
  }
  for (int i = 0; i < cmd_uints.size(); ++i)
  {
    std::cout << cmd_uints[i] << ' ';
  }
  std::cout << '\n';
  std::string cmd_string = ascii_to_uint(cmd_uints);
  std::cout << "command : ";
  std::cout << cmd_string << '\n';

  if (!reg_0.empty())
  {
    std::cout << "reg_0 = ";
    std::cout << reg_0 << std::endl;
  }

  if (!reg_1.empty())
  {
    std::cout << "reg_1 = ";
    std::cout << reg_1 << std::endl;
  }

  if (!reg_2.empty())
  {
    std::cout << "reg_2 = ";
    std::cout << reg_2 << std::endl;
  }

  if (!const_immed.empty())
  {
    std::cout << "const = ";
    std::cout << const_immed << std::endl;
  }

  unsigned int a = alt_hash(cmd_string);

  switch (a)
    {
      case 106: // j 
      {
        //
      }
      break;
      case 304: // lb
      {
        //
      }
      break;
      case 311: // sb
      {
        //
      }
      break;
      case 318: // li
      {
        pseudo_li(registers, reg_0, const_immed);
      }
      break;
      case 334: // jr
      {
        
      }
      break;
      case 339: // or 
      {
        
      }
      break;
      case 346: // lw
      {
        
      }
      break;
      case 353: // sw
      {
        
      }
      break;
      case 597: // add
      {
        pseudo_add(registers, reg_0, reg_1, reg_2);
      }
      break;
      case 617: // and
      {
        
      }
      break;
      case 621: // bne
      {
        
      }
      break;
      case 624: // jal
      {
        
      }
      break;
      case 634: // sra
      {
        
      }
      break;
      case 639: // beq
      {
        
      }
      break;
      case 643: // sub
      {
        pseudo_sub(registers, reg_0, reg_1, reg_2);
      }
      break;
      case 654: // ori
      {
        
      }
      break;
      case 655: // sll
      {
        
      }
      break;
      case 657: // lui
      {
        
      }
      break;
      case 664: // div
      {
        
      }
      break;
      case 667: // srl
      {
        
      }
      break;
      case 679: // slt
      {
        
      }
      break;
      case 684: // xor 
      {
        
      }
      break;
      case 1017: // addi
      {
        
      }
      break;
      case 1037: // andi
      {
        
      }
      break;
      case 1045: // mfhi
      {
        
      }
      break;
      case 1065: // addu
      {
        
      }
      break;
      case 1081: // mflo
      {
        
      }
      break;
      case 1095: // bgez
      {
        
      }
      break;
      case 1099: // slti
      {
        
      }
      break;
      case 1104: // xori
      {
        
      }
      break;
      case 1105: // blez
      {
        
      }
      break;
      case 1111: // subu
      {
        
      }
      break;
      case 1113: // noop
      {
        
      }
      break;
      case 1127: // sllv
      {
        
      }
      break;
      case 1131: // mult
      {
        
      }
      break;
      case 1132: // divu 
      {
        
      }
      break;
      case 1139: // srlv
      {
        
      }
      break;
      case 1140: // bgtz
      {
        
      }
      break;
      case 1147: // sltu
      {
        
      }
      break;
      case 1150: // bltz
      {
        
      }
      break;
      case 1602: // addiu
      {
        
      }
      break;
      case 1684: // sltiu
      {
        
      }
      break;
      case 1716: // multu
      {
        
      }
      break;
      case 2228: // bgezal
      {
        
      }
      break;
      case 2283: // bltzal
      {
        
      }
      break;
      case 2987: // syscall
      {
        
      }
      break;
      default: 
      {
        std::cout << "invalid command syntax\n";
      }
      break;
    } 
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


// obsolete 
void create_registers(std::map < unsigned int, unsigned int > & map)
{
  for (unsigned int i = 0; i < 35; ++i)
    {
        map.insert(std::pair< unsigned int , unsigned int > (i , 0));
    }
}


void create_registers_1(std::vector < unsigned int > & regs)
{
  for (int i = 0; i < 35; ++i)
    {
      regs.push_back(0);
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





void do_action(std::string & command, std::map < unsigned int, std::string > map, 
               std::map < unsigned int, unsigned int > reg_map,
               const std::vector < std::string > & help_commands)
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
    }
    else
    ++it;
  }

  bool help_cmd_exists = help_command_exists(command, help_commands);
  std::cout << help_cmd_exists << '\n';
  if (help_cmd_exists)
  {
    command_exists = true;
    std::cout << "Help command entered\n";
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
    a = "li";
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


// obsolete
void print_map_registers(std::map < unsigned int, unsigned int > map)
{
  // print map:
  // std::map < unsigned int, unsigned int > ::iterator it2 = map.begin();
  // int j = 0;
  // for (it2 = map.begin(); it2 != map.end(); ++it2)
  // {
  //   std::cout << "R" << j;
  //   if (j < 10) std::cout << ' ';

  //   std::cout << std::setw(5) << "=>" 
  //   << std::right << std::setw(10) << it2->second << '\n';
  //   ++j;
  // }
  for (int i = 0; i < map.size(); ++i)
  {
    std::cout << "R" << i;
    std::cout << std::setw(10) << map[i] << '\n';
  }
}


void print_map_registers_1(const std::vector < unsigned int > & regs)
{
  // for (int i = 0; i < regs.size(); ++i)
  // {
  //   if (i < 10)
  //   {
  //     std::cout << 'R' << i << ' ';
  //     std::cout << std::setw(10) << regs[i] << '\n';
  //   }

  //   else 
  //   {
  //     std::cout << 'R' << i;
  //     std::cout << std::setw(10) << regs[i] << '\n';
  //   }
  // }
  std::cout << "================================================================\n"
            << "REGISTERS\n"
            << "================================================================\n";
  std::cout << "R0" << std::setw(11) << "[r0] = " << regs[0] << '\n'
            << "R1" << std::setw(11) << "[at] = " << regs[1] << '\n'
            << "R2" << std::setw(11) << "[v0] = " << regs[2] << '\n'
            << "R3" << std::setw(11) << "[v1] = " << regs[3] << '\n'
            << "R4" << std::setw(11) << "[a0] = " << regs[4] << '\n'
            << "R5" << std::setw(11) << "[a1] = " << regs[5] << '\n'
            << "R6" << std::setw(11) << "[a2] = " << regs[6] << '\n'
            << "R7" << std::setw(11) << "[a3] = " << regs[7] << '\n'
            << "R8" << std::setw(11) << "[t0] = " << regs[8] << '\n'
            << "R9" << std::setw(11) << "[t1] = " << regs[9] << '\n'
            << "R10" << std::setw(10) << "[t2] = " << regs[10] << '\n'
            << "R11" << std::setw(10) << "[t3] = " << regs[11] << '\n'
            << "R12" << std::setw(10) << "[t4] = " << regs[12] << '\n'
            << "R13" << std::setw(10) << "[t5] = " << regs[13] << '\n'
            << "R14" << std::setw(10) << "[t6] = " << regs[14] << '\n'
            << "R15" << std::setw(10) << "[t7] = " << regs[15] << '\n'
            << "R16" << std::setw(10) << "[s0] = " << regs[16] << '\n'
            << "R17" << std::setw(10) << "[s1] = " << regs[17] << '\n'
            << "R18" << std::setw(10) << "[s2] = " << regs[18] << '\n'
            << "R19" << std::setw(10) << "[s3] = " << regs[19] << '\n'
            << "R20" << std::setw(10) << "[s4] = " << regs[20] << '\n'
            << "R21" << std::setw(10) << "[s5] = " << regs[21] << '\n'
            << "R22" << std::setw(10) << "[s6] = " << regs[22] << '\n'
            << "R23" << std::setw(10) << "[s7] = " << regs[23] << '\n'
            << "R24" << std::setw(10) << "[t8] = " << regs[24] << '\n'
            << "R25" << std::setw(10) << "[t9] = " << regs[25] << '\n'
            << "R26" << std::setw(10) << "[k0] = " << regs[26] << '\n'
            << "R27" << std::setw(10) << "[k1] = " << regs[27] << '\n'
            << "R28" << std::setw(10) << "[gp] = " << regs[28] << '\n'
            << "R29" << std::setw(10) << "[sp] = " << regs[29] << '\n'
            << "R30" << std::setw(10) << "[s8] = " << regs[30] << '\n'
            << "R31" << std::setw(10) << "[ra] = " << regs[31] << '\n'
            << "R32" << std::setw(10) << "[pc] = " << regs[32] << '\n'
            << "R33" << std::setw(10) << "[hi] = " << regs[33] << '\n'
            << "R34" << std::setw(10) << "[lo] = " << regs[34] << '\n'
            << "================================================================\n";
}





#endif