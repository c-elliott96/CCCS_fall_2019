// File: a02q02.cpp
// Name: Christian Elliott

#include <iostream>


int f(int n, int a, int b, int d)
{
  if (n % d == 0) // if n is divisible by d
	{
    return n / 2;
	}

  else // if n is not divisible by d
	{
    return (3 * n) + 1;
	}
}


int fs(int * &p, int n, int N, int a, int b, int d)
{
  int i = 0;
  for (; i <= N; ++i)
  {
    if (i == 0)
    {
      p[i] = n;
    }
    else
    {    
      n = f(n, a, b, d);
      p[i] = n;
      if (n == 1)
      {
        p[i] = n;
        return i;
      }
    }
  }
  return i + 1;
}


int main()
{
  int a, b, d, n, N;
  std::cin >> a >> b >> d >> n >> N;
  int * p = new int[N + 1];
  /*
  for (int i = 0; i < N; ++i)
  {
    p[i] = new int;
  } 
  */

  int i = fs(p, n, N, a, b, d);

  std::cout << a << ' ' << b << ' ' << d << ' ' << n << ' ' << N << ' ';
  if (p[i] == 1) 
  {
    std::cout << "pass ";
  }
  else 
  {
    std::cout << "fail ";
  }
  std::cout << i << ' ';
  for (int j = 0; j < i; ++j)
  {
    std::cout << p[j] << ' ';
  }
  std::cout << std::endl;
  delete [] p;
  
  return 0;
}
