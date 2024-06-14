#ifndef UNTITLED22_VECTOR_H
#define UNTITLED22_VECTOR_H
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include <type_traits>
#include <memory>

template <class T>
class Vector {
  public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  Vector() : size_(0), capacity_(0), data_(nullptr) {}
  explicit Vector(SizeType size) : size_(size), capacity_(size), data_(size ? new T[size] : nullptr) {
    for (SizeType i = 0; i < size_; ++i) {
      data_[i] = T();
    }
  }
  Vector(SizeType size, ConstReference value) : size_(size), capacity_(size), data_(size ? new T[size] : nullptr) {
    try {
      for (SizeType i = 0; i < size_; ++i) {
        data_[i] = value;
      }
    } catch (...) {
      delete[] data_;
      throw;
    }
  }
  template <class ForwardIt, class = std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag,
                                                                       typename std::iterator_traits<ForwardIt>::iterator_category>>>
  Vector(ForwardIt first, ForwardIt last) : size_(std::distance(first, last)), capacity_(size_), data_(size_ ? new T[size_] : nullptr) {
    SizeType i = 0;
    try {
      for (auto it = first; it != last; ++it) {
        data_[i++] = *it;
      }
    } catch (...) {
      Clear();
      throw;
    }
  }
  Vector(std::initializer_list<T> list) : Vector(list.begin(), list.end()) {
  }
  ~Vector() noexcept {
    Clear();
  }
  Vector(const Vector& arr) : size_(arr.size_), capacity_(arr.capacity_), data_(size_ ? new T[arr.capacity_] : nullptr) {
    for (SizeType i = 0; i < size_; ++i) {
      try {
        data_[i] = arr.data_[i];
      } catch (...) {
        delete[] data_;
        throw;
      }
    }
  }
  Vector(Vector&& arr) noexcept : size_(arr.size_), capacity_(arr.capacity_), data_(arr.data_) {
    arr.size_ = 0;
    arr.capacity_ = 0;
    arr.data_ = nullptr;
  }
  Vector& operator=(const Vector& arr) {
    if (this != &arr) {
      Vector temp(arr);
      Swap(temp);
    }
    return *this;
  }
  Vector& operator=(Vector&& arr) noexcept {
    if (this != &arr) {
      delete[] data_;
      size_ = arr.size_;
      capacity_ = arr.capacity_;
      data_ = arr.data_;
      arr.size_ = 0;
      arr.capacity_ = 0;
      arr.data_ = nullptr;
    }
    return *this;
  }
  Reference operator[](SizeType idx) {
    return data_[idx];
  }
  ConstReference operator[](SizeType idx) const {
    return data_[idx];
  }
  Reference At(SizeType idx) {
    if (idx >= size_) {
      throw std::out_of_range("");
    }
    return data_[idx];
  }
  ConstReference At(SizeType idx) const {
    if (idx >= size_) {
      throw std::out_of_range("");
    }
    return data_[idx];
  }
  Reference Front() {
    return data_[0];
  }
  ConstReference Front() const {
    return data_[0];
  }
  Reference Back() {
    if (size_ == 0) {
      throw std::out_of_range("");
    }
    return data_[size_ - 1];
  }
  ConstReference Back() const {
    return data_[size_ - 1];
  }
  Pointer Data() {
    return data_;
  }
  ConstPointer Data() const {
    return data_;
  }
  [[nodiscard]] SizeType Size() const {
    return size_;
  }
  [[nodiscard]] SizeType Capacity() const {
    return capacity_;
  }
  [[nodiscard]] bool Empty() const {
    return size_ == 0;
  }
  void Swap(Vector& arr) noexcept {
    std::swap(size_, arr.size_);
    std::swap(capacity_, arr.capacity_);
    std::swap(data_, arr.data_);
  }
  void Resize(SizeType new_size) {
    if (new_size <= capacity_) {
      for (SizeType i = size_; i < new_size; ++i) {
        data_[i] = T();
      }
      size_ = new_size;
      return;
    }
    auto new_data = new T[new_size];
    for (SizeType i = 0; i < size_; ++i) {
      new_data[i] = std::move(data_[i]);
    }
    for (SizeType i = size_; i < new_size; ++i) {
      new_data[i] = T();
    }
    delete[] data_;
    data_ = new_data;
    size_ = new_size;
    capacity_ = new_size;
  }
  void Resize(SizeType new_size, const ValueType& value) {
    if (new_size <= capacity_) {
      for (SizeType i = size_; i < new_size; ++i) {
        data_[i] = value;
      }
      size_ = new_size;
      return;
    }
    auto new_data = new T[new_size];
    for (SizeType i = 0; i < size_; ++i) {
      new_data[i] = std::move(data_[i]);
    }
    for (SizeType i = size_; i < new_size; ++i) {
      new_data[i] = value;
    }
    delete[] data_;
    data_ = new_data;
    size_ = new_size;
    capacity_ = new_size;
  }
  void ShrinkToFit() {
    if (capacity_ > size_) {
      Pointer new_data = size_ ? new T[size_] : nullptr;
      for (SizeType i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
    }
  }
  void Clear() noexcept {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
  void Reserve(SizeType new_cap) {
    if (new_cap > capacity_) {
      T* temp = nullptr;
      temp = new T[new_cap];
      for (SizeType i = 0; i < size_; ++i) {
        temp[i] = std::move(data_[i]);
      }
      delete[] data_;
      data_ = temp;
      capacity_ = new_cap;
    }
  }
  void PushBack(const T& it) {
    if (size_ == capacity_) {
      SizeType old_size = size_;
      SizeType old_capacity = capacity_;
      auto old_data = data_;
      try {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_] = it;
        size_++;
      } catch (...) {
        size_ = old_size;
        capacity_ = old_capacity;
        data_ = old_data;
        throw;
      }
    }
    else {
      data_[size_] = it;
      size_++;
    }
  }
  void PushBack(T&& value) {
    if (size_ == capacity_) {
      SizeType old_size = size_;
      SizeType old_capacity = capacity_;
      auto old_data = data_;
      try {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_] = std::move(value);
        size_++;
      } catch (...) {
        size_ = old_size;
        capacity_ = old_capacity;
        data_ = old_data;
        throw;
      }
    } else {
      data_[size_] = std::move(value);
      size_++;
    }
  }
  void PopBack() {
    if (size_ > 0) {
      std::destroy_at(data_ + size_ - 1);
      --size_;
    }
  }
  bool operator==(const Vector& arr) const {
    if (size_ != arr.size_) {
      return false;
    }
    return std::equal(data_, data_ + size_, arr.data_);
  }
  bool operator!=(const Vector& arr) const {
    return !(*this == arr);
  }
  bool operator<(const Vector& arr) const {
    return std::lexicographical_compare(data_, data_ + size_, arr.data_, arr.data_ + arr.size_);
  }
  bool operator>(const Vector& arr) const {
    return arr < *this;
  }
  bool operator<=(const Vector& arr) const {
    return !(arr < *this);
  }
  bool operator>=(const Vector& arr) const {
    return !(*this < arr);
  }
  Iterator begin() noexcept {  // NOLINT
    return data_;
  }
  ConstIterator begin() const noexcept {  // NOLINT
    return data_;
  }
  ConstIterator cbegin() const noexcept {  // NOLINT
    return data_;
  }
  Iterator end() noexcept {  // NOLINT
    return data_ + size_;
  }
  ConstIterator end() const noexcept {  // NOLINT
    return data_ + size_;
  }
  ConstIterator cend() const noexcept {  // NOLINT
    return data_ + size_;
  }
  ReverseIterator rbegin() noexcept {  // NOLINT
    return ReverseIterator(end());
  }
  ConstReverseIterator rbegin() const noexcept {  // NOLINT
    return ConstReverseIterator(end());
  }
  ConstReverseIterator crbegin() const noexcept {  // NOLINT
    return ConstReverseIterator(end());
  }
  ReverseIterator rend() noexcept {  // NOLINT
    return ReverseIterator(begin());
  }
  ConstReverseIterator rend() const noexcept {  // NOLINT
    return ConstReverseIterator(begin());
  }
  ConstReverseIterator crend() const noexcept {  // NOLINT
    return ConstReverseIterator(begin());
  }
  private:
  SizeType size_;
  SizeType capacity_;
  Pointer data_;
};
#endif  // UNTITLED22_VECTOR_H
