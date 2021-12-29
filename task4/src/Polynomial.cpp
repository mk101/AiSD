#include "Polynomial.h"

Polynomial::Monom::Monom(const double_t &value, const std::vector<int32_t> &degrees) : value(value), degrees(degrees) {}
Polynomial::Monom::Monom() : value(0) {}

Polynomial::Polynomial() : nodes() {}
Polynomial::Polynomial(const std::vector<double_t> &values,const std::vector<std::vector<int32_t>> &degrees) {
  assert(values.size() == degrees.size() && "Count of values and degrees must me equal");
  size_t degs = degrees[0].size();
  for (const auto &d : degrees) {
    assert (d.size() == degs && "Count of degrees must be equal");
  }

  for (size_t i = 0; i < values.size(); i++) {
    nodes.insert({values[i], degrees[i]});
  }

  sum();
  sort();
}


Polynomial Polynomial::operator+(const Polynomial &p) const {
  Polynomial buf(*this);

  for (auto &b : p.nodes) {
    bool has = false;
    for (auto &a : buf.nodes) {
      if (a.degrees == b.degrees) {
        a.value += b.value;
        has = true;
        break;
      }
    }
    if (!has) {
      buf.nodes.insert({b.value, b.degrees});
    }
  }

  buf.sum();
  buf.sort();
  return buf;
}
Polynomial Polynomial::operator-(const Polynomial &p) const {
  Polynomial buf(*this);
  
  for (auto &b : p.nodes) {
    bool has = false;
    for (auto &a : buf.nodes) {
      if (a.degrees == b.degrees) {
        a.value -= b.value;
        has = true;
        break;
      }
    }
    if (!has) {
      buf.nodes.insert({-b.value, b.degrees});
    }
  }

  buf.sum();
  buf.sort();
  return buf;
}
Polynomial Polynomial::operator*(const Polynomial &p) const {
  Polynomial res;

  for (auto &a : nodes) {
    for (auto &b : p.nodes) {
      std::vector<int32_t> degrees = a.degrees.size() > b.degrees.size()
                                    ? a.degrees : b.degrees;
      auto &min = a.degrees.size() > b.degrees.size()
                                  ? b.degrees : a.degrees;

      for (size_t i = 0; i < min.size(); i++) {
        degrees.at(i) += min.at(i);
      }

      res.nodes.insert({a.value*b.value, degrees});
    }
  }

  res.sum();
  res.sort();
  return res;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &polynomial) {
  char p = 'a';
  std::stringstream s;
  for (auto &n : polynomial.nodes) {
    if (n.value != 0) {
      s << (n.value >= 0 ? "+ " : "- ") << abs(n.value);
      for (size_t i = 0; i < n.degrees.size(); i++) {
        if (n.degrees[i] != 0 && n.degrees[i] != 1) {
          s << static_cast<char>((p + i)) << '^' << n.degrees[i];
        } else if (n.degrees[i] == 1) {
          s << static_cast<char>((p + i));
        }
      }
      s << " ";
    }
  }
  std::string res = s.str();
  out << std::string(res.begin() + 1,  res.end());

  return out;
}
void Polynomial::sum() {
  std::pair<size_t, size_t> *similar = nullptr;
  while ((similar = findSimilar()) != nullptr) {
    nodes[similar->first].value += nodes[similar->second].value;
    nodes.removeAt(similar->second);
    delete similar;
  }
}
std::pair<size_t, size_t> *Polynomial::findSimilar() const {
  for (size_t i = 0; i < nodes.getSize() - 1; i++) {
    for (size_t j = i+1; j < nodes.getSize(); j++) {
      if (nodes[i].degrees == nodes[j].degrees) {
        return new std::pair<size_t, size_t>(i,j);
      }
    }
  }

  return nullptr;
}
void Polynomial::sort() {
  clear();
  std::vector<Monom> ns;

  for (auto &n : nodes) {
    ns.push_back(n);
  }

  std::sort(ns.begin(),  ns.end(), [](const Monom &n1, const Monom &n2) {
    for (size_t i = 0; i < n1.degrees.size(); i++) {
      if (n1.degrees[i] < n2.degrees[i]) {
        return false;
      }
    }
    return true;
  });
}
Polynomial &Polynomial::operator+=(const Polynomial &p) {
  (*this) = (*this) + p;
  return *this;
}
Polynomial &Polynomial::operator-=(const Polynomial &p) {
  (*this) = (*this) - p;
  return *this;
}
Polynomial &Polynomial::operator*=(const Polynomial &p) {
  (*this) = (*this) * p;
  return *this;
}
Polynomial Polynomial::operator+(const double_t &n) const {
  Polynomial p({n}, {{0}});
  return (*this) + p;
}
Polynomial Polynomial::operator-(const double_t &n) const {
  Polynomial p({n}, {{0}});
  return (*this) - p;
}
Polynomial Polynomial::operator*(const double_t &n) const {
  Polynomial p({n}, {{0}});
  return (*this) * p;
}
Polynomial &Polynomial::operator+=(const double_t &n) {
  Polynomial p({n}, {{0}});
  (*this) += p;
  return (*this);
}
Polynomial &Polynomial::operator-=(const double_t &n) {
  Polynomial p({n}, {{0}});
  (*this) -= p;
  return (*this);
}
Polynomial &Polynomial::operator*=(const double_t &n) {
  Polynomial p({n}, {{0}});
  (*this) *= p;
  return (*this);
}
Polynomial Polynomial::multiplyByVariable(size_t index) const {
  Polynomial p(*this);
  for (auto &n : p.nodes) {
    n.degrees[index]++;
  }

  return p;
}
Polynomial Polynomial::divideByVariable(size_t index) const {
  Polynomial p(*this);
  for (auto &n : p.nodes) {
    n.degrees[index]--;
  }

  return p;
}
Polynomial Polynomial::operator()(const uint32_t &power) const {
  Polynomial p(*this);
  Polynomial res = p;

  if (power == 0) {
    return {{1}, {{0}}};
  }

  for (int32_t i = 1; i < power; i++) {
    res *= p;
  }

  return res;
}
double_t Polynomial::execute(const std::vector<double_t> &parameters) const {
  double_t  res = 0;

  assert(parameters.size() == nodes[0].degrees.size() && "Parameters size must be equal");

  for (const auto &n : nodes) {
    double_t k = 1;
    for (size_t i = 0; i < n.degrees.size(); i++) {
      k *= pow(parameters[i], n.degrees[i]);
    }
    res += n.value * k;
  }

  return res;
}
Polynomial Polynomial::operator/(const Polynomial &p) const {
  Polynomial p1(*this);
  Polynomial p2(p);
  p1.sort();
  p2.sort();

  auto degSize1 = p1.nodes[0].degrees.size();
  auto degSize2 = p2.nodes[0].degrees.size();
  assert(degSize1 == degSize2);

  auto &degSize = degSize1;

  for (size_t i = 0; i < degSize; i++) {
    assert(p1.nodes[0].degrees[i] >= p2.nodes[0].degrees[i]);
  }

  Polynomial res;

  while (p1.isBigger(p2)) {
    double v = p1.nodes[0].value / p2.nodes[0].value;
    std::vector<int32_t> d;
    for (size_t i = 0; i < degSize; i++) {
      d.push_back(p1.nodes[0].degrees[i] - p2.nodes[0].degrees[i]);
    }

    Monom r(v, d);

    res.nodes.insert(r);
    p1 -= p2 * r;
    p1.sort();
  }

  return res;
}

