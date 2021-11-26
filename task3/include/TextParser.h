#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include "Table.h"
#include "Validator.h"

using ParseFunc = void (*)(const std::string&, const Table<std::string, double>&);

class TextParser {
 private:
  std::ifstream stream;
 public:
  explicit TextParser(const std::string &path);
  ~TextParser();
  void Parse(ParseFunc func);
};