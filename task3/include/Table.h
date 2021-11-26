#pragma once
#include <cassert>
#include <exception>

template<class Key, class Value>
class TableEntry{
 private:
  Key key;
 public:
  Value value;
  TableEntry() = default;
  TableEntry(Key key, Value value) : key(key), value(value) {}
  Key GetKey() const {
    return key;
  }
  bool operator==(const TableEntry &rhs) const {
    return std::tie(key, value) == std::tie(rhs.key, rhs.value);
  }
  bool operator!=(const TableEntry &rhs) const {
    return rhs != *this;
  }
};

template<class Key, class Value>
class Table {
  //using TableEntry = TableEntry<Key, Value>;
 private:
  TableEntry<Key, Value> *Pointer = nullptr;
  size_t Size;
  size_t MemSize;

  void Reallocate(size_t size) {
    auto *buf = new TableEntry<Key, Value>[size];
    for (size_t i = 0; i < size && i < Size; i++) {
      buf[i] = Pointer[i];
    }
    delete[] Pointer;
    Pointer = buf;
    MemSize = size;
  }
 public:
  explicit Table(size_t memSize) : MemSize(memSize), Size(0) {
    assert(memSize > 0);
    Pointer = new TableEntry<Key, Value>[memSize];
  }
  Table(const Table<Key, Value> &t) {
    delete[] Pointer;
    Size = t.Size;
    MemSize = t.MemSize;
    Pointer = new TableEntry<Key, Value>[MemSize];

    for (size_t i = 0; i < Size; i++) {
      Pointer[i] = t.Pointer[i];
    }
  }

  Table<Key, Value> &operator=(const Table<Key, Value> &t) {
    if (this == &t) {
      return *this;
    }

    delete[] Pointer;
    Size = t.Size;
    MemSize = t.MemSize;
    Pointer = new TableEntry<Key, Value>[MemSize];

    for (size_t i = 0; i < Size; i++) {
      Pointer[i] = t.Pointer[i];
    }

    return *this;
  }

  ~Table() {
    delete[] Pointer;
  }

  [[nodiscard]] bool IsEmpty() const {
    return Size == 0;
  }

  [[nodiscard]] bool HasKey(Key key) const {
    for (size_t i = 0; i < Size; i++) {
      if (Pointer[i].GetKey() == key) {
        return true;
      }
    }
    return false;
  }

  void Add(Key key, Value value) {
    if (HasKey(key)){
      return;
    }

    if (Size == MemSize) {
      Reallocate(Size + 10);
    }
    Pointer[Size++] = TableEntry(key, value);
  }

  const Value& operator[](const Key &k) const {
    for (size_t i = 0; i < Size; i++) {
      if (Pointer[i].GetKey() == k) {
        return Pointer[i].Value;
      }
    }

    throw std::exception("Unknown key");
  }

  Value& operator[](const Key &k) {
    for (size_t i = 0; i < Size; i++) {
      if (Pointer[i].GetKey() == k) {
        return Pointer[i].value;
      }
    }

    throw std::exception("Unknown key");
  }
};