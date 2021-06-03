#pragma once
#include <iostream>

template<class T>
class Allocator
{
public:
    Allocator() {}
    ~Allocator() {}

    template<class... Args>
    void construct(T* p, Args&&... args);
    T* allocate(size_t maxSize);
    void deallocate(T* ptr, size_t count);
    void destroy(T* ptr);
};

template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T>
{
    T* ptr_;
public:
    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
    explicit Iterator(T* ptr): ptr_(ptr) {}
    bool operator == (const Iterator<T> &right) const;
    bool operator != (const Iterator<T> &right) const;
    T& operator *() const;
    Iterator operator++();
    Iterator operator --();
    Iterator operator +(difference_type n) const;
    Iterator operator -(difference_type n) const;
    Iterator& operator +=(difference_type n);
    Iterator& operator -=(difference_type n);

    Iterator &operator[](int n);

    friend Iterator operator+(difference_type left, const Iterator &right){
        return Iterator(left + right.ptr_);
    }
    friend Iterator operator-(difference_type left, const Iterator &right){
        return Iterator(left - right.ptr_);
    }
};

//Из поддерживаемых методов достаточно
//emplace_back
template<class T>
class MyVector
{
    Allocator<T> alloc_;
    T* data_;
    size_t size_;
    size_t capacity_;
public:
    explicit MyVector(size_t n = 0);
    ~MyVector();
    void push_back(const T& elem);
    T pop_back();
    template <typename... Args>
    void emplace_back(Args&&... args);
    Iterator<T> begin() const;
    Iterator<T> end() const;
    std::reverse_iterator<Iterator<T>> rbegin() const;
    std::reverse_iterator<Iterator<T>> rend() const;
    T& operator [](size_t index);
    void resize(size_t new_size);
    void reserve(size_t new_size);
    size_t size() const;
    size_t capacity() const;
    void clear();
    bool empty() const;
};

#include "vector.tpp"