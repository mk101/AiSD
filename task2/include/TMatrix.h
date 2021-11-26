#pragma once
#include "TVector.h"

template<class ValType>
class TMatrix : public TVector<TVector<ValType>>{
 private:
  ValType zero = ValType(0);
 public:
  explicit TMatrix(size_t s = 3) : TVector<TVector<ValType>>(s) {
    for (size_t i = 0; i < s; i++) {
      this->pVector[i] = TVector<ValType>(s-i, i);
    }
  }
  TMatrix(const TMatrix &m) : TVector<TVector<ValType>>(m) {}
  TMatrix(const TVector<TVector<ValType>> &m) : TVector<TVector<ValType>>(m) {}
  TMatrix(const std::initializer_list<TVector<ValType>>& il) {
    this->StartIndex = 0;
    this->Size = il.size();
    size_t k = 0;
    for (auto i = il.begin(); i < il.end(); i++) {
      assert(this->Size == (i->GetSize() + i->GetStartIndex()));
      this->pVector[k++] = *i;
    }
  }

  TMatrix<ValType>& operator=(const TMatrix<ValType> &m) {
    if (this != &m) {
      if (this->Size != m.Size) {
        delete[] this->pVector;
        this->pVector = new TVector<ValType>[m.Size];
      }
      this->Size = m.Size;
      for (size_t i = 0; i < this->Size; i++) {
        this->pVector[i] = m.pVector[i];
      }
    }
    return *this;

  }
  TMatrix<ValType> operator+(const TMatrix<ValType> &m) const {
    return TVector<TVector<ValType>>(*this) + TVector<TVector<ValType>>(m);
  }
  TMatrix<ValType> operator-(const TMatrix<ValType> &m) const {
    return TVector<TVector<ValType>>(*this) - TVector<TVector<ValType>>(m);
  }
  TMatrix<ValType> operator*(const TMatrix<ValType> &m) const {
    TMatrix<ValType> buf(*this);

    for (size_t i = 0; i < this->Size; i++) {
      for (size_t j = 0; j < this->pVector[i].GetSize(); j++) {
        ValType sum = ValType(0);
        for (size_t k = 0; k <= j; k++) {
          sum += this->pVector[i][k] * m.pVector[k+m.pVector[i].GetStartIndex()][j-m.pVector[k].GetStartIndex()];
        }
        buf[i][j] = sum;
      }
    }

    return buf;
  }
  bool operator==(const TMatrix<ValType> &m) const {
    return TVector<TVector<ValType>>(*this) == TVector<TVector<ValType>>(m);
  }

  const ValType& operator()(size_t row, size_t col) const {
    if (col < row) {
      return zero;
    }
    return this->pVector[row][col - row];
  }

  friend std::istream& operator>>(std::istream& in, TMatrix<ValType> &m) {
    for (size_t i = 0; i < m.Size; i++) {
      in >> m.pVector[i];
    }

    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const TMatrix<ValType> &m) {
    for (size_t i = 0; i < m.Size; i++) {
      out << m.pVector[i] << std::endl;
    }

    return out;
  }
};
