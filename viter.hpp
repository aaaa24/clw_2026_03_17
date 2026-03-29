#ifndef VITER_HPP
#define VITER_HPP

#include <cstddef>

namespace topit {
  template< class T >
  struct Vector;

  template< class T >
  struct VIter {
    VIter();
    explicit VIter(T * ptr);
    T & operator*() const;
    T * operator->() const;
    T & operator[](std::ptrdiff_t n) const;
    VIter< T > & operator++();
    VIter< T > operator++(int);
    VIter< T > & operator--();
    VIter< T > operator--(int);
    VIter< T > operator+(std::ptrdiff_t n) const;
    VIter< T > operator-(std::ptrdiff_t n) const;
    std::ptrdiff_t operator-(const VIter< T > & other);
    bool operator==(const VIter< T > & other) const noexcept;
    bool operator!=(const VIter< T > & other) const noexcept;
    bool operator<(const VIter< T > & other) const noexcept;
    bool operator>(const VIter< T > & other) const noexcept;
    bool operator<=(const VIter< T > & other) const noexcept;
    bool operator>=(const VIter< T > & other) const noexcept;
  private:
    friend struct Vector< T >;
    T * ptr_;
  };
}

template< class T >
topit::VIter< T >::VIter():
  ptr_(nullptr)
{}

template< class T >
topit::VIter< T >::VIter(T * ptr):
  ptr_(ptr)
{}

template< class T >
T & topit::VIter< T >::operator*() const
{
  return *ptr_;
}

template< class T >
T * topit::VIter< T >::operator->() const
{
  return ptr_;
}

template< class T >
T & topit::VIter< T >::operator[](std::ptrdiff_t n) const
{
  return ptr_[n];
}

#endif
