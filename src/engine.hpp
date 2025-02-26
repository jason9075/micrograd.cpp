#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_set>

class Value {
public:
  float data;
  std::unordered_set<std::shared_ptr<Value>> children;
  std::string op;
  std::function<void()> backward = []() {}; // Function pointer
  float grad = 0;
  Value(int d, const std::unordered_set<std::shared_ptr<Value>> &children = {},
        const std::string &op = "");
  Value(float d,
        const std::unordered_set<std::shared_ptr<Value>> &children = {},
        const std::string &op = "");
  Value(const Value &v);

  // Assignment operator
  Value &operator=(const Value &value);

  // Arithmetic operator
  friend Value operator+(Value &lhs, Value &rhs);
  friend Value operator*(Value &lhs, Value &rhs);

  // Output stream operator
  friend std::ostream &operator<<(std::ostream &os, const Value &value);

  ~Value();
};

// Comparison operator
bool operator==(const Value &lhs, const Value &rhs);

// Hash function for unordered_set
namespace std {
template <> struct hash<Value> {
  std::size_t operator()(const Value &v) const noexcept {
    return std::hash<float>{}(v.data);
  }
};

} // namespace std
