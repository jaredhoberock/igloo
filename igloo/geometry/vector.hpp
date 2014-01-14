#pragma once

#include <cstddef>

#include <igloo/geometry/detail/vector_base.hpp>

namespace igloo
{


template<typename T, std::size_t> class vector;


template<typename T>
class vector<T,2> : public detail::vector_base<vector<T,2>, T, 2>
{
  private:
    typedef detail::vector_base<vector<T,2>, T, 2> super_t;

  public:
    typedef typename super_t::value_type value_type;

    inline vector() : super_t() {}

    template<typename OtherVector>
    inline vector(const OtherVector &other) : super_t(other) {}

    inline vector(value_type v) : super_t(v) {}

    inline vector(value_type xx, value_type yy)
      : super_t(),
        x(xx),
        y(yy)
    {}

    inline vector cross(const vector &rhs) const
    {
      return detail::cross(*this, rhs);
    } // end cross()

    T x, y;
}; // end vector<T,2>


template<typename T>
class vector<T,3> : public detail::vector_base<vector<T,3>, T, 3>
{
  private:
    typedef detail::vector_base<vector<T,3>, T, 3> super_t;

  public:
    typedef typename super_t::value_type value_type;

    inline vector() : super_t() {}

    template<typename OtherVector>
    inline vector(const OtherVector &other) : super_t(other) {}

    inline vector(value_type v) : super_t(v) {}

    inline vector(value_type xx, value_type yy, value_type zz)
      : super_t(),
        x(xx),
        y(yy),
        z(zz)
    {}

    inline vector cross(const vector &rhs) const
    {
      return detail::cross(*this, rhs);
    } // end cross()

    T x, y, z;
}; // end vector<T,3>


typedef vector<float,2> float2;
typedef vector<float,3> float3;


} // end igloo

