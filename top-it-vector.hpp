#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECROT_HPP

#include <cstddef>

namespace topit {
  template< class T >
  struct Vector {
    Vector();
    Vector(const Vector & v);
    Vector(Vector && v) noexcept;
    ~Vector();
    Vector(size_t size, const T & init);
    Vector & operator=(const Vector & v);
    Vector & operator=(Vector && v) noexcept;

    void swap(Vector< T > & v) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T & at(size_t pos);
    const T & at(size_t pos) const;
    T & operator[](size_t pos) noexcept;
    const T & operator[](size_t pos) const noexcept;

    void pushBack(const T & val);
    void popBack();
    void insert(size_t pos, const T & val);
    void insert(size_t pos, const Vector< T > & v, size_t start, size_t end);
    void erase(size_t i);
    void erase(size_t start, size_t end);

  private:
    T * data_;
    size_t size_, capacity_;

    explicit Vector(size_t size);
    void extend();
  };

  template< class T >
  bool operator==(const Vector< T > & lhs, const Vector< T > & rhs);
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::Vector(const Vector< T > & v):
  Vector(v.getSize())
{
  for (size_t i = 0; i < v.getSize(); ++i) {
    data_[i] = v[i];
  }
}

template< class T >
topit::Vector< T >::Vector(Vector< T > && v) noexcept:
  data_(v.data_),
  size_(v.size_),
  capacity_(v.capacity_)
{
  v.data_ = nullptr;
}

template< class T >
topit::Vector< T >::~Vector()
{
  delete [] data_;
}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
topit::Vector< T >::Vector(size_t size, const T & init):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = init;
  }
}

template< class T >
topit::Vector< T > & topit::Vector< T >::operator=(const Vector< T > & v)
{
  if (this == std::addressof(v)) {
    return *this;
  }
  Vector< T > cpy = v;
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T > & topit::Vector< T >::operator=(Vector< T > && v) noexcept
{
  if (this == std::addressof(v)) {
    return *this;
  }
  Vector< T > cpy = std::move(v);
  swap(cpy);
  return *this;
}

template< class T >
void topit::Vector< T >::swap(Vector< T > & v) noexcept
{
  std::swap(data_, v.data_);
  std::swap(size_, v.size_);
  std::swap(capacity_, v.capacity_);
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
  const Vector< T > * cthis = this;
  return const_cast< T & >(cthis->at(pos));
}

template< class T >
const T & topit::Vector< T >::at(size_t pos) const
{
  if (pos >= size_) {
    throw std::out_of_range("Out of array's size");
  }
  return data_[pos];
}

template< class T >
T & topit::Vector< T >::operator[](size_t pos) noexcept
{
  return data_[pos];
}

template< class T >
const T & topit::Vector< T >::operator[](size_t pos) const noexcept
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

template< class T >
void topit::Vector< T >::insert(size_t pos, const T & val)
{
  if (pos > size_) {
    throw std::out_of_range("Out of array's size");
  }
  Vector< T > cpy = *this;
  if (cpy.size_ == cpy.capacity_) {
    cpy.extend();
  }
  for (size_t i = cpy.size_; i > pos; --i) {
    cpy.data_[i] = cpy.data_[i - 1];
  }
  cpy.data_[pos] = val;
  ++cpy.size_;
  swap(cpy);
}

template< class T >
void topit::Vector< T >::insert(size_t pos, const Vector< T > & v, size_t start, size_t end)
{
  if (pos > size_) {
    throw std::out_of_range("Out of array's size");
  }
  if (end <= start || v.getSize() < end) {
    throw std::out_of_range("Incorrect start or end");
  }
  size_t insert_size = end - start;
  Vector< T > cpy(size_ + insert_size);

  for (size_t i = 0; i < pos; ++i) {
    cpy[i] = data_[i];
  }

  for (size_t i = 0; i < insert_size; ++i) {
    cpy[pos + i] = v.data_[start + i];
  }

  for (size_t i = 0; i < size_ - pos; ++i) {
    cpy[pos + insert_size + i] = data_[pos + i];
  }

  swap(cpy);
}

template< class T >
void topit::Vector< T >::erase(size_t i)
{
    if (i >= size_) {
        throw std::out_of_range("Out of array's size");
    }

    Vector< T > cpy(size_ - 1);

    for (size_t j = 0; j < i; ++j) {
        cpy[j] = data_[j];
    }

    for (size_t j = i + 1; j < size_; ++j) {
        cpy[j - 1] = data_[j];
    }

    swap(cpy);
}

template< class T >
void topit::Vector< T >::erase(size_t start, size_t end)
{
    if (start > size_ || end > size_ || start >= end) {
        throw std::out_of_range("Invalid erase range");
    }
    size_t remove_count = end - start;
    size_t new_size = size_ - remove_count;
    Vector< T > cpy(new_size);

    for (size_t j = 0; j < start; ++j) {
        cpy[j] = data_[j];
    }

    for (size_t j = end; j < size_; ++j) {
        cpy[j - remove_count] = data_[j];
    }

    swap(cpy);
}

template< class T >
bool topit::operator==(const Vector< T > & lhs, const Vector< T > & rhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; i < lhs.getSize() && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}

#endif
