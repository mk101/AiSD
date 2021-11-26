#pragma once
#include <vector>
#include <string>
#include <exception>
#include "TStack.h"
#include "Translator.h"
#include "Table.h"

class MathExpression {
 private:

  std::string formula;
  Table<std::string, double> parameters;
 public:
  MathExpression(const std::string &formula, const Table<std::string, double> &parameters);
  double Execute();
};