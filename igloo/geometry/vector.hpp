#pragma once

#include <igloo/utility/math_vector.hpp>

namespace igloo
{


/*! A vector represents a direction in 3-space.
 */
class vector : public math_vector_facade<vector, float, 3>
{
  private:
    typedef math_vector_facade<vector, float, 3> super_t;

  public:
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
      return igloo::cross(*this, rhs);
    } // end cross()

    float x, y, z;
}; // end vector


} // end igloo

