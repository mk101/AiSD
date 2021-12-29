#pragma once
#include <algorithm>
#include <cassert>
#include <exception>
#include <iterator>

template<class T>
class List {
 private:

  template<class U>
  struct Node {
   public:
    U data;
    Node<U> *next;

    Node(U data, Node<U> *next) : data(data), next(next) {}
    explicit Node(U data) : data(data), next(nullptr) {}
    Node(const Node<U> &n) {
      data = n.data;
      next = nullptr;
      if (n.next != nullptr) {
        next = new Node<U>(*(n.next));
      }
    }

    Node<U> &operator=(const Node<U> &n) {
      if (this == &n) {
        return *this;
      }

      data = n.data;

      List::deleteNext(next);

      if (n.next != nullptr) {
        next = new Node<U>(*(n.next));
      }

      return *this;
    }
  };

  Node<T> *head;
  size_t size;

  static void deleteNext(Node<T> *ptr) {
    if (ptr != nullptr) {
      deleteNext(ptr->next);
      delete ptr;
    }
  }

  Node<T> *findPrev(Node<T> *cur) const {
    assert(cur != head);
    auto ptr = head;

    while (ptr->next != cur) {
      ptr = ptr->next;
    }

    return ptr;
  }
 public:
  List() : head(nullptr), size(0) {}
  List(const List<T> &l) {
    size = l.size;
    head = new Node<T>(*(l.head));
  }
  List<T> &operator=(const List<T> &l) {
    if (this == &l) {
      return *this;
    }

    size = l.size;
    deleteNext(head);
    head = new Node<T>(*(l.head));

    return *this;
  }

  ~List() {
    deleteNext(head);
  }
  void insert(const T &data, size_t index) {
    assert(size >= index);
    if (head == nullptr) {
      head = new Node<T>(data);
      size = 1;
      return;
    }

    auto ptr = head;
    for (size_t i = 1; i < index; i++) {
      ptr = ptr->next;
    }

    ptr->next = new Node<T>(data);
    size++;
  }

  void insert(const T &data) {
    insert(data, size);
  }

  void remove(const T &data) {
    auto ptr = head;

    if (head->data == data) {
      head = head->next;
      size--;
      delete ptr;
      return;
    }

    while (ptr != nullptr) {
      if (ptr->data == data) {
        auto prev = findPrev(ptr);
        prev->next = ptr->next;
        size--;
        delete ptr;
        return;
      }

      ptr = ptr->next;
    }
  }

  void removeAt(size_t index) {
    assert(size > index);

    auto ptr = head;
    if (index == 0) {
      head = head->next;
      delete ptr;
      size--;
      return;
    }

    for (size_t i = 0; i < index; i++) {
      ptr = ptr->next;
    }

    auto prev = findPrev(ptr);
    prev->next = ptr->next;
    delete ptr;
    size--;
  }

  [[nodiscard]] size_t getSize() const {
    return size;
  }

  const T& operator[](size_t index) const {
    assert(size > index);

    auto ptr = head;
    for (size_t i = 0; i < index; i++) {
      ptr = ptr->next;
    }

    return ptr->data;
  }

  T& operator[](size_t index) {
    assert(size > index);

    auto ptr = head;
    for (size_t i = 0; i < index; i++) {
      ptr = ptr->next;
    }

    return ptr->data;
  }

  struct Iterator {
    using iteratorCategory = std::forward_iterator_tag;
    using differenceType   = std::ptrdiff_t;

   public:
    explicit Iterator(Node<T> *ptr) : ptr(ptr) {}

    T &operator*() const {
      return ptr->data;
    }
    T *operator->() {
      return &(ptr->data);
    }
    Iterator &operator++() {
      ptr = ptr->next;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator== (const Iterator &a, const Iterator &b) {
      return a.ptr == b.ptr;
    }
    friend bool operator!= (const Iterator &a, const Iterator &b) {
      return a.ptr != b.ptr;
    }

   private:
    Node<T> *ptr;
  };
  struct ConstIterator {
    using iteratorCategory = std::forward_iterator_tag;
    using differenceType   = std::ptrdiff_t;

   public:
    explicit ConstIterator(Node<T> *ptr) : ptr(ptr) {}

    const T &operator*() const {
      return ptr->data;
    }
    const T *operator->() const {
      return &(ptr->data);
    }
    ConstIterator &operator++() {
      ptr = ptr->next;
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator== (const ConstIterator &a, const ConstIterator &b) {
      return a.ptr == b.ptr;
    }
    friend bool operator!= (const ConstIterator &a, const ConstIterator &b) {
      return a.ptr != b.ptr;
    }

   private:
    Node<T> *ptr;
  };

  Iterator begin() {
    return Iterator(head);
  }

  Iterator end() {
    return Iterator(nullptr);
  }

  ConstIterator begin() const {
    return ConstIterator(head);
  }

  ConstIterator end() const {
    return ConstIterator(nullptr);
  }
};
