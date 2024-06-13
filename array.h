#ifndef UNTITLED22_ARRAY_H
#define UNTITLED22_ARRAY_H
#define ARRAY_TRAITS_IMPLEMENTED

#include <stdexcept>
#include <type_traits>
#include <iostream>

class ArrayOutOfRange : public std::out_of_range {
  public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};
template <class T, size_t N>
class Array {
 public:
  T arr_[N];
  T& operator[](size_t idx) {
    return arr_[idx];
  }
  const T& operator[](size_t idx) const {
    return arr_[idx];
  }
  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }
    return arr_[idx];
  }
  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }
    return arr_[idx];
  }
  T& Front() {
    return arr_[0];
  }
  const T& Front() const {
    return arr_[0];
  }
  T& Back() {
    return arr_[N - 1];
  }
  const T& Back() const {
    return arr_[N - 1];
  }
  const T* Data() const {
    return arr_;
  }
  T* Data() {
    return arr_;
  }
  size_t Size() const {
    return N;
  }
  bool Empty() const {
    return N == 0;
  }
  void Fill(const T& value) {
    for (size_t i = 0; i < N; i++) {
      arr_[i] = value;
    }
  }
  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      T temp = arr_[i];
      arr_[i] = other.arr_[i];
      other.arr_[i] = temp;
    }
  }
};
template <class T>
constexpr size_t GetSize(T&) {
  return 0;
}
template <class T>
constexpr size_t GetSize(T&&) {
  return 0;
}
template <class T, size_t N>
constexpr size_t GetSize(T(&)[N]) {
  return N;
}
template <typename T>
constexpr size_t GetRank(T&&) {
  return 0;
}
template <typename T>
constexpr size_t GetRank(T&) {
  return 0;
}
template <typename T, std::size_t N>
constexpr size_t GetRank(T(&arr)[N]) {
  return 1 + GetRank(arr[0]);
}
template <typename T>
constexpr size_t GetNumElements(T&) {
  return 1;
}
template <typename T>
constexpr size_t GetNumElements(T&&) {
  return 1;
}
template <typename T, size_t N>
constexpr size_t GetNumElements(T(&arr)[N]) {
  return N * GetNumElements(arr[0]);
}
template <>
constexpr size_t GetNumElements<int>(int&) {
  return 1;
}
#endif  // UNTITLED22_ARRAY_H
