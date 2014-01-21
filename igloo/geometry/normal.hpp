#pragma once

#include <igloo/geometry/vector.hpp>

namespace igloo
{


/*! A normal represents a normal vector in 3-space.
 */
class normal : vector
{
  private:
    typedef vector super_t;

  public:
    /*! Creates a new default constructed normal.
     */
    inline normal() : super_t() {}

    /*! Creates a new normal from a float3.
     *  \param v The float3 to copy.
     */
    inline normal(const vector &v) : super_t(v) {}

    /*! Creates a new normal.
     *  \param x The x coordinate of the normal.
     *  \param y The y coordinate of the normal.
     *  \param z The z coordinate of the normal.
     */
    inline normal(float x, float y, float z) : super_t(x,y,z) {}

    /*! normal difference.
     *  \param rhs The normal to subtract.
     *  \return The normal resulting from the given subtraction.
     */
    inline normal operator-(const normal &rhs) const
    {
      return static_cast<const vector&>(*this) - rhs;
    } // end operator-()

    /*! normal addition.
     *  \param rhs The normal to add.
     *  \return The normal resulting from the given addition.
     */
    inline normal operator+(const normal &rhs) const
    {
      return static_cast<const normal&>(*this) + rhs;
    } // end operator+()

    using super_t::operator[];
    using super_t::operator float *;
    using super_t::operator const float *;

    using super_t::x;
    using super_t::y;
    using super_t::z;
}; // end normal


/*! normal scalar multiply.
 *  \param x The scalar to multiply by.
 *  \param n The normal to scale.
 *  \return n multiplied by x.
 */
inline normal operator*(float x, const normal &n)
{
  return normal(x * n.x, x * n.y, x * n.z);
} // end operator*()


} // end igloo

