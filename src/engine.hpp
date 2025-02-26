#pragma once

#include <iostream>
#include <memory>
#include <unordered_set>

class Value {
private:
  float data;
  std::unordered_set<std::shared_ptr<Value>> children;
  std::string op;

public:
  Value(int d, const std::unordered_set<std::shared_ptr<Value>> &children = {},
        const std::string &op = "");
  Value(float d,
        const std::unordered_set<std::shared_ptr<Value>> &children = {},
        const std::string &op = "");
  Value(const Value &v);

  // Assignment operator
  Value &operator=(const Value &value);

  // Arithmetic operator
  friend Value operator+(const Value &lhs, const Value &rhs);
  friend Value operator*(const Value &lhs, const Value &rhs);

  // Output stream operator
  friend std::ostream &operator<<(std::ostream &os, const Value &value);

  float getData() const { return data; }
  ~Value();
};

// Comparison operator
bool operator==(const Value &lhs, const Value &rhs);

// Hash function for unordered_set
namespace std {
template <> struct hash<Value> {
  std::size_t operator()(const Value &v) const noexcept {
    return std::hash<float>{}(v.getData());
  }
};

} // namespace std
