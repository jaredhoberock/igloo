#pragma once

#include <type_traits>
#include <iterator>
#include <cstddef>
#include <vector>
#include <array>

namespace igloo
{


template<typename T>
  class array_ref
{
  public:
    typedef typename std::remove_const<T>::type      value_type;
    typedef T *                                      pointer;
    typedef T &                                      reference;
    typedef pointer                                  iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::size_t                              size_type;
    typedef std::ptrdiff_t                           difference_type;

    constexpr array_ref() : m_ptr(), m_size(0) {}

    constexpr array_ref(const array_ref &other) : m_ptr(other.m_ptr), m_size(other.m_size) {}

    constexpr array_ref(pointer array, size_type length) : m_ptr(array), m_size(length) {}

    template<typename U>
    constexpr array_ref(std::vector<U> &v,
                        typename std::enable_if<
                          std::is_convertible<decltype(v.data()), pointer>::value
                        >::type * = 0)
      : m_ptr(v.data()), m_size(v.size())
    {}

    template<typename U>
    constexpr array_ref(const std::vector<U> &v,
                        typename std::enable_if<
                          std::is_convertible<decltype(v.data()), pointer>::value
                        >::type * = 0)
      : m_ptr(v.data()), m_size(v.size())
    {}

    template<typename U, std::size_t N>
    constexpr array_ref(U(&a)[N],
                        typename std::enable_if<
                          std::is_convertible<decltype(a), pointer>::value
                        >::type * = 0)
      : m_ptr(a), m_size(N)
    {}

    template<typename U, std::size_t N>
    constexpr array_ref(const U(&a)[N],
                        typename std::enable_if<
                          std::is_convertible<decltype(a), pointer>::value
                        >::type * = 0)
      : m_ptr(a), m_size(N)
    {}

    template<typename U, std::size_t N>
    constexpr array_ref(const std::array<U,N> &a,
                        typename std::enable_if<
                          std::is_convertible<decltype(a.data()), pointer>::value
                        >::type * = 0)
      : m_ptr(a.data()), m_size(N)
    {}

    template<typename U, std::size_t N>
    constexpr array_ref(std::array<U,N> &a,
                        typename std::enable_if<
                          std::is_convertible<decltype(a.data()), pointer>::value
                        >::type * = 0)
      : m_ptr(a.data()), m_size(N)
    {}

    constexpr pointer data() const
    {
      return m_ptr;
    }

    constexpr iterator begin() const
    {
      return data();
    }

    constexpr iterator end() const
    {
      return end() + size();
    }

    reverse_iterator rbegin() const
    {
      return reverse_iterator(end());
    }

    reverse_iterator rend() const
    {
      return rbegin() + size();
    }

    constexpr size_type size() const
    {
      return m_size;
    }

    constexpr bool empty() const
    {
      return m_size != 0;
    }

    constexpr reference operator[](size_type i) const
    {
      return m_ptr[i];
    }

    constexpr reference front() const
    {
      return *m_ptr;
    }

    constexpr reference back() const
    {
      return m_ptr[size() - 1];
    }

    operator std::vector<value_type> () const
    {
      return std::vector<value_type>(begin(),end());
    }

  private:
    pointer   m_ptr;
    size_type m_size;
}; // end array_ref


} // end igloo

