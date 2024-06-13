#ifndef UNTITLED22_UNIQUE_PTR_H
#define UNTITLED22_UNIQUE_PTR_H
#include <iostream>

template <typename T>
class UniquePtr {
  T* a_;
  public:
  UniquePtr() {
    a_ = nullptr;
  }
  explicit UniquePtr(T* ptr) {
    a_ = ptr;
  }
  UniquePtr(UniquePtr&& ptr) noexcept {
    a_ = ptr.a_;
    ptr.a_ = nullptr;
  }
  UniquePtr& operator=(UniquePtr&& ptr) noexcept {
    if (this != &ptr) {
      delete a_;
      a_ = ptr.a_;
      ptr.a_ = nullptr;
    }
    return *this;
  }
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  ~UniquePtr() {
    delete a_;
  }
  T* Get() const {
    return a_;
  }
  T& operator*() const {
    return *a_;
  }
  T* operator->() const {
    return a_;
  }
  explicit operator bool() const {
    return a_ != nullptr;
  }
  void Swap(UniquePtr& a) {
    std::swap(a_, a.a_);
  }
  void Reset(T* new_ptr = nullptr) {
    if (a_ != new_ptr) {
      delete a_;
      a_ = new_ptr;
    }
  }
  T* Release() {
    T* temp = a_;
    a_ = nullptr;
    return temp;
  }
};

#endif  //UNTITLED22_UNIQUE_PTR_H
