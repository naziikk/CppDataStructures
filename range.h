#ifndef UNTITLED22_RANGE_H
#define UNTITLED22_RANGE_H
#define REVERSE_RANGE_IMPLEMENTED
#include <iostream>
class Iterator {
  int it_;
  int step_;
public:
    Iterator(int it, int step) : it_(it), step_(step) {
    }
    Iterator& operator++() {
      it_ = it_ + step_;
      return *this;
    }
    int operator*() const {
      return it_;
    }
    bool operator!=(const Iterator& other) const {
      if (step_ == 0) {
        return false;
      }
      if (step_ == INT_MAX) {
        return false;
      }
      if (step_ > 0) {
        return it_ < other.it_;
      }
      return it_ > other.it_;
    }
};
class Range {
  int begin_;
  int step_;
  int end_;
public:
  explicit Range(int end) : begin_(0), step_(1), end_(end) {
  }
  Range(int begin, int end, int step = 1) : begin_(begin), step_(step), end_(end) {
  }
  Iterator begin() const {  // NOLINT
    return Iterator{begin_, step_};
  }
  Iterator end() const {  // NOLINT
    return Iterator{end_, step_};
  }
  Iterator rbegin() const {  // NOLINT
    if (step_ == 0) {
      return Iterator{end_, INT_MAX};
    }
    if (step_ < 0) {
      if (end_ < begin_) {
        return Iterator{end_ - ((end_ - begin_) % step_ != 0 ? (end_ - begin_) % step_ : (end_ - begin_) % step_ + step_), -step_};
      }
      return Iterator{end_ - (end_ - begin_) % step_, INT_MAX};
    }
    return Iterator{end_ - ((end_ - begin_) % step_ ? (end_ - begin_) % step_ : (end_ - begin_) % step_ + step_), -step_};
  }
  Iterator rend() const {  // NOLINT
    if (step_ < 0) {
      if (end_ < begin_) {
        return Iterator{begin_ - step_, -step_};
      }
      return Iterator{begin_ + step_, INT_MAX};
    }
    return Iterator{begin_ - 1, -step_};
  }
};
#endif//UNTITLED22_RANGE_H
