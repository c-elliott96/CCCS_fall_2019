// Fraction.h

#ifndef FRACTION_H
#define FRACTION_H

class Fraction
{
 public:
  Fraction(int, int);    // default constructor --> two ints 
  Fraction(int);         // default constructor --> one int (x/1)
  Fraction();            // placeholder constructor???
  int get_n() const { return n_; }
  int get_d() const { return d_; }
  //std::ostream & operator<<(std::ostream &, const Fraction &);
  Fraction & operator=(const Fraction &);
  Fraction & operator+(const Fraction &);
  Fraction & operator-(const Fraction &);
  Fraction & operator*(const Fraction &);
  Fraction & operator/(const Fraction &);
  void reduce(Fraction &);

 private:
  int n_, d_;
};

//Fraction operator+(const Fraction &, const Fraction &);
std::ostream & operator<<(std::ostream &, const Fraction &);
// find out why I'm having a hard time overloading this if I put protoype
// in Public class def.

#endif
