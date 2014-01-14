#pragma once

#include <cstddef>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

namespace igloo
{
namespace detail
{


template<typename Derived, typename T, std::size_t N>
  class vector_base
{
  public:
    typedef T                  value_type;
    typedef value_type &       reference;
    typedef const value_type & const_reference;
    typedef std::size_t        size_type;
    static const std::size_t   static_size = N;

    typedef T*       iterator;
    typedef const T* const_iterator;

    vector_base(){}

    vector_base(const vector_base &other)
    {
      for(size_type i = 0; i != static_size; ++i)
      {
        (*this)[i] = other[i];
      }
    }

    template<typename OtherVector>
    inline vector_base(const OtherVector &other)
    {
      for(size_type i = 0; i != static_size; ++i)
      {
        (*this)[i] = other[i];
      }
    }

    Derived &operator=(const vector_base &other)
    {
      for(size_type i = 0; i != static_size; ++i)
      {
        (*this)[i] = other[i];
      }
    }

    template<typename OtherVector>
    Derived &operator=(const OtherVector &other)
    {
      for(size_type i = 0; i != static_size; ++i)
      {
        (*this)[i] = other[i];
      }
    }

    inline vector_base(value_type v)
    {
      std::fill(begin(), end(), v);
    }

    size_type size() const
    {
      return static_size;
    }

    iterator begin()
    {
      return reinterpret_cast<iterator>(this);
    }

    iterator end()
    {
      return begin() + size();
    }

    const_iterator begin() const
    {
      return reinterpret_cast<const_iterator>(this);
    }

    const_iterator end() const
    {
      return begin() + size();
    }

    inline operator value_type * ()
    {
      return begin();
    }

    inline operator const value_type * () const
    {
      return begin();
    }

    inline reference operator[](size_type i)
    {
      return begin()[i];
    }

    inline const_reference operator[](size_type i) const
    {
      return begin()[i];
    }

    template<size_type i>
    inline reference get()
    {
      return operator[](i);
    }

    template<size_type i>
    inline const_reference get() const
    {
      return operator[](i);
    }

    inline Derived operator+() const
    {
      return *this;
    }

    inline Derived operator-() const
    {
      Derived result;
      for(size_type i = 0; i < static_size; ++i)
      {
        result[i] = -(*this)[i];
      }
      
      return result;
    }

    inline Derived &operator+=(const Derived &other)
    {
      for(size_type i = 0; i < static_size; ++i)
      {
        (*this)[i] += other[i];
      }

      return derived();
    }

    inline Derived &operator-=(const Derived &other)
    {
      for(size_type i = 0; i < static_size; ++i)
      {
        (*this)[i] -= other[i];
      }

      return derived();
    }

    inline Derived &operator*=(value_type v)
    {
      for(size_type i = 0; i < static_size; ++i)
      {
        (*this)[i] *= v;
      }

      return derived();
    }

    inline Derived &operator*=(const Derived &other)
    {
      for(size_type i = 0; i < static_size; ++i)
      {
        (*this)[i] *= other[i];
      }

      return derived();
    }

    inline Derived &operator/=(value_type v)
    {
      for(size_type i = 0; i < static_size; ++i)
      {
        (*this)[i] /= v;
      }

      return derived();
    }

    inline Derived &operator/=(const Derived &other)
    {
      for(size_type i = 0; i < static_size; ++i)
      {
        (*this)[i] /= other[i];
      }

      return derived();
    }

    inline value_type dot(const Derived &other) const
    {
      return std::inner_product(begin(), end(), other.begin(), value_type(0)); 
    }

    inline value_type abs_dot(const Derived &other) const
    {
      // XXX fabs returns float, there ought to be a generic way to accomplish this
      return std::fabs(dot(other));
    }

    inline value_type norm() const
    {
      return std::sqrt(norm2());
    }

    inline value_type norm2() const
    {
      return dot(*this);
    }

    inline value_type sum() const
    {
      return std::accumulate(begin(), end(), value_type(0));
    }

    inline value_type product() const
    {
      return std::accumulate(begin(), end(), value_type(0), std::multiplies<value_type>());
    }

