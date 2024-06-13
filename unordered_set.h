#ifndef UNTITLED20_UNORDERED_SET_H
#define UNTITLED20_UNORDERED_SET_H

#include <list>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

template <class KeyT>
class UnorderedSet {
 private:
  std::vector<std::list<KeyT>> st_;
  size_t el_count_ = 0;
  std::hash<KeyT> help_;

 public:
  [[nodiscard]] size_t ElementCount() const {
    return el_count_;
  }

  UnorderedSet() {
    st_.resize(0);
    el_count_ = 0;
  }

  explicit UnorderedSet(size_t count) {
    st_.resize(count);
    el_count_ = 0;
  }

  template <class ForwardIt>
  UnorderedSet(ForwardIt first, ForwardIt last) : el_count_(0) {
    st_.resize(std::distance(first, last));
    for (auto it = first; it != last; ++it) {
      Insert(*it);
    }
  }

  UnorderedSet(const UnorderedSet& other) : st_(other.st_), el_count_(other.el_count_) {
  }

  UnorderedSet(UnorderedSet&& other) noexcept : st_(std::move(other.st_)), el_count_(other.el_count_) {
    other.Clear();
  }

  UnorderedSet& operator=(UnorderedSet&& other) noexcept {
    st_ = std::move(other.st_);
    el_count_ = other.el_count_;
    other.Clear();
    return *this;
  }

  UnorderedSet& operator=(const UnorderedSet& other) {
    st_ = other.st_;
    el_count_ = other.el_count_;
    return *this;
  }

  size_t Size() const {
    return el_count_;
  }

  bool Empty() const {
    return el_count_ == 0;
  }

  void Clear() {
    st_.clear();
    st_.resize(0);
    el_count_ = 0;
  }

  bool Insert(const KeyT& key) {
    if (st_.empty()) {
      st_.resize(1);
    }
    if (Find(key)) {
      return false;
    }
    if (LoadFactor() >= 1.0) {
      Rehash(BucketCount() * 2);
    }
    st_[Bucket(key)].push_back(key);
    el_count_++;
    return true;
  }

  bool Insert(KeyT&& key) {
    if (st_.empty()) {
      st_.resize(1);
    }
    if (Find(key)) {
      return false;
    }
    if (LoadFactor() >= 1.0) {
      Rehash(BucketCount() * 2);
    }
    st_[Bucket(key)].push_back(std::move(key));
    el_count_++;
    return true;
  }

  bool Erase(const KeyT& key) {
    if (Find(key)) {
      std::list<KeyT>& bucket = st_[Bucket(key)];
      auto it = std::find(bucket.begin(), bucket.end(), key);
      if (it != bucket.end()) {
        bucket.erase(it);
        el_count_--;
        return true;
      }
    }
    return false;
  }

  bool Find(const KeyT& key) const {
    if (BucketCount() == 0) {
      return false;
    }
    const std::list<KeyT>& bucket = st_[Bucket(key)];
    return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
  }

  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count < el_count_) {
      return;
    }
    std::vector<std::list<KeyT>> cur(new_bucket_count);
    for (const auto& bucket : st_) {
      for (const auto& item : bucket) {
        size_t idx = help_(item) % new_bucket_count;
        cur[idx].push_back(item);
      }
    }
    st_ = std::move(cur);
  }

  void Reserve(size_t new_bucket_count) {
    if (new_bucket_count > st_.size()) {
      Rehash(new_bucket_count);
    }
  }

  [[nodiscard]] size_t BucketCount() const {
    return st_.size();
  }

  [[nodiscard]] size_t BucketSize(size_t id) const {
    if (id < st_.size()) {
      return st_.at(id).size();
    }
    return 0;
  }

  size_t Bucket(const KeyT& key) const {
    return help_(key) % st_.size();
  }

  [[nodiscard]] double LoadFactor() const {
    return BucketCount() != 0 ? static_cast<double>(el_count_) / BucketCount() : 0.0;
  }
};

#endif  // UNTITLED20_UNORDERED_SET_H
