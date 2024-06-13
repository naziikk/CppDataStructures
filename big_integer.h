#ifndef UNTITLED22_BIG_INTEGER_H
#define UNTITLED22_BIG_INTEGER_H


#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iomanip>

class BigIntegerOverflow : public std::runtime_error {
  public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
  }
};

class BigIntegerDivisionByZero : public std::runtime_error {
  public:
  BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {
  }
};

class BigInteger {
  public:
  static const long long BASE = 1e9;
  static const long long SIZE = 10;
  BigInteger();
  BigInteger(long long num);
  BigInteger(const char* c_str);
  bool operator==(const BigInteger& other) const;
//  bool operator!=(const BigInteger& other) const;
//  bool operator<(const BigInteger& other) const;
//  bool operator<=(const BigInteger& other) const;
//  bool operator>(const BigInteger& other) const;
//  bool operator>=(const BigInteger& other) const;
//  BigInteger operator+(const BigInteger& other) const;
//  BigInteger operator-(const BigInteger& other) const;
//  BigInteger operator*(const BigInteger& other) const;
//  BigInteger operator/(const BigInteger& other) const;
//  BigInteger operator%(const BigInteger& other) const;
//  BigInteger& operator+=(const BigInteger& other);
//  BigInteger& operator-=(const BigInteger& other);
//  BigInteger& operator*=(const BigInteger& other);
//  BigInteger& operator/=(const BigInteger& other);
//  BigInteger& operator%=(const BigInteger& other);
//  BigInteger operator+() const;
//  BigInteger operator-() const;
//  BigInteger& operator++();
//  BigInteger operator++(int);
//  BigInteger& operator--();
//  BigInteger operator--(int);
//  explicit operator bool() const;
  friend std::ostream& operator<<(std::ostream& os, const BigInteger& bigint);
//  friend std::istream& operator>>(std::istream& is, BigInteger& bigint);
  [[nodiscard]] bool IsNegative() const;
 private:
  std::vector<long long> digits_;
  bool negative_;
//  void FromInt(int num);
//  void FromString(const std::string& str); // Преобразование из строки
};



#endif//UNTITLED22_BIG_INTEGER_H
