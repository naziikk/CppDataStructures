#include "rational.h"

Rational::Rational() {
  num_ = 0;
  den_ = 1;
}
Rational::Rational(int x, int y) {
  num_ = x;
  den_ = y;
  if (den_ == 0) {
    throw RationalDivisionByZero();
  }
  ToPrime();
}
Rational::Rational(int x) {
  num_ = x;
  den_ = 1;
}
int Rational::GetNumerator() const {
  return num_;
}
int Rational::GetDenominator() const {
  return den_;
}
void Rational::SetNumerator(int x) {
  num_ = x;
  ToPrime();
}
void Rational::SetDenominator(int x) {
  if (x == 0) {
    throw RationalDivisionByZero();
  }
  den_ = x;
  ToPrime();
}
void Rational::ToPrime() {
  if (den_ == 0) {
    throw RationalDivisionByZero();
  }
  if (den_ < 0) {
    num_ = -num_;
    den_ = -den_;
  }
  int cur = std::gcd(num_, den_);
  num_ /= cur;
  den_ /= cur;
}
Rational Rational::operator+(const Rational& val) const {
  return {num_ * val.den_ + val.num_ * den_, den_ * val.den_};
}
Rational Rational::operator-(const Rational& val) const {
  return {num_ * val.den_ - val.num_ * den_, den_ * val.den_};
}
Rational Rational::operator*(const Rational& val) const {
  return {num_ * val.num_, den_ * val.den_};
}
Rational Rational::operator/(const Rational& val) const {
  return {num_ * val.den_, den_ * val.num_};
}
Rational& Rational::operator+=(const Rational& val) {
  num_ = num_ * val.den_ + val.num_ * den_;
  den_ = den_ * val.den_;
  ToPrime();
  return *this;
}
Rational& Rational::operator-=(const Rational& val) {
  num_ = num_ * val.den_ - val.num_ * den_;
  den_ = den_ * val.den_;
  ToPrime();
  return *this;
}
Rational& Rational::operator*=(const Rational& val) {
  num_ *= val.num_;
  den_ *= val.den_;
  ToPrime();
  return *this;
}
Rational& Rational::operator/=(const Rational& val) {
  num_ *= val.den_;
  den_ *= val.num_;
  ToPrime();
  return *this;
}
Rational Rational::operator-() const {
  return {-num_, den_};
}
Rational Rational::operator+() const {
  return *this;
}
Rational& Rational::operator++() {
  *this += 1;
  return *this;
}
Rational Rational::operator++(int) {
  Rational temp = *this;
  ++(*this);
  return temp;
}
Rational& Rational::operator--() {
  *this -= 1;
  return *this;
}
Rational Rational::operator--(int) {
  Rational temp = *this;
  --(*this);
  return temp;
}
bool Rational::operator==(const Rational& val) const {
  return num_ == val.num_ && den_ == val.den_;
}
bool Rational::operator!=(const Rational& val) const {
  return !(*this == val);
}
bool Rational::operator<(const Rational& val) const {
  return num_ * val.den_ < val.num_ * den_;
}
bool Rational::operator>(const Rational& val) const {
  return val < *this;
}
bool Rational::operator<=(const Rational& val) const {
  return !(val < *this);
}
bool Rational::operator>=(const Rational& val) const {
  return !(*this < val);
}
bool Rational::operator>(int val) const {
  return num_ > val * den_;
}
bool operator>(int val, const Rational& n) {
  return val * n.den_ > n.num_;
}
std::ostream& operator<<(std::ostream& os, const Rational& n) {
  if (n.num_ == 0) {
    os << 0;
  } else {
    os << n.num_;
    if (n.den_ != 1) {
      os << "/" << n.den_;
    }
  }
  return os;
}
std::istream& operator>>(std::istream& is, Rational& n) {
  char ch = 0;
  is >> n.num_;
  if (is.peek() == '/') {
    is >> ch >> n.den_;
  } else {
    n.den_ = 1;
  }
  n.ToPrime();
  return is;
}