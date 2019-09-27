// File: a02q05.cpp
// Name: Christian Elliott


// Fraction class
// Main.cpp tests fraction
// Fraction.h has header file infomation
// Fraction.cpp has implementation of Fraction.h

// Todo:
// Skeleton code of fraction class
// first, simplify and reduce the fraction
// copy contructor, assignment operator
// 

#include <iostream>
#include "Fraction.h"


int main()
{
  int n, d;
  std::cin >> n >> d;
  // Fraction f(n,d);
  Fraction f(n, d);
  Fraction g(5, 2);
  f = g;
  std::cout << f;

  return 0;
}
