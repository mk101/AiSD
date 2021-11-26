#include "Validator.h"

const std::string &TToken::GetValue() const {
  return value;
}
size_t TToken::GetPosition() const {
  return position;
}
TToken::TToken(std::string &value, size_t position) : value(value), position(position) {}
bool TToken::operator==(const TToken &rhs) const {
  return std::tie(value, position) == std::tie(rhs.value, rhs.position);
}
bool TToken::operator!=(const TToken &rhs) const {
  return !(rhs == *this);
}
TToken::TToken() {
  value = "";
  position = 0;
}

Validator::Validator(const std::vector<Token> &tokens) : tokens(tokens), stack() {}
void Validator::Validate() {
  stack.Clear();
  bool isDigit = false;
  //bool isOperator = false;
  bool isBracket = false;
  Token last;
  for (const auto& ch : tokens) {
    if (((std::isdigit(ch.GetValue()[0])) || (ch.GetValue()[0] >= 'a' && ch.GetValue()[0] <= 'z')) && isDigit) {
      throw std::runtime_error(std::string("Error at ") + std::to_string(last.GetPosition()) + std::string(". Extra ") + last.GetValue());
    }

    if ((!((std::isdigit(ch.GetValue()[0])) || (ch.GetValue()[0] >= 'a' && ch.GetValue()[0] <= 'z')) && ch.GetValue() != ")" && ch.GetValue() != "(") && !isDigit && !isBracket) {
      throw std::runtime_error(std::string("Error at ") + std::to_string(last.GetPosition()) + std::string(". Extra ") + last.GetValue());
    }

    isDigit = static_cast<bool>(std::isdigit(ch.GetValue()[0])) || (ch.GetValue()[0] >= 'a' && ch.GetValue()[0] <= 'z');

    if (ch.GetValue() == "(") {
      isBracket = true;
      stack.Push(ch);
    } else if (ch.GetValue() == ")") {
      isBracket = true;
      if (!stack.IsEmpty() && stack.Top().GetValue() == "(") {
        stack.Pop();
      } else {
        throw std::runtime_error(std::string("Error at ") + std::to_string(ch.GetPosition()) + std::string(". Extra ')'"));
      }
    } else {
      isBracket = false;
    }
    last = ch;
  }

  if (!stack.IsEmpty()) {
    throw std::runtime_error(std::string("Error at ") + std::to_string(stack.Top().GetPosition()) + std::string(". Extra '('"));
  }
}
