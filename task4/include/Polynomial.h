#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "List.h"

class Polynomial {
 private:
  struct Monom {
    double_t value;
    std::vector<int32_t> degrees;
    Monom(const double_t &value, const std::vector<int32_t> &degrees);
    Monom();
  };

  List<Monom> nodes;

  [[nodiscard]] std::pair<size_t, size_t> *findSimilar() const;
  void sum();

  void sort();
  void clear();

  bool hasZero() const;
  bool isBigger(const Polynomial &p) const;

  Polynomial operator* (const Monom &m) const;
 protected:
  Polynomial();

 public:
  Polynomial(const std::vector<double_t> &values,const std::vector<std::vector<int32_t>> &degrees);

  Polynomial operator+ (const Polynomial &p) const;
  Polynomial operator- (const Polynomial &p) const;
  Polynomial operator* (const Polynomial &p) const;
  Polynomial operator/ (const Polynomial &p) const;

  Polynomial &operator+= (const Polynomial &p);
  Polynomial &operator-= (const Polynomial &p);
  Polynomial &operator*= (const Polynomial &p);
  Polynomial &operator/= (const Polynomial &p);

  Polynomial operator+ (const double_t &n) const;
  Polynomial operator- (const double_t  &n) const;
  Polynomial operator* (const double_t  &n) const;
  Polynomial operator/ (const double_t  &n) const;

  Polynomial &operator+= (const double_t  &n);
  Polynomial &operator-= (const double_t  &n);
  Polynomial &operator*= (const double_t  &n);
  Polynomial &operator/= (const double_t  &n);

  [[nodiscard]] Polynomial multiplyByVariable(size_t index) const;
  [[nodiscard]] Polynomial divideByVariable(size_t index) const;

  Polynomial operator() (const uint32_t &power) const;

  [[nodiscard]] double_t execute(const std::vector<double_t> &parameters) const;
  friend std::ostream &operator<<(std::ostream &out, const Polynomial &polynomial);
};
