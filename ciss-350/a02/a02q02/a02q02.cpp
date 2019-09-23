// File: a02q02.cpp
// Name: Christian Elliott

#include <iostream>


int f(int n, int a=3, int b=1, int d=2)
{
  if (n % d == 0) // if n is divisible by d
	{
	  n = n / d;
	}

  else // if n is not divisible by d
	{
	  n = (a * n) + b;
	}

  return n;
}


int fs(int * & p, int n, int a=3, int b=1, int d=2)
{
  
}


int main()
{
  int a, b, d, n, N;
  std::cin >> a >> b >> d >> n >> N;
  
  // run while loop here that runs f and puts return value into arr[]
  
  return 0;
}