bool Polynomial::isBigger(const Polynomial &p) const {
  for (size_t i = 0; i < nodes[0].degrees.size(); i++) {
    if (nodes[0].degrees[i] < p.nodes[0].degrees[i]) {
      return false;
    }
  }

  return true;
}

void Polynomial::clear() {
  while (hasZero()) {
    for (size_t i = 0; i < nodes.getSize(); i++) {
      if (nodes[i].value == 0) {
        nodes.removeAt(i);
        break;
      }
    }
  }
}
bool Polynomial::hasZero() const {
  for (auto &m : nodes) {
    if (m.value == 0) {
      return true;
    }
  }

  return false;
}
Polynomial Polynomial::operator*(const Polynomial::Monom &m) const {
  assert(m.degrees.size() == nodes[0].degrees.size());

  Polynomial res(*this);

  for (auto &n : res.nodes) {
    n.value *= m.value;
    for (size_t i = 0; i < n.degrees.size(); i++) {
      n.degrees[i] += m.degrees[i];
    }
  }

  return res;
}
Polynomial &Polynomial::operator/=(const Polynomial &p) {
  (*this) = (*this) / p;
  return *this;
}
Polynomial Polynomial::operator/(const double_t &n) const {
  Polynomial p({n}, {{0}});
  return (*this) / p;
}
Polynomial &Polynomial::operator/=(const double_t &n) {
  Polynomial p({n}, {{0}});
  (*this) /= p;
  return (*this);
}



