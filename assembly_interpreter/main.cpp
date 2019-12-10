// Author: Christian Elliott
// Date: 12.2019
// CISS-360 final

#include <iostream>
#include <string>
#include <vector>
#include "Interpreter.h"


std::string get_input(std::string &S)
{
  std::cin >> S;
  return S;
}


std::string get_input()
{
  std::string output;
  std::cin >> output;
  return output;
}


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


std::string ascii_to_uint(const std::vector< unsigned int > & x)
{
  std::string ret;
  for (int i = 0; i < x.size(); ++i)
    {
      ret.push_back(char(x[i]));
    }
  return ret;
}


int main()
{
  while(1)
    {
      std::cout << "Give me a string: ";
      std::string input = get_input();
      std::vector< unsigned int> uints = str_to_uint(input);

      std::cout << input << '\n';

      for (int i = 0; i < uints.size(); ++i)
	{
	  std::cout << uints[i] << ' ';
	}
      std::cout << '\n';

      std::string str;
      str = ascii_to_uint(uints);
      std::cout << str << '\n';
      //std::cout << "Original Input: " << input << '\n';
      //std::cout << "Converted input: " << uints << '\n';
    }
}
