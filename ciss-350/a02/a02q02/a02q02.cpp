// File: a02q02.cpp
// Name: Christian Elliott

#include <iostream>


bool f(int a, int b, int d, int n, int N)
{
  int i = 0;
  while (i <= N)
	{
	  if (n % d == 0) // if n is divisible by d
		{
		  n = n / d;
		}
	  else
		  n = a * n + b;
	  
	  ++i;
	}
  if (n != 1)
	{
	  return false;
	}
  else
	return true;
}


int main()
{
  int a, b, d, n, N;
  std::cin >> a >> b >> d >> n >> N;

  std::cout << a << ' ' << b << ' ' << d << ' ' << n << ' ' << N << ' ';
  if(f(a, b, d, n, N))
	{
	  std::cout << 
	}
  
  
  return 0;
}
