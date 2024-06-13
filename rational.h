#ifndef UNTITLED22_RATIONAL_H
#define UNTITLED22_RATIONAL_H

#include <iostream>
#include <stdexcept>
#include <numeric>

class RationalDivisionByZero : public std::runtime_error {
  public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};
class Rational {
  private:
  int num_;
  int den_;
  void ToPrime();
  public:
  Rational();
  Rational(int x); // NOLINT
  Rational(int x, int y);
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int x);
  void SetDenominator(int x);
  Rational operator-() const;
  Rational operator+() const;
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
  Rational operator+(const Rational& val) const;
  Rational operator-(const Rational& val) const;
  Rational operator*(const Rational& val) const;
  Rational operator/(const Rational& val) const;
  Rational& operator+=(const Rational& val);
  Rational& operator-=(const Rational& val);
  Rational& operator*=(const Rational& val);
  Rational& operator/=(const Rational& val);
  bool operator==(const Rational& val) const;
  bool operator!=(const Rational& val) const;
  bool operator<(const Rational& val) const;
  bool operator>(const Rational& val) const;
  bool operator<=(const Rational& val) const;
  bool operator>=(const Rational& val) const;
  bool operator>(int val) const;
  friend bool operator>(int val, const Rational& n);
  friend std::ostream& operator<<(std::ostream& os, const Rational& n);
  friend std::istream& operator>>(std::istream& is, Rational& n);
};

#endif  //UNTITLED22_RATIONAL_H
