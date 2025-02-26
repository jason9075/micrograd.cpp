#include <iostream>

#include "engine.hpp"

int main(int argc, char *argv[]) {
  std::cout << "<<< Program started >>>" << std::endl;
  Value v1(1);
  Value v2(2.2f);
  Value v3 = v1 + v2;
  Value v4 = v1 * 2.1f;

  std::cout << v3 << std::endl;
  std::cout << v4 << std::endl;
  return 0;
}
