#include "../big_integer.h"
BigInteger::BigInteger() {
  for (int i = 0; i < SIZE; i++) {
    digits_[i] = 0;
  }
}
BigInteger::BigInteger(long long num) {
  for (int i = 0; i < SIZE; i++) {
    digits_[i] = 0;
  }
  int next = 0;
  while (num) {
    digits_[next++] = num % BASE;
    num /= BASE;
  }
}
BigInteger::BigInteger(const char* c_str) {
  std::string str(c_str);
  negative_ = (str[0] == '-');
  size_t start = (str[0] == '-') ? 1 : 0;
  size_t len = str.size();
  for (size_t i = len; i > start; i -= SIZE) {
    int digit = 0;
    size_t pow = 1;
    for (size_t j = 0; j < SIZE && i - j > start; ++j) {
      digit += (str[i - j - 1] - '0') * pow;
      pow *= 10;
    }
    digits_.push_back(digit);
  }
}
//bool operator==(const BigInteger& other) const;
//bool operator!=(const BigInteger& other) const;
//bool operator<(const BigInteger& other) const;
//bool operator<=(const BigInteger& other) const;
//bool operator>(const BigInteger& other) const;
//bool operator>=(const BigInteger& other) const;
//BigInteger operator+(const BigInteger& other) const;
//BigInteger operator-(const BigInteger& other) const;
//BigInteger operator*(const BigInteger& other) const;
//BigInteger operator/(const BigInteger& other) const;
//BigInteger operator%(const BigInteger& other) const;
//BigInteger& operator+=(const BigInteger& other);
//BigInteger& operator-=(const BigInteger& other);
//BigInteger& operator*=(const BigInteger& other);
//BigInteger& operator/=(const BigInteger& other);
//BigInteger& operator%=(const BigInteger& other);
//BigInteger operator+() const;
//BigInteger operator-() const;
//BigInteger& operator++();
//BigInteger operator++(int);
//BigInteger& operator--();
//BigInteger operator--(int);
//explicit operator bool() const;
std::ostream& operator<<(std::ostream& out, const BigInteger& num) {
  if (num.digits_.empty()) {
    out << "0";
  } else {
    // Выводим первую цифру без ведущих нулей
    out << num.digits_.back();

    // Выводим остальные цифры с ведущими нулями
    for (int i = num.digits_.size() - 2; i >= 0; --i) {
      out << std::setw(BigInteger::SIZE) << std::setfill('0') << num.digits_[i];
    }
  }
  return out;
}
//friend std::istream& operator>>(std::istream& is, BigInteger& bigint);
bool BigInteger::IsNegative() const {
  return digits_[0] < 0;
}