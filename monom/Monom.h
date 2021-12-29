#pragma once
//#include "List.h"

#include <cassert>
#include <iostream>
class Monom {
 private:
  double k;
  double *degrees;
  size_t degSize;
 private:
  Monom *next;
 protected:

  Monom();
 public:
  Monom(double k, double *degrees, size_t deg_size);
  Monom(const Monom &m);
  ~Monom();
  Monom &operator=(const Monom &m);
  void setNext(Monom *next);

  [[nodiscard]] Monom *getNext() const;
  Monom operator+(const Monom &m) const;

  Monom operator-(const Monom &m) const;
  Monom operator*(const Monom &m) const;
  Monom operator/(const Monom &m) const;
  [[nodiscard]] bool isDegreesEqual(const Monom &m) const;

  friend std::ostream &operator<<(std::ostream &os, const Monom &monom);
  bool isPositive() const;
};

class Polynom {
 private:
  Monom *head;
  size_t num;
 public:
  Polynom();
  ~Polynom();
  Polynom(const Polynom &p);
  Polynom& operator=(const Polynom &p);
  void appendMonom(const Monom &m);
  Polynom operator+(const Polynom &p) const;
  friend std::ostream &operator<<(std::ostream &out, const Polynom &p);
};



