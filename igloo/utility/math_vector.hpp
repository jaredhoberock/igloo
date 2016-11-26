#pragma once

#include <type_traits>
#include <numeric>
#include <cmath>
#include <functional>
#include <iostream>
#include <tuple>

namespace igloo
{


template<typename Derived, typename T, std::size_t N>
  class math_vector_facade
{
  public:
    typedef T                  value_type;
    typedef value_type &       reference;
    typedef const value_type & const_reference;
    typedef std::size_t        size_type;
    static const std::size_t   static_size = N;

    typedef T*       iterator;
    typedef const T* const_iterator;

    constexpr math_vector_facade(){}

    math_vector_facade(const math_vector_facade &other)
    {
      for(size_type i = 0; i != static_size; ++i)
      {
        (*this)[i] = other[i];
      }
    }

    template<typename OtherVector>
    math_vector_facade(const OtherVector &other,
                       typename std::enable_if<
                         !std::is_arithmetic<OtherVector>::value
                       >::type * = 0)
    {
      for(size_type i = 0; i != static_size; ++i)
      {
        (*this)[i] = other[i];
      }
    }

    Derived &operator=(const math_vector_facade &other)
    {
      for(size_type i = 0; i != static_size; ++i)
      {
        (*this)[i] = other[i];
      }

      return derived();
    }

    template<typename OtherVector>
    Derived &operator=(const OtherVector &other)
    {
      for(size_type i = 0; i != static_size; ++i)
      {
        (*this)[i] = other[i];
      }

      return derived();
    }

    template<typename Number>
    explicit math_vector_facade(Number v,
                                typename std::enable_if<
                                  std::is_arithmetic<Number>::value
                                >::type * = 0)
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

