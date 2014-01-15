#pragma once

#include <igloo/geometry/vector.hpp>

namespace igloo
{


/*! A normal represents a normal vector in 3-space.
 */
class normal : float3
{
  private:
    typedef float3 super_t;

  public:
    /*! Creates a new default constructed normal.
     */
    inline normal() : super_t() {}

    /*! Creates a new normal from a float3.
     *  \param v The float3 to copy.
     */
    inline normal(const float3 &v) : super_t(v) {}

    /*! Creates a new normal.
     *  \param x The x coordinate of the normal.
     *  \param y The y coordinate of the normal.
     *  \param z The z coordinate of the normal.
     */
    inline normal(float x, float y, float z) : super_t(x,y,z) {}

    using super_t::operator[];
    using super_t::operator float *;
    using super_t::operator const float *;

    using super_t::x;
    using super_t::y;
    using super_t::z;
}; // end normal


} // end igloo

