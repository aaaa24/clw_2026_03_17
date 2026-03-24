#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECROT_HPP

#include <cstddef>

namespace topit {
  template< class T >
  struct Vector {
    Vector();
    Vector(const Vector &);
    Vector(Vector &&);
    ~Vector();
    Vector & operator=(const Vector &);
    Vector & operator=(Vector &&);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T & at(size_t pos);
    const T & at(size_t pos) const;
    T & operator[](size_t pos);
    const T & operator[](size_t pos) const;

    void pushBack(const T & val);
    void popBack();
    void insert(size_t i, const T & val);
    void erase(size_t i);

  private:
    T * data_;
    size_t size_, capacity_;
    void extend();
  };
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::~Vector()
{
  delete [] data_;
}

template< class T >
void topit::Vector< T >::extend()
{
  size_t new_capacity = 0;
  if (capacity_ == 0) {
    new_capacity = 1;
  } else {
    new_capacity = 2 * capacity_;
  }
  T * new_data = new T[new_capacity];
  for (size_t i = 0; i < size_; ++i) {
    try {
      new_data[i] = data_[i];
    } catch (...) {
      delete [] new_data;
      throw;
    }
  }
  delete [] data_;
  data_ = new_data;
  capacity_ = new_capacity;
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return size_ == 0;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
T & topit::Vector< T >::at(size_t pos)
{
  return data_[pos];
}

template< class T >
const T & topit::Vector< T >::at(size_t pos) const
{
  return data_[pos];
}

template< class T >
T & topit::Vector< T >::operator[](size_t pos)
{
  return data_[pos];
}

template< class T >
const T & topit::Vector< T >::operator[](size_t pos) const
{
  return data_[pos];
}

template< class T >
void topit::Vector< T >::pushBack(const T & val)
{
  if (size_ == capacity_) {
    extend();
  }
  data_[size_] = val;
  ++size_;
}

template< class T >
void topit::Vector< T >::popBack()
{
  --size_;
}

#endif
