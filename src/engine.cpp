#include "engine.hpp"
#include <memory>
#include <stack>

Value::Value(int d, const std::unordered_set<std::shared_ptr<Value>> &children,
             const std::string &op)
    : data(static_cast<float>(d)), children(children), op(op) {}

Value::Value(float d,
             const std::unordered_set<std::shared_ptr<Value>> &children,
             const std::string &op)
    : data(d), children(children), op(op) {}

// Arithmetic operator
// example: v1 + v2
std::shared_ptr<Value> operator+(const std::shared_ptr<Value> &lhs,
                                 const std::shared_ptr<Value> &rhs) {
  std::unordered_set<std::shared_ptr<Value>> children = {lhs, rhs};
  auto result = Value::create(lhs->data + rhs->data, children, "+");

  result->_backward = [lhs, rhs, result]() {
    lhs->grad += result->grad;
    rhs->grad += result->grad;
  };
  return result;
}

std::shared_ptr<Value> operator*(const std::shared_ptr<Value> &lhs,
                                 const std::shared_ptr<Value> &rhs) {

  std::unordered_set<std::shared_ptr<Value>> children = {lhs, rhs};
  auto result = Value::create(lhs->data * rhs->data, children, "*");

  result->_backward = [lhs, rhs, result]() {
    lhs->grad += rhs->data * result->grad;
    rhs->grad += lhs->data * result->grad;
  };
  return result;
}
// example: v1 + 1.2f
std::shared_ptr<Value> operator+(const std::shared_ptr<Value> &lhs, float rhs) {
  std::unordered_set<std::shared_ptr<Value>> children = {lhs};
  auto result = Value::create(lhs->data + rhs, children, "+");

  result->_backward = [lhs, result]() { lhs->grad += result->grad; };
  return result;
}

std::shared_ptr<Value> operator*(const std::shared_ptr<Value> &lhs, float rhs) {
  std::unordered_set<std::shared_ptr<Value>> children = {lhs};
  auto result = Value::create(lhs->data * rhs, children, "*");

  result->_backward = [lhs, rhs, result]() { lhs->grad += rhs * result->grad; };
  return result;
}

void Value::backward() {

  // topological sort
  std::stack<std::shared_ptr<Value>> topo;
  std::unordered_set<std::shared_ptr<Value>> visited;

  // depth first search
  std::function<void(std::shared_ptr<Value>)> buildTopo =
      [&](std::shared_ptr<Value> v) {
        if (visited.find(v) != visited.end())
          return;

        visited.insert(v);
        for (auto &child : v->children) {
          buildTopo(child);
        }
        topo.push(v);
      };

  buildTopo(shared_from_this());
  this->grad = 1;

  while (!topo.empty()) {
    // cpp pop() does not return the value
    auto v = topo.top();
    topo.pop();
    v->_backward();
  }
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
