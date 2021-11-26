#include "MathExpression.h"
MathExpression::MathExpression(const std::string &formula, const Table<std::string, double> &parameters)
    : formula(formula), parameters(parameters) {}

double MathExpression::Execute() {
  TStack<double> stack(5);
  Translator translator(formula);
  auto tokens = translator.Translate();

  for (const auto &token : tokens) {
    if (std::isdigit(token.GetValue()[0])) {
      stack.Push(std::stod(token.GetValue()));
    } else if (token.GetValue()[0] <= 'z' && token.GetValue()[0] >= 'a') {
        stack.Push(parameters[token.GetValue()]);
    } else {
      double d1;
      switch (token.GetValue()[0]) {
        case '+':
          d1 = stack.Pop();
          stack.Push(d1 + stack.Pop());
          break;
        case '-':
          d1 = stack.Pop();
          stack.Push(stack.Pop() - d1);
          break;
        case '*':
          d1 = stack.Pop();
          stack.Push(stack.Pop() * d1);
          break;
        case '/':
          d1 = stack.Pop();
          if (d1 == 0) {
            throw std::runtime_error("Div by 0 at " + std::to_string(token.GetPosition()));
          }
          stack.Push(stack.Pop() / d1);
          break;
        default:
          throw std::runtime_error("Unknown " + token.GetValue() + " at " + std::to_string(token.GetPosition()));
      }
    }
  }

  return stack.Top();
}
