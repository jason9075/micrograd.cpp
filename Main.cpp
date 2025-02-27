#include <iostream>

#include "engine.hpp"

int main(int argc, char *argv[]) {
  std::cout << "<<< Program started >>>" << std::endl;
  auto v1 = Value::create(1.1f);
  auto v2 = Value::create(2);
  auto v3 = v1 + v2;
  auto v4 = Value::create(2.1f);
  v4 = v4 + 1.2f;
  auto v5 = v3 * v4;

  v5->backward();

  std::cout << *v1 << std::endl;
  std::cout << *v2 << std::endl;
  std::cout << *v3 << std::endl;
  std::cout << *v4 << std::endl;
  std::cout << *v5 << std::endl;
  return 0;
}
