// Fraction.cpp

#include <iostream>
#include "Fraction.h"


Fraction::Fraction(int n, int d)
{
  // first, find GCD
  int gcd = 1;
  if (n >= 0)
    {
      for (int i = n; i > 0; --i)
	{
	  if (d % i == 0 && n % i == 0)
	    {
	      gcd = i;
	      break;
	    }
	}
    }
  else
    {
      for (int i = n * -1; i > 0; --i)
	{
	  if (d % i == 0 && n % i == 0)
	    {
	      gcd = i;
	      break;
	    }
	}
    }

  // here GCD either is 1 or passed above if statement
  n /= gcd;
  d /= gcd;

  // things to check for:
  // x/1 , -x/1, -x/-1, -x/y, -x/-y, -x/x, x/x, 0/x, x/0

  if (d < 0 && n < 0) // if numerator AND denominator are negative
    {
      d = d * -1;
      n = n * -1;
    }
  n_ = n;
  d_ = d;  
}


Fraction::Fraction(int n)
{
  n_ = n;
  d_ = 1;
}


Fraction::Fraction()
{
  n_ = 0;
  d_ = 1;
}

std::ostream & operator<<(std::ostream & cout, const Fraction & f)
{
  int n = f.get_n();
  int d = f.get_d();

  if (d == 1) // if it's n/1 --> print n;
    {
      cout << n << ' ';
      return cout;
    }

  if (d == -1)
    {
      cout << n * -1 << ' ';
      return cout;
    }

  else if (n == d && d!= 0) // if it's N/N --> print 1;
    {
      cout << 1 << ' ';
      return cout;
    }

  else if (n == 0 && d != 0) // if it's 0/d --> print 0;
    {
      cout << 0 << ' ';
      return cout;
    }

  else if (d == 0) // if undefined
    {
      cout << "UNDEFINED" << ' ';
      return cout;
    }

  else if (n < 0 && d > 1) // if top is neg
    {
      cout << '-' << n * -1 << '/' << d << ' ';
      return cout;
    }

  else if (n >= 1 && d < 0) // if bottom is neg
    {
      cout << '-' << n << '/' << d * -1 << ' ';
      return cout;
    }

  else
    {
      cout << n << '/' << d << ' ';
    }
  return cout;
}


Fraction & Fraction::operator=(const Fraction & f)
{
  this->n_ = f.n_;
  this->d_ = f.d_;

  return (*this);
}


Fraction & Fraction::operator+(const Fraction & g)
{
  this->n_ = (n_ * g.d_) + (g.n_ * d_);
  this->d_ = (d_ * g.d_);

  reduce(*this);
  return (*this);
}


Fraction & Fraction::operator-(const Fraction & g)
{
  n_ = (n_ * g.d_) - (g.n_ * d_);
  d_ = (d_ * g.d_);

  reduce(*this);
  return (*this);
}


Fraction & Fraction::operator*(const Fraction & f)
{
  n_ = n_ * f.n_;
  d_ = d_ * f.d_;

  reduce(*this);
  return (*this);
}


Fraction & Fraction::operator/(const Fraction & f)
{
  this->n_ = n_ * f.d_;
  this->d_ = d_ * f.n_;
  reduce(*this);
  return (*this);
}


void Fraction::reduce(Fraction & f)
{
  int n = n_;
  int d = d_;
  int gcd = 1;
  if (n >= 0)
    {
      for (int i = n; i > 0; --i)
	{
	  if (d % i == 0 && n % i == 0)
	    {
	      gcd = i;
	      break;
	    }
	}
    }
  else
    {
      for (int i = n * -1; i > 0; --i)
	{
	  if (d % i == 0 && n % i == 0)
	    {
	      gcd = i;
	      break;
	    }
	}
    }

  // here GCD either is 1 or passed above if statement
  n /= gcd;
  d /= gcd;

  // things to check for:
  // x/1 , -x/1, -x/-1, -x/y, -x/-y, -x/x, x/x, 0/x, x/0

  if (d < 0 && n < 0) // if numerator AND denominator are negative
    {
      d = d * -1;
      n = n * -1;
    }
  n_ = n;
  d_ = d;
}
