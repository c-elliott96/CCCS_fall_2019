// Fraction.h

#ifndef FRACTION_H
#define FRACTION_H

class Fraction
{
 public:
  Fraction(int, int);
  Fraction(int);
  Fraction();
  int get_n() const { return n_; }
  int get_d() const { return d_; }
  //std::ostream & operator<<(std::ostream &, const Fraction &);
  Fraction & operator=(const Fraction &);
  Fraction & operator+(const Fraction &, const Fraction &);

 private:
  int n_, d_;
};

//Fraction operator+(const Fraction &, const Fraction &);
std::ostream & operator<<(std::ostream &, const Fraction &);
// find out why I'm having a hard time overloading this if I put protoype
// in Public class def.

#endif
