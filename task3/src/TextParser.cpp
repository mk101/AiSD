#include "TextParser.h"

std::vector<std::string> split(const std::string &source, char d) {
  std::vector<std::string> res;
  std::istringstream f(source);
  std::string s;
  while (std::getline(f, s, d)) {
    res.push_back(s);
  }

  return res;
}

TextParser::TextParser(const std::string &path) : stream(path) {}
TextParser::~TextParser() {
  if(stream.is_open()) {
    stream.close();
  }
}
void TextParser::Parse(ParseFunc func) {
  std::string line;
  while (std::getline(stream, line)) {
    auto strs = split(line, ';');
    Table<std::string, double> table(5);
    if (strs.size() > 1) {
      auto parameters = split(strs[1], ',');
      for (const auto &parameter : parameters) {
        auto ss = split(parameter, '=');
        if (ss.size() != 2) {
          throw std::runtime_error("Expected <name> = <value>");
        }
        ss[0].erase(std::remove_if(ss[0].begin(), ss[0].end(), isspace), ss[0].end());
        ss[1].erase(std::remove_if(ss[1].begin(), ss[1].end(), isspace), ss[1].end());
        table.Add(ss[0], std::stod(ss[1]));
      }
    }

    func(strs[0], table);
  }
}
