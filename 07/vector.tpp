#include "vector.hpp"

template<class T>
T* Allocator<T>::allocate(size_t count){
    return static_cast<T *>(operator new[](count * sizeof(T)));
}

template<class T>
void Allocator<T>::deallocate(T* ptr, size_t count){
    operator delete[](ptr, count * sizeof(T));
}

template<class T>
template<class... Args>
void Allocator<T>::construct(T* p, Args&&... args) {
    p = new(p) T(std::forward<Args>(args)...);
}

template<class T>
void Allocator<T>::destroy(T* ptr){
    ptr->~T();
}

template <class T>
bool Iterator<T>::operator == (const Iterator<T> &right) const{
    return ptr_ == right.ptr_;
}

template <class T>
bool Iterator<T>::operator != (const Iterator<T> &right) const{
    return !(ptr_ == right.ptr_);
}

template <class T>
T& Iterator<T>::operator *() const{
    return *ptr_;
}

template <class T>
Iterator<T> Iterator<T>::operator++(){
    ptr_++;
    return *this;
}
template <class T>
Iterator<T> Iterator<T>::operator --(){
    ptr_--;
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator+=(Iterator<T>::difference_type n)
{
    ptr_ += n;
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator-=(Iterator<T>::difference_type n)
{
    ptr_ -= n;
    return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator+(Iterator<T>::difference_type n) const
{
    return Iterator<T>(ptr_ + n);
}

template <class T>
Iterator<T> Iterator<T>::operator-(Iterator<T>::difference_type n) const
{
    return Iterator<T>(ptr_ - n);
}

template <class T>
Iterator<T>& Iterator<T>::operator[](int n)
{
    return ptr_[n];
}

template<class T>
MyVector<T>::MyVector(size_t n): size_(n), capacity_(n * 2){
    data_ = alloc_.allocate(capacity_);
    for (size_t i = 0; i < size_; i++){
        alloc_.construct(data_ + i);
    }
}

template<class T>
MyVector<T>::~MyVector() {
    for (size_t i = 0; i < size_; i++)
        alloc_.destroy(data_ + i);
    alloc_.deallocate(data_, capacity_);
}

template<class T>
void MyVector<T>::push_back(const T& elem){
    if (size_ >= capacity_)
        reserve(2 * capacity_ + 1);
    alloc_.construct(data_ + size_, elem);
    size_ += 1;
}

template<class T>
T MyVector<T>::pop_back(){
    T a = data_[size_ - 1];
    if (size_){
        size_ -= 1;
        alloc_.destroy(data_ + size_);
    }
    return a;
}

template<class T>
template <typename... Args>
void MyVector<T>::emplace_back(Args&&... args){
    if (size_ >= capacity_)
        reserve(2 * capacity_ + 1);
    alloc_.construct(data_ + size_, std::forward<Args>(args)...);
    size_ += 1;
}

template<class T>
Iterator<T> MyVector<T>::begin() const {
    return Iterator<T>(data_);
}

template<class T>
Iterator<T> MyVector<T>::end() const {
    return Iterator<T>(data_ + size_ - 1);
}

template<class T>
std::reverse_iterator<Iterator<T>> MyVector<T>::rbegin() const {
    return std::reverse_iterator<Iterator<T>>(Iterator<T>(data_ + size_));
}

template<class T>
std::reverse_iterator<Iterator<T>> MyVector<T>::rend() const {
    return std::reverse_iterator<Iterator<T>>(Iterator<T>(data_ + 1));
}

template<class T>
T& MyVector<T>::operator [](size_t index){
    return data_[index];
}

template<class T>
void MyVector<T>::resize(size_t new_size){
    if (new_size < size_){
        for (size_t i = new_size; i < size_; i++){
            alloc_.destroy(data_ + i);
        }
    }
    else if (new_size > size_){
        reserve(new_size);
        for (size_t i = size_; i < new_size; i++){
            alloc_.construct(data_ + i);
        }
    }
    size_ = new_size;
}

template<class T>
void MyVector<T>::reserve(size_t new_size){
    if (new_size > capacity_){
        T *tmp = alloc_.allocate(new_size);

        for (size_t i = 0; i < size_; i++){
            alloc_.construct(tmp + i, std::move(data_[i]));
            alloc_.destroy(data_ + i);
        }
        alloc_.deallocate(data_, capacity_);
        capacity_ = new_size;
        data_ = tmp;
    }
}

template<class T>
size_t MyVector<T>::size() const{
    return size_;
}

template<class T>
size_t MyVector<T>::capacity() const{
    return capacity_;
}

template<class T>
void MyVector<T>::clear(){
    for (size_t i = 0; i < size_; i++){
        alloc_.destroy(data_ + i);
    }
    size_ = 0;
}

template<class T>
bool MyVector<T>::empty() const{
    return size_ == 0;
}