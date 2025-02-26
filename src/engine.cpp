#include "engine.hpp"

Value::Value(int d, const std::unordered_set<std::shared_ptr<Value>> &children,
             const std::string &op)
    : data(static_cast<float>(d)), children(children), op(op) {}

Value::Value(float d,
             const std::unordered_set<std::shared_ptr<Value>> &children,
             const std::string &op)
    : data(d), children(children), op(op) {}

Value::Value(const Value &v) : data(v.data), children(v.children), op(v.op) {}

Value &Value::operator=(const Value &value) {
  if (this != &value) {
    data = value.data;
    children = value.children;
    op = value.op;
  }
  return *this;
}

Value operator+(Value &lhs, Value &rhs) {
  auto result = Value(lhs.data + rhs.data, {}, "+");
  result.children.insert(std::make_shared<Value>(lhs));
  result.children.insert(std::make_shared<Value>(rhs));

  result.backward = [&lhs, &rhs, &result]() {
    lhs.grad += result.grad;
    rhs.grad += result.grad;
  };
  return result;
}

Value operator*(Value &lhs, Value &rhs) {
  auto result = Value(lhs.data * rhs.data, {}, "*");
  result.children.insert(std::make_shared<Value>(lhs));
  result.children.insert(std::make_shared<Value>(rhs));
  result.backward = [&lhs, &rhs, &result]() {
    lhs.grad += rhs.data * result.grad;
    rhs.grad += lhs.data * result.grad;
  };
  return result;
}

std::ostream &operator<<(std::ostream &os, const Value &v) {
  os << "Value(data=" << v.data << ", set=" << v.children.size()
     << ", op=" << v.op << ", grad=" << v.grad << ")";
  return os;
}

bool operator==(const Value &lhs, const Value &rhs) {
  return lhs.data == rhs.data;
}

Value::~Value() {}
