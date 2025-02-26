#include <iostream>

#include "engine.hpp"

int main(int argc, char *argv[]) {
  std::cout << "<<< Program started >>>" << std::endl;
  Value v1(2);
  Value v2(2.2f);
  Value v3 = v1 * v2;
  Value v4 = 2.1f;
  Value v5 = v3 * v4;

  v5.grad = 1.0f;
  v5.backward();
  v4.backward();
  v3.backward();
  v2.backward();
  v1.backward();

  std::cout << v1 << std::endl;
  std::cout << v2 << std::endl;
  std::cout << v3 << std::endl;
  std::cout << v4 << std::endl;
  std::cout << v5 << std::endl;
  return 0;
}
