#pragma once

#include <mutex>
#include <queue>

namespace ll::safeq {

template<typename T>
class SafeQueue {
private:
  std::queue<T> _q;
  std::mutex _mu;

  using size_type = typename std::queue<T>::size_type;

public:
  SafeQueue() : _q(), _mu() {}

  inline void push(T&& elem) {
    std::lock_guard<std::mutex> lock(_mu);
    _q.push(std::move(elem));
  }
  inline void push(const T& elem) {
    std::lock_guard<std::mutex> lock(_mu);
    _q.push(elem);
  }

  inline T& front() {
    std::lock_guard<std::mutex> lock(_mu);
    return _q.front();
  }
  inline const T& front() const {
    std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(_mu));
    return _q.front();
  }

  inline void pop() {
    std::lock_guard<std::mutex> lock(_mu);
    _q.pop();
  }

  inline void enqueue(T&& elem) {
    push(elem);
  }
  inline void enqueue(const T& elem) {
    push(elem);
  }

  inline T dequeue() {
    std::lock_guard<std::mutex> lock(_mu);
    T x = std::move(_q.front());
    _q.pop();
    return x;
  }

  inline bool empty() {
    std::lock_guard<std::mutex> lock(_mu);
    return _q.empty();
  }

  inline size_type size() {
    std::lock_guard<std::mutex> lock(_mu);
    return _q.size();
  }
};

}// namespace ll::safeq
