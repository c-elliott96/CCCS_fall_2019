// Name: Christian Elliott
// File: a01q04.cpp

#include <iostream>


void increment(int digits[], int len_digits, int base)
{
  bool carry = false;
  for (int i = len_digits - 1; i >= 0; --i)
	{
	  if (!carry && digits[i] == base - 1)
		{
		  carry = true;
		  digits[i] = 0;
		  continue;
		}
	  else if (carry && digits[i] != base - 1)
		{
		  carry = false;
		  ++digits[i];
		  return;
		}
	  else if (carry && digits[i] == base - 1)
		{
		  digits[i] = 0;
		  continue;
		}
	  else
		{
		  ++digits[i];
		  return;
		}
	}
}


void print(int digits[], int len_digits)
{
  /*
  for (int i = len_digits - 1; i >= 1; --i)
	{
	  std::cout << digits[i] << ','; 
	}
  */

  for (int i = 0; i < len_digits - 1; ++i)
	{
	  std::cout << digits[i] << ',';
	}
  std::cout << digits[len_digits - 1] << std::endl;
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
