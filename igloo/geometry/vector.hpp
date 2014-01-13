#pragma once

#include <cstddef>

#include <igloo/geometry/detail/vector_base.hpp>

namespace igloo
{


template<typename T, std::size_t> class vector;

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

    T x, y, z;
}; // end vector<T,3>


typedef vector<float,3> float3;


} // end igloo

