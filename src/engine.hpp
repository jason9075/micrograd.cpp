#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_set>

// because of circular dependency, we need to forward declare Value
class Value : public std::enable_shared_from_this<Value> {
public:
  float data;
  std::unordered_set<std::shared_ptr<Value>> children;
  std::string op;
  std::function<void()> _backward = []() {}; // Function pointer
  float grad = 0;

  static std::shared_ptr<Value>
  create(int d, const std::unordered_set<std::shared_ptr<Value>> &children = {},
         const std::string &op = "") {
    return std::shared_ptr<Value>(new Value(d, children, op));
  }
  static std::shared_ptr<Value>
  create(float d,
         const std::unordered_set<std::shared_ptr<Value>> &children = {},
         const std::string &op = "") {
    return std::shared_ptr<Value>(new Value(d, children, op));
  }

  // prevent copy constructor and assignment operator
  Value(const Value &) = delete;
  Value &operator=(const Value &) = delete;

  // Arithmetic operator
  // example: v1 + v2
  friend std::shared_ptr<Value> operator+(const std::shared_ptr<Value> &lhs,
                                          const std::shared_ptr<Value> &rhs);
  friend std::shared_ptr<Value> operator*(const std::shared_ptr<Value> &lhs,
                                          const std::shared_ptr<Value> &rhs);
  // example: v1 + 1.2f
  friend std::shared_ptr<Value> operator+(const std::shared_ptr<Value> &lhs,
                                          float rhs);
  friend std::shared_ptr<Value> operator*(const std::shared_ptr<Value> &lhs,
                                          float rhs);

  void backward();

  // Output stream operator
  friend std::ostream &operator<<(std::ostream &os, const Value &value);

  ~Value();

private:
  Value(int d, const std::unordered_set<std::shared_ptr<Value>> &children,
        const std::string &op);
  Value(float d, const std::unordered_set<std::shared_ptr<Value>> &children,
        const std::string &op);
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
