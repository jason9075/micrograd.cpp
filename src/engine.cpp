#include "engine.hpp"

Value::Value(int v) : value(static_cast<float>(v)) {}
Value::Value(float v) : value(v) {}

Value::Value(const Value &v) : value(v.value) {}
Value &Value::operator=(const Value &v) {
  value = v.value;
  return *this;
}

Value operator+(const Value &lhs, const Value &rhs) {
  return Value(lhs.value + rhs.value);
}

std::ostream &operator<<(std::ostream &os, const Value &v) {
  os << "Value(" << v.value << ")";
  return os;
}

Value::~Value() {}
