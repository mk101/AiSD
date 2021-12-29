#include "Monom.h"

Monom::Monom() : k(0), degSize(0), degrees(nullptr), next(nullptr) {}
Monom::Monom(double k, double *degrees, size_t deg_size)
: k(k), degrees(degrees), degSize(deg_size), next(nullptr) {}
Monom::Monom(const Monom &m) {
  k = m.k;
  degSize = m.degSize;
  degrees = new double[degSize];
  for (size_t i = 0; i < degSize; i++) {
    degrees[i] = m.degrees[i];
  }
  if (m.next != nullptr)
    next = new Monom(*m.next);
  else
    next = nullptr;
}
Monom::~Monom() {
  delete[] degrees;
}
Monom &Monom::operator=(const Monom &m) {
  if (this == &m) {
    return *this;
  }
  k = m.k;
  degSize = m.degSize;
  delete[] degrees;
  degrees = new double[degSize];
  for (size_t i = 0; i < degSize; i++) {
    degrees[i] = m.degrees[i];
  }
  if (m.next != nullptr)
    next = new Monom(*m.next);

  return *this;
}
// 2x + 4xy
Monom Monom::operator+(const Monom &m) const {
  Monom res(*this);

  if (degSize == m.degSize) {
    res.k += m.k;
  } else {
    res.next = new Monom(m);
  }

  return res;
}
Monom Monom::operator-(const Monom &m) const {
  Monom res(*this);

  if (degSize == m.degSize) {
    res.k -= m.k;
  } else {
    res.next = new Monom(-m.k, m.degrees, m.degSize);
  }

  return res;
}
Monom Monom::operator*(const Monom &m) const {
  Monom res;
  const Monom *a;

  if (degSize >= m.degSize) {
    res = Monom(*this);
    a = &m;
  } else {
    res = Monom(m);
    a = this;
  }

  res.k *= a->k;
  for (size_t i = 0; i < a->degSize; i++) {
    res.degrees[i] += a->degrees[i];
  }

  return res;
}
Monom Monom::operator/(const Monom &m) const {
  Monom res;
  const Monom *a;

  if (degSize >= m.degSize) {
    res = Monom(*this);
    a = &m;
  } else {
    res = Monom(m);
    a = this;
  }

  res.k /= a->k;
  for (size_t i = 0; i < a->degSize; i++) {
    res.degrees[i] -= a->degrees[i];
  }

  return res;
}
Monom *Monom::getNext() const {
  return next;
}
void Monom::setNext(Monom *next) {
  Monom::next = next;
}
bool Monom::isDegreesEqual(const Monom &m) const {
  if (degSize != m.degSize) {
    return false;
  }

  for (size_t i = 0; i < degSize; i++) {
    if (m.degrees[i] != degrees[i]) {
      return false;
    }
  }

  return true;
}
std::ostream &operator<<(std::ostream &out, const Monom &m) {
  out << abs(m.k);
  char ch = 'a';

  for (size_t i = 0; i < m.degSize; i++) {
    out << ch << '^' << m.degrees[i];
    ch++;
  }

  return out;
}
bool Monom::isPositive() const {
  return k >= 0;
}

int main() {

  Monom x(1, new double[2]{1,1}, 2);
  Monom y(4, new double[2]{1,1}, 2);
  Monom x1(-6, new double[2]{2,2}, 2);
  Monom y1(42, new double[2]{2,3}, 2);

  Monom z = x + y;
  std::cout << z << std::endl;

  Polynom p1;
  Polynom p2;
  p1.appendMonom(x);
  p1.appendMonom(x1);
  p1.appendMonom(z);

  p2.appendMonom(y);
  p2.appendMonom(y1);
  p2.appendMonom(z);

  std::cout << p1 + p2;

  return 0;
}
Polynom::Polynom() : head(nullptr), num(0) {}
Polynom::~Polynom() {
  Monom *next = nullptr;
  while (head != nullptr) {
    next = head->getNext();
    delete head;
    head = next;
  }
}
void Polynom::appendMonom(const Monom &m) {
  if (head == nullptr) {
    head = new Monom(m);
    num++;
    return;
  }

  auto *ptr = new Monom(m);
  ptr->setNext(head);
  head = ptr;
  num++;
}
Polynom Polynom::operator+(const Polynom &p) const {
  Polynom res(*this);
  Monom *ptr = p.head;

  while (ptr != nullptr) {
    Monom *hPtr = res.head;
    while (hPtr != nullptr && !ptr->isDegreesEqual(*hPtr)) {
      hPtr = hPtr->getNext();
    }

    if (hPtr == nullptr) {
      res.appendMonom(*ptr);
    } else {
      *hPtr = (*hPtr) + (*ptr);
    }

    ptr = ptr->getNext();
  }

  return res;
}
std::ostream &operator<<(std::ostream &out, const Polynom &p) {
  Monom *ptr = p.head;
  while (ptr != nullptr) {
    if (ptr == p.head) {
      out << *ptr << ' ';
    } else {
      out << (ptr->isPositive() ? "+ " : "- ") << *ptr << ' ';
    }

    ptr = ptr->getNext();
  }

  return out;
}
Polynom::Polynom(const Polynom &p) {
  head = new Monom(*p.head);
  num = p.num;
}
Polynom &Polynom::operator=(const Polynom &p) {
  if (this == &p) {
    return *this;
  }

  head = new Monom(*p.head);
  num = p.num;

  return *this;
}
