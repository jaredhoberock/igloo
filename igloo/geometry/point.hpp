#pragma once

#include <igloo/geometry/vector.hpp>

namespace igloo
{


/*! A point represents coordinates in 3-space.
 */
class point : float3
{
  private:
    typedef float3 super_t;

  public:
    /*! Creates a new default constructed point.
     */
    inline point() : super_t() {}

    /*! Creates a new point.
     *  \param x The x coordinate of the point.
     *  \param y The y coordinate of the point.
     *  \param z The z coordinate of the point.
     */
    inline point(float x, float y, float z) : super_t(x,y,z) {}

    using super_t::operator[];
    using super_t::operator float *;

    using super_t::x;
    using super_t::y;
    using super_t::z;
}; // end point


} // end igloo

