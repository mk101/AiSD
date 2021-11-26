#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>

template<class T>
class TStack {
 private:
  T *Data;
  int32_t Num;
  int32_t TopIndex;
 public:
  TStack(int32_t num = 10) {
    assert(num != 0);
    Data = new T[num];
    Num = num;
    TopIndex = -1;
  }
  TStack(const TStack &st) {
    Num = st.Num;
    TopIndex = st.TopIndex;
    delete[] Data;
    Data = new T[Num];
    for (int32_t i = 0; i < TopIndex + 1; i++) {
      Data[i] = st.Data[i];
    }
  }
  ~TStack() {
    delete[] Data;
  }

  TStack& operator=(const TStack &st) {
    if(this == &st) {
      return *this;
    }

    Num = st.Num;
    TopIndex = st.TopIndex;
    delete[] Data;
    Data = new T[Num];

    for (int32_t i = 0; i < TopIndex + 1; i++) {
      Data[i] = st.Data[i];
    }

    return *this;
  }
  bool IsEmpty() const {
    return TopIndex == -1;
  }
  bool IsFull() const {
    return TopIndex == Num - 1;
  }
  void Push(const T& elem) {
    if (IsFull()) {
      T *tmp = Data;
      Data = new T[Num + 10];
      for (int32_t i = 0; i < Num; i++) {
        Data[i] = tmp[i];
      }
      Num += 10;
      delete[] tmp;
    }
    Data[++TopIndex] = elem;
  }
  T Pop() {
    assert(!IsEmpty());
    return Data[TopIndex--];
  }
  T Top() const {
    assert(!IsEmpty());
    return Data[TopIndex];
  }
  void Print() const {
    std::cout << "Stack: ";
    if (IsEmpty()) {
      std::cout << "Is empty!";
    }
    for (int32_t i = 0; i < TopIndex+1; i++) {
      std::cout << Data[i] << ' ';
    }
  }

  void Clear() {
    while (!IsEmpty()) {
      Pop();
    }
  }
};
