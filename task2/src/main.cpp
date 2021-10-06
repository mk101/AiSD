#include "TVector.h"

int main() {
  TVector<int> v1 = { 1, 2, 3, 4 };
  TVector<int> v2 = { 4, 3, 2, 1 };
  std::cout << v1 << std::endl;

  std::cout << v1 + v2 << std::endl;
  std::cout << v1 - v2 << std::endl;
  std::cout << v1 * v2 << "\n=====\n";

  std::cout << v1 + 42 << std::endl;
  std::cout << v1 - 42 << std::endl;
  std::cout << v1 * 42 << "\n=====\n";

  std::cout << v1[3] << std::endl;
  //v1.TestThis();
  //std::cin >> v1;
  //std::cout << v1;
  return 0;
}