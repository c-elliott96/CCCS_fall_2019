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
  Fraction f(1, 7);
  Fraction g(1, 8);
  Fraction h = g / f;
  std::cout << h << '\n';

  return 0;
}
