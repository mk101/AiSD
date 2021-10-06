#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

template<class ValType>
class TVector {
 protected:
  size_t Size;
  ValType* pVector;
  size_t StartIndex;
 public:
  //Clang-Tidy: Constructors that are callable with a single argument must be marked explicit to avoid unintentional implicit conversions
  explicit TVector(size_t size = 10, size_t startIndex = 0) : Size(size), StartIndex(startIndex) {
    pVector = new ValType[size];
  }
  TVector(const TVector<ValType>& v) : Size(v.Size), StartIndex(v.StartIndex) {
    pVector = new ValType[Size];
    for (size_t i = 0; i < Size; i++) {
      pVector[i] = v.pVector[i];
    }
  }
  TVector(const std::initializer_list<ValType>& il) {
    StartIndex = 0;
    Size = 0;
    size_t k = 0;
    for (auto i = il.begin(); i < il.end(); i++) {
      if (*i == 0 && Size == 0) {
        StartIndex++;
        continue;
      } else if (Size == 0) {
        Size = il.size() - StartIndex;
        pVector = new ValType[Size];
        pVector[k++] = *i;
        continue;
      }

      pVector[k++] = *i;
    }
  }
  ~TVector() {
    delete[] pVector;
  }
  [[nodiscard]] size_t GetSize() const {
    return Size;
  }
  [[nodiscard]] size_t GetStartIndex() const {
    return StartIndex;
  }

  ValType& GetValue(const size_t pos) {
    assert(pos < Size);
    return pVector[pos];
  }
  const ValType& GetValue(const size_t pos) const {
    assert(pos < Size);
    return pVector[pos];
  }

  ValType& operator[] (size_t pos) {
    return GetValue(pos);
  }
  const ValType& operator[] (size_t pos) const {
    return GetValue(pos);
  }

  bool operator==(const TVector<ValType>& v) const {
    if (Size == v.Size && StartIndex == v.StartIndex) {
      for (size_t i = 0; i < Size; i++) {
        if (pVector[i] != v.pVector[i]) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  TVector<ValType>& operator=(const TVector<ValType>& v) {
    if (this == &v) {
      return *this;
    }

    Size = v.Size;
    StartIndex = v.StartIndex;

    delete[] pVector;
    pVector = new ValType[Size];
    for (size_t i = 0; i < Size; i++) {
      pVector[i] = v.pVector[i];
    }

    return *this;
  }

  TVector<ValType> operator+(const ValType& vt) const {
    TVector<ValType> buf(*this);
    for (size_t i = 0; i < Size; i++) {
      buf[i] = buf[i] + vt;
    }

    return buf;
  }
  TVector<ValType> operator-(const ValType& vt) const {
    TVector<ValType> buf(*this);
    for (size_t i = 0; i < Size; i++) {
      buf[i] = buf[i] - vt;
    }

    return buf;
  }
  TVector<ValType> operator*(const ValType& vt) const {
    TVector<ValType> buf(*this);
    for (size_t i = 0; i < Size; i++) {
      buf[i] = buf[i] * vt;
    }

    return buf;
  }

  TVector<ValType> operator+(const TVector<ValType>& vt) const {
    assert(Size == vt.Size && StartIndex == vt.StartIndex);
    TVector<ValType> buf(*this);
    for (size_t i = 0; i < Size; i++) {
      buf[i] = buf[i] + vt[i];
    }

    return buf;
  }
  TVector<ValType> operator-(const TVector<ValType>& vt) const {
    assert(Size == vt.Size && StartIndex == vt.StartIndex);
    TVector<ValType> buf(*this);
    for (size_t i = 0; i < Size; i++) {
      buf[i] = buf[i] - vt[i];
    }

    return buf;
  }
  TVector<ValType> operator*(const TVector<ValType>& vt) const {
    assert(Size == vt.Size && StartIndex == vt.StartIndex);
    TVector<ValType> buf(*this);
    for (size_t i = 0; i < Size; i++) {
      buf[i] = buf[i] * vt[i];
    }

    return buf;
  }

  friend std::istream& operator>>(std::istream& in, TVector<ValType>& v) {
    for (size_t i = 0; i < v.GetSize(); i++) {
      in >> v[i];
    }
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const TVector<ValType>& v) {
    out << '{';
    std::string buf;
    for (size_t i = 0; i < v.GetStartIndex(); i++) {
      buf += "0, ";
    }
    for (size_t i = 0; i < v.GetSize(); i++) {
      buf += std::to_string(v[i]);
      buf += ", ";
    }

    out << (!buf.empty() ? std::string(buf.begin(), buf.end() - 2) : std::string()) << '}';
    return out;
  }

//  void TestThis() {
//    std::cout << "========================\n" << this << std::endl << &(*this);
//  }
};

