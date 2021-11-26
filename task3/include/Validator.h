#pragma once
#include <string>
#include <vector>
#include "TStack.h"

class TToken {
 private:
  std::string value;
  size_t position;
 public:
  TToken(std::string &value, size_t position);
  TToken();
  [[nodiscard]] const std::string &GetValue() const;
  [[nodiscard]] size_t GetPosition() const;
  bool operator==(const TToken &rhs) const;
  bool operator!=(const TToken &rhs) const;
};

using Token = TToken;

class Validator {
 private:
  TStack<Token> stack;
  std::vector<Token> tokens;
 public:
  explicit Validator(const std::vector<Token> &tokens);
  void Validate();
};