    inline Derived abs() const
    {
      Derived result = *this;

      for(size_type i = 0; i < static_size; ++i)
      {
        result[i] = std::abs(result[i]);
      }

      return result;
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
Derived operator+(const math_vector_facade<Derived,T,N> &a,
                  const math_vector_facade<Derived,T,N> &b)
{
  Derived result = a;
  result += b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator-(const math_vector_facade<Derived,T,N> &a,
                  const math_vector_facade<Derived,T,N> &b)
{
  Derived result = a;
  result -= b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator*(const math_vector_facade<Derived,T,N> &a, T b)
{
  Derived result = a;
  result *= b;
  return result;
}

template<typename Derived, typename T, std::size_t N>
Derived operator*(T a, const math_vector_facade<Derived,T,N> &b)
{
  Derived result = b;
  result *= a;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator*(const math_vector_facade<Derived,T,N> &a,
                  const math_vector_facade<Derived,T,N> &b)
{
  Derived result = a;
  result *= b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator/(const math_vector_facade<Derived,T,N> &a, T b)
{
  Derived result = a;
  result /= b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
Derived operator/(const math_vector_facade<Derived,T,N> &a,
                  const math_vector_facade<Derived,T,N> &b)
{
  Derived result = a;
  result /= b;
  return result;
}


template<typename Derived, typename T, std::size_t N>
T dot(const math_vector_facade<Derived,T,N> &a,
      const math_vector_facade<Derived,T,N> &b)
{
  return a.dot(b);
} // end dot()


template<typename Derived, typename T, std::size_t N>
T abs_dot(const math_vector_facade<Derived,T,N> &a,
          const math_vector_facade<Derived,T,N> &b)
{
  return a.abs_dot(b);
} // end dot()


template<typename Derived, typename T, std::size_t N>
T norm(const math_vector_facade<Derived,T,N> &vec)
{
  return vec.norm();
}


template<typename Derived, typename T, std::size_t N>
T norm2(const math_vector_facade<Derived,T,N> &vec)
{
  return vec.norm2();
}


template<typename Derived, typename T, std::size_t N>
T sum(const math_vector_facade<Derived,T,N> &vec)
{
  return vec.sum();
}


template<typename Derived, typename T, std::size_t N>
T product(const math_vector_facade<Derived,T,N> &vec)
{
  return vec.product();
}


template<typename Derived, typename T, std::size_t N>
inline Derived normalize(const math_vector_facade<Derived,T,N> &vec)
{
  return vec.normalize();
}


template<typename Derived, typename T, std::size_t N>
inline Derived reflect(const math_vector_facade<Derived,T,N> &a,
                       const math_vector_facade<Derived,T,N> &b)
{
  return a.reflect(b);
}


template<typename Derived, typename T>
inline Derived cross(const math_vector_facade<Derived,T,3> &lhs,
                     const math_vector_facade<Derived,T,3> &rhs)
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
std::ostream &operator<<(std::ostream &os, const math_vector_facade<Derived,T,N> &v)
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
std::istream &operator>>(std::istream &is, const math_vector_facade<Derived,T,N> &v)
{
  for(size_t i = 0; i < N; ++i)
  {
    is >> v[i];
  } // end for i

  return is;
} // end operator<<()


template<typename T, std::size_t N> class math_vector;


template<typename T>
class math_vector<T,2> : public math_vector_facade<math_vector<T,2>, T, 2>
{
  private:
    typedef math_vector_facade<math_vector<T,2>, T, 2> super_t;

  public:
    typedef typename super_t::value_type value_type;

    inline math_vector() : super_t() {}

    template<typename OtherVector>
    inline math_vector(const OtherVector &other) : super_t(other) {}

    inline math_vector(value_type v) : super_t(v) {}

    inline math_vector(value_type xx, value_type yy)
      : super_t(),
        x(xx),
        y(yy)
    {}

    T x, y;
}; // end math_vector<T,2>


template<typename T>
class math_vector<T,3> : public math_vector_facade<math_vector<T,3>, T, 3>
{
  private:
    typedef math_vector_facade<math_vector<T,3>, T, 3> super_t;

  public:
    typedef typename super_t::value_type value_type;

    inline math_vector() : super_t() {}

    template<typename OtherVector>
    inline math_vector(const OtherVector &other) : super_t(other) {}

    inline math_vector(value_type v) : super_t(v) {}

    inline math_vector(value_type xx, value_type yy, value_type zz)
      : super_t(),
        x(xx),
        y(yy),
        z(zz)
    {}

    inline math_vector cross(const math_vector &rhs) const
    {
      return igloo::cross(*this, rhs);
    } // end cross()

    T x, y, z;
}; // end math_vector<T,3>


template<typename T>
class math_vector<T,4> : public math_vector_facade<math_vector<T,4>, T, 4>
{
  private:
    typedef math_vector_facade<math_vector<T,4>, T, 4> super_t;

  public:
    typedef typename super_t::value_type value_type;

    inline math_vector() : super_t() {}

    template<typename OtherVector>
    inline math_vector(const OtherVector &other) : super_t(other) {}

    inline math_vector(value_type v) : super_t(v) {}

    inline math_vector(value_type xx, value_type yy, value_type zz, value_type ww)
      : super_t(),
        x(xx),
        y(yy),
        z(zz),
        w(ww)
    {}

    T x, y, z, w;
}; // end math_vector<T,3>


typedef math_vector<unsigned int,2> uint2;
typedef math_vector<unsigned int,3> uint3;

typedef math_vector<float,2> float2;
typedef math_vector<float,3> float3;
typedef math_vector<float,4> float4;


} // end igloo


namespace std
{


template<std::size_t I, typename T, std::size_t N>
struct tuple_element<I, igloo::math_vector<T,N>>
{
  using type = T;
};

template<std::size_t I, typename T, std::size_t N>
typename std::tuple_element<I, igloo::math_vector<T,N>>::type&
get(igloo::math_vector<T,N>& vec)
{
  return vec[I];
}

template<std::size_t I, typename T, std::size_t N>
const typename std::tuple_element<I, igloo::math_vector<T,N>>::type&
get(const igloo::math_vector<T,N>& vec)
{
  return vec[I];
}


template<std::size_t I, typename T, std::size_t N>
typename std::tuple_element<I, igloo::math_vector<T,N>>::type&&
get(igloo::math_vector<T,N>&& vec)
{
  return vec[I];
}


} // end std

