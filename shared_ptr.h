#ifndef UNTITLED22_SHARED_PTR_H
#define UNTITLED22_SHARED_PTR_H
#include <iostream>

template <class T>
class SharedPtr {
  T* ptr_;
  size_t* strong_counter_;
  void Clear() {
    if (strong_counter_) {
      if (*strong_counter_ == 1) {
        delete ptr_;
        delete strong_counter_;
      } else {
        --(*strong_counter_);
      }
    }
    ptr_ = nullptr;
    strong_counter_ = nullptr;
  }
 public:
   SharedPtr() : ptr_(nullptr), strong_counter_(nullptr) {}
   explicit SharedPtr(T* ptr) : ptr_(ptr), strong_counter_(ptr ? new size_t(1) : nullptr) {
     if (!ptr) {
       delete strong_counter_;
       strong_counter_ = nullptr;
     }
   }
   SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
     if (ptr_) {
       ++(*strong_counter_);
     }
   }
   SharedPtr& operator=(const SharedPtr& other) {
     if (this != &other) {
       Clear();
       ptr_ = other.ptr_;
       strong_counter_ = other.strong_counter_;
       if (ptr_) {
         ++(*strong_counter_);
       }
     }
     return *this;
   }
   ~SharedPtr() {
     Clear();
   }
   SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
     other.ptr_ = nullptr;
     other.strong_counter_ = nullptr;
   }
   SharedPtr& operator=(SharedPtr&& other) noexcept {
     if (this != &other) {
       Clear();
       ptr_ = other.ptr_;
       strong_counter_ = other.strong_counter_;
       other.ptr_ = nullptr;
       other.strong_counter_ = nullptr;
     }
     return *this;
   }
   void Reset(T* new_ptr = nullptr) {
     if (ptr_ != new_ptr) {
       Clear();
       ptr_ = new_ptr;
       strong_counter_ = ptr_ ? new size_t(1) : nullptr;
     }
   }
   void Swap(SharedPtr& ptr) {
     std::swap(ptr_, ptr.ptr_);
     std::swap(strong_counter_, ptr.strong_counter_);
   }
   T* Get() const {
     return ptr_;
   }
   [[nodiscard]] size_t UseCount() const {
     return strong_counter_ ? *strong_counter_ : 0;
   }
   T& operator*() const {
     return *ptr_;
   }
   T* operator->() const {
     return ptr_;
   }
   explicit operator bool() const {
     return ptr_ != nullptr;
   }
};

#endif  // UNTITLED22_SHARED_PTR_H
