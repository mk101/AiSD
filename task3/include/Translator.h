#pragma once
#include "TStack.h"
#include <string>
#include <exception>
#include <format>
#include <vector>
#include <map>
#include <cctype>
#include "Validator.h"
#include "Table.h"

class Translator {
 private:
  TStack<Token> stack;
  std::string formula;
  std::vector<Token> tokens;
  Validator validator;

  void generateTokens();
  void addDigit(size_t &cur);
  void addWord(size_t &cur);
  void addOperator(size_t &cur);
 public:
  explicit Translator(const std::string &formula);
  std::vector<Token> Translate();
};
