#pragma once

#include <iostream>

class Value {
private:
  float value;

public:
  Value(int value);
  Value(float value);

  Value(const Value &value);
  Value &operator=(const Value &value);
  friend Value operator+(const Value &lhs, const Value &rhs);
  friend std::ostream &operator<<(std::ostream &os, const Value &value);

  ~Value();
};
