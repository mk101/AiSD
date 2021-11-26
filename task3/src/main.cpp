#include "MathExpression.h"
#include "TextParser.h"
#include <iostream>

/*
2 + 4 * (1 + a); a=10
2*(1+2/3)+2
2 ** 4
2 + 2*2
1 + b; a=42


 1 + 2
1 + 2 * (3-2)-4
(((1+23)*1-22)+5)*2-(1
1 + a; a=5
2 * a + b - c; a=5, b=7, c=-3
5 // 5
7 ** 3
 */

int main() {

    TextParser tp("data.txt");
    tp.Parse([](const std::string& formula, const Table<std::string, double>& parameters){
      static size_t pos = 1;
      std::cout << pos++ << ". ";
      try {
        MathExpression me(formula, parameters);
        double res = me.Execute();
        std::cout << res;
      } catch (std::exception& e){
        std::cout << e.what();
      }
      std::cout << std::endl;
    });
  return 0;
}

//Table, Validator, Translator, MathExpression