    inline Derived normalize() const
    {
      return (*this) / norm();
    }

    // XXX add map & reduce?

    inline Derived reflect(const Derived &v) const
    {
      return value_type(2) * dot(v) * (*this) - v;
    }

  private:
    inline Derived &derived()
    {
      return static_cast<Derived&>(*this);
    }

    inline const Derived &derived() const
    {
      return static_cast<const Derived&>(*this);
    }
};


template<typename Derived, typename T, std::size_t N>
Derived operator+(const vector_base<Derived,T,N> &a,
                  const vector_base<Derived,T,N> &b)
{
  Derived result = a;
  result += b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator-(const vector_base<Derived,T,N> &a,
                  const vector_base<Derived,T,N> &b)
{
  Derived result = a;
  result -= b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator*(const vector_base<Derived,T,N> &a, T b)
{
  Derived result = a;
  result *= b;
  return result;
}

template<typename Derived, typename T, std::size_t N>
Derived operator*(T a, const vector_base<Derived,T,N> &b)
{
  Derived result = b;
  result *= a;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator*(const vector_base<Derived,T,N> &a,
                  const vector_base<Derived,T,N> &b)
{
  Derived result = a;
  result *= b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator/(const vector_base<Derived,T,N> &a, T b)
{
  Derived result = a;
  result /= b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator/(const vector_base<Derived,T,N> &a,
                  const vector_base<Derived,T,N> &b)
{
  Derived result = a;
  result /= b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
T dot(const vector_base<Derived,T,N> &a,
      const vector_base<Derived,T,N> &b)
{
  return a.dot(b);
} // end dot()


template<typename Derived, typename T, std::size_t N>
T abs_dot(const vector_base<Derived,T,N> &a,
          const vector_base<Derived,T,N> &b)
{
  return a.abs_dot(b);
} // end dot()


template<typename Derived, typename T, std::size_t N>
T norm(const vector_base<Derived,T,N> &vec)
{
  return vec.norm();
}


template<typename Derived, typename T, std::size_t N>
T norm2(const vector_base<Derived,T,N> &vec)
{
  return vec.norm2();
}


template<typename Derived, typename T, std::size_t N>
T sum(const vector_base<Derived,T,N> &vec)
{
  return vec.sum();
}


template<typename Derived, typename T, std::size_t N>
T product(const vector_base<Derived,T,N> &vec)
{
  return vec.product();
}


template<typename Derived, typename T, std::size_t N>
inline Derived normalize(const vector_base<Derived,T,N> &vec)
{
  return vec.normalize();
}


template<typename Derived, typename T, std::size_t N>
inline Derived reflect(const vector_base<Derived,T,N> &a,
                       const vector_base<Derived,T,N> &b)
{
  return a.reflect(b);
}


template<typename Derived, typename T>
inline Derived cross(const vector_base<Derived,T,3> &lhs,
                     const vector_base<Derived,T,3> &rhs)
{
  Derived result;
  
  Derived subtract_me(lhs[2]*rhs[1], lhs[0]*rhs[2], lhs[1]*rhs[0]);
  
  result[0] = (lhs[1] * rhs[2]);
  result[0] -= subtract_me[0];
  result[1]= (lhs[2] * rhs[0]);
  result[1]-= subtract_me[1];
  result[2] = (lhs[0] * rhs[1]);
  result[2] -= subtract_me[2];
  
  return result;
} // end cross()


template<typename Derived, typename T, std::size_t N>
std::ostream &operator<<(std::ostream &os, const vector_base<Derived,T,N> &v)
{
  size_t i = 0;
  for(; i < N - 1; ++i)
  {
    os << v[i] << " ";
  }

  os << v[i];

  return os;
} // end operator<<()


template<typename Derived, typename T, std::size_t N>
std::istream &operator>>(std::istream &is, const vector_base<Derived,T,N> &v)
{
  for(size_t i = 0; i < N; ++i)
  {
    is >> v[i];
  } // end for i

  return is;
} // end operator<<()


} // end detail
} // end igloo

