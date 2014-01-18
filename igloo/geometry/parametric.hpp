#pragma once

#include <igloo/utility/math_vector.hpp>

namespace igloo
{


/*! A parametric represents parametric coordinates in the plane.
 */
class parametric : float2
{
  private:
    typedef float2 super_t;

  public:
    /*! Creates a new default constructed parametric.
     */
    inline parametric() : super_t() {}

    /*! Creates a new point.
     *  \param x The x coordinate of the parametric coordinates.
     *  \param y The y coordinate of the parametric coordinates.
     */
    inline parametric(float x, float y) : super_t(x,y) {}

    using super_t::operator[];
    using super_t::operator float *;
    using super_t::operator const float *;

    using super_t::x;
    using super_t::y;
}; // end parametric


} // end igloo

