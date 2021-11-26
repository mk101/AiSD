#include "Translator.h"

Translator::Translator(const std::string& formula) : stack(), formula(formula), tokens(), validator(tokens) {
  generateTokens();
  validator = Validator(tokens);
  validator.Validate();
}
void Translator::generateTokens() {
  size_t cur = 0;
  while(cur < formula.size()) {
    if (formula[cur] >= '0' && formula[cur] <= '9') {
      addDigit(cur);
    } else if (formula[cur] >= 'a' && formula[cur] <= 'z') {
      addWord(cur);
    } else if (formula[cur] == ' ') {
      cur++;
    } else {
      addOperator(cur);
    }
  }
}
void Translator::addDigit(size_t &cur) {
  std::string buf;
  size_t begin = cur;
  bool hasDot = false;
  while ((formula[cur] >= '0' && formula[cur] <= '9') || formula[cur] == '.') {
    if (formula[cur] == '.') {
      if (hasDot) {
        throw std::runtime_error(std::string("Extra . at ") + std::to_string(begin));
      }
      hasDot = true;
    }
    buf += formula[cur++];
  }

  tokens.emplace_back(buf, begin);
}
void Translator::addWord(size_t &cur) {
  std::string buf;
  size_t begin = cur;
  while ((formula[cur] >= 'a' && formula[cur] <= 'z')
        || (formula[cur] >= '0' && formula[cur] <= '9')) {
    buf += formula[cur++];
  }

  tokens.emplace_back(buf, begin);
}
void Translator::addOperator(size_t &cur) {
  std::vector<std::string> operators = {"+", "-", "*", "/", "(", ")"};
  std::string buf = std::string (1, formula[cur++]);
  size_t begin = cur;

  while (cur < formula.size() && std::find(operators.begin(), operators.end(), buf + std::string(1, formula[cur])) != operators.end()) {
    buf += std::string (1, formula[cur++]);
  }

  tokens.emplace_back(buf, begin);
}
std::vector<Token> Translator::Translate() {
  std::vector<Token> result;
  TStack<Token> operators;
  Table<char, size_t> operatorsPr(6);
  operatorsPr.Add('+', 1);
  operatorsPr.Add('-', 1);
  operatorsPr.Add('*', 2);
  operatorsPr.Add('/', 2);
  operatorsPr.Add('(', 3);
  operatorsPr.Add(')', 0);

  for (const auto& token : tokens) {
    auto fst = token.GetValue()[0];
    if (std::isdigit(fst)) {
      result.push_back(token);
    } else if (operatorsPr.HasKey(fst)) {
      if (!operators.IsEmpty() && operatorsPr[operators.Top().GetValue()[0]] >= operatorsPr[fst]) {
        //TODO: убрать костыль
        if (operators.Top().GetValue() == "(") {
          operators.Push(token);
          continue;
        }
        while (!operators.IsEmpty() && operatorsPr[operators.Top().GetValue()[0]] >= operatorsPr[fst]) {
          if (operators.Top().GetValue() == "(") {
            operators.Pop();
            continue;
          }
          result.push_back(operators.Pop());
        }
        if (token.GetValue() != ")") {
          operators.Push(token);
        }
      } else {
        operators.Push(token);
      }
    } else {
      //throw std::exception(":(");
      result.push_back(token);
    }
  }

  while (!operators.IsEmpty()) {
    result.push_back(operators.Pop());
  }

  return result;
}
