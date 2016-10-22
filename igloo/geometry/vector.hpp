#pragma once

#include <igloo/utility/math_vector.hpp>
#include <utility>

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


inline std::pair<vector,vector> basis(const vector& v1)
{
  // see PBRT v2 p63

  vector v2;

  if(std::fabs(v1.x) > std::fabs(v1.y))
  {
    float inv_length = 1.f / std::sqrt(v1.x*v1.x + v1.z*v1.z);

    v2 = vector(-v1.z * inv_length, 0, v1.x * inv_length);
  }
  else
  {
    float inv_length = 1.f / std::sqrt(v1.y*v1.y + v1.z*v1.z);

    v2 = vector(0, v1.z * inv_length, -v1.y * inv_length);
  }

  vector v3 = v1.cross(v2);

  return std::make_pair(v2,v3);
}


inline std::tuple<vector,vector,vector> orthonormal_basis(const vector& v)
{
  vector v1 = v.normalize();

  auto v2_and_v3 = basis(v1);

  return std::make_tuple(v1, std::get<0>(v2_and_v3), std::get<1>(v2_and_v3));
}




} // end igloo

