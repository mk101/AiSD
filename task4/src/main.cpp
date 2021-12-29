#include "Polynomial.h"


int main() {
  Polynomial p1({8, 4, -2}, {{2}, {1}, {0}});
  Polynomial p2({4, -42}, {{1}, {0}});

  auto p = p1 / p2;
  std::cout << p << std::endl;
  std::cout << p.divideByVariable(0) << std::endl;
  std::cout << p.multiplyByVariable(0) << std::endl;

  return 0;
}