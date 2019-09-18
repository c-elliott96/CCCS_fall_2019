// Name: Christian Elliott
// File: a02q01.cpp

#include <iostream>


int main()
{
  int n;
  int counter = 0;
  std::cin >> n;
  while (n != 1)
	{
	  std::cout << n << ' ';
	  if (n % 2 != 0) // if n is odd
		{
		  n = (3 * n) + 1;
		}

	  else  // if n is even 
		{
		  n = n / 2;
		}
	  ++counter;
	}

  std::cout << n << ' ' << counter << std::endl;
  
  return 0;
}
