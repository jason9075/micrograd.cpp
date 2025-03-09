#include "engine.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

int main() {
  // Test addition: v1 + v2 should have data ≈ 3.1 (1.1 + 2.0)
  auto v1 = Value::create(1.1f);
  auto v2 = Value::create(2);
  auto v3 = v1 + v2;
  assert(std::fabs(v3->data - 3.1f) < 1e-5);
  std::cout << "Addition test passed!" << std::endl;

  // Test multiplication: (v1 + v2) * v4 should have data ≈ 3.1 * 2.1
  auto v4 = Value::create(2.1f);
  auto v5 = v3 * v4;
  assert(std::fabs(v5->data - (3.1f * 2.1f)) < 1e-5);
  std::cout << "Multiplication test passed!" << std::endl;

  return 0;
